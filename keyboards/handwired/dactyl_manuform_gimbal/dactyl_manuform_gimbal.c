/* Copyright 2020 Sergey Vlasov (sigprof)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <math.h>

#include "print.h"

#include QMK_KEYBOARD_H

#include "adps9660.h"
#include "analog.h"
#include "DRV2605L.h"
#include "joystick.h"
#include "pointing_device.h"
#include "transactions.h"

extern void enable_mouse_layer_left(void);

extern void disable_mouse_layer_left(void);

extern void enable_mouse_layer_right(void);

extern void disable_mouse_layer_right(void);

static void read_gimbal(void);

static void keyboard_sync_mouse_enabled_slave_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data);

static void keyboard_sync_led_slave_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data);

static void wakeup(void);

bool mouse_enabled;
uint8_t prox_threshold;

struct joystick_calib_t {
  int lower;
  int centre;
  int upper;
  int deadzone;
};

struct joystick_calib_t joystick_calibration[2] =
  {
   {33, 495, 963, 5},
   {215, 560, 898, 5},
  };

static int joystick_x;
static int joystick_y;
uint16_t joystick_x_raw;
uint16_t joystick_y_raw;

typedef struct _master_to_slave_t {
} master_to_slave_t;

typedef struct _slave_to_master_t {
  bool mouse_enabled;
} slave_to_master_t;

// Backlight timeout feature
#define LED_TIMEOUT 10    // in minutes
static uint16_t idle_timer = 0;
static uint8_t halfmin_counter = 0;
static bool led_on = true;

void board_init(void) {
    // B9 is configured as I2C1_SDA in the board file; that function must be
    // disabled before using B7 as I2C1_SDA.
    setPinInputHigh(B9);

    palSetPadMode(GPIOA, 1, PAL_MODE_INPUT_ANALOG);
    palSetPadMode(GPIOA, 2, PAL_MODE_INPUT_ANALOG);
    //palSetPadMode(GPIOB, 6, PAL_STM32_MODE_ALTERNATE | PAL_STM32_ALTERNATE(4));
    //palSetPadMode(GPIOB, 7, PAL_STM32_MODE_ALTERNATE | PAL_STM32_ALTERNATE(4));
}

void keyboard_post_init_kb(void) {
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(0, 255, 102);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL + 3);
    rgblight_set_speed_noeeprom(0);

    adps9660_init();
    wait_ms(100);
    prox_threshold = 0;
    for (int i = 0; i < 10; ++i) {
      uint8_t prox;
      adps9660_proximity(&prox);
      if (prox > prox_threshold) {
	prox_threshold = prox;
      }
      wait_ms(20);
    }
    prox_threshold += 2;
    uprintf("Threshold: %d\n", prox_threshold);

    read_gimbal();
    joystick_calibration[0].centre = joystick_x_raw;
    joystick_calibration[1].centre = joystick_y_raw;

    if (!is_keyboard_left()) {
      joystick_calibration[0].lower = 95;
      joystick_calibration[0].upper = 754;
      joystick_calibration[1].lower = 159;
      joystick_calibration[1].upper = 885;
    }
    
    transaction_register_rpc(KEYBOARD_SYNC_MOUSE_ENABLED, keyboard_sync_mouse_enabled_slave_handler);
    transaction_register_rpc(KEYBOARD_SYNC_LED, keyboard_sync_led_slave_handler);
    
    keyboard_post_init_user();
}

int rate_curve(double input);
double gimbal_calibrate(int input, int axis);

#if 0
void oled_task_user(void) {
  // Host Keyboard Layer Status
  char msg[256];

  // Host Keyboard Layer Status
  
  //oled_write_P(PSTR("Hello world!\n"), false);
  
  //snprintf(msg, sizeof(msg), "%04d %04d", joystick_status.axes[0], joystick_status.axes[1]);
  snprintf(msg, sizeof(msg), "%04d %04d\n", joystick_x_raw, joystick_y_raw);
  oled_write(msg, false);
  snprintf(msg, sizeof(msg), "%04d %04d\n", joystick_x, joystick_y);
  oled_write(msg, false);
  uint8_t prox;
  adps9660_proximity(&prox);
  snprintf(msg, sizeof(msg), "%04d %04d\n", prox, prox_threshold);
  oled_write(msg, false);
}
#endif

joystick_config_t joystick_axes[JOYSTICK_AXES_COUNT] = {
							[0] = JOYSTICK_AXIS_IN(A2, 2450, 31970, 61670),
							[1] = JOYSTICK_AXIS_IN(A1, 11670, 36720, 59420)
};

static void read_gimbal(void) {
  joystick_x_raw = analogReadPin(A2);
  joystick_y_raw = analogReadPin(A1);
  joystick_x = rate_curve(gimbal_calibrate(joystick_x_raw, 0));
  joystick_y = rate_curve(gimbal_calibrate(joystick_y_raw, 1));

  if (!is_keyboard_left()) {
    joystick_x *= -1;
    joystick_y *= -1;
  }
}

// Turn raw gimbal reading into a value from -127 to 127.
double gimbal_calibrate(int input, int axis) {
  int centred = input - joystick_calibration[axis].centre;
  double val;

  if (abs(centred) < joystick_calibration[axis].deadzone) {
    return 0.0;
  }
  
  if (centred < 0) {
    val = ((double)centred) / ((double)(joystick_calibration[axis].centre - joystick_calibration[axis].lower));
  } else {
    val = ((double)centred) / ((double)(joystick_calibration[axis].upper - joystick_calibration[axis].centre));
  }

  return val;
}

double rate = 0.09;
double super = 0.03;

int rate_curve(double input) {
  double x = input * 127;
  return (int)(x * rate + pow(x * rate, 3) * super);
}

/*
static int limit(int val, int limit) {
  if (abs(val) > limit) {
    return val < 0 ? -limit : limit;
  } else {
    return val;
  }
}
*/

void pointing_device_task(void) {
  static uint32_t last_report = 0u;
  if (timer_elapsed32(last_report) > 10) {
    last_report = timer_read32();

    report_mouse_t currentReport = pointing_device_get_report();
    
    currentReport.x = joystick_x;
    currentReport.y = joystick_y;
    
    pointing_device_set_report(currentReport);
    pointing_device_send();
  }
}

void housekeeping_task_kb(void) {
  static int prev_prox_state = 0;
  static uint32_t prev_prox_time = 0;
  //static int prox_enabled_mouse = 0;
  
  static uint32_t last_measurement = 0u;
  static uint32_t measurement_interval = 10u;
  
  if (timer_elapsed32(last_measurement) > measurement_interval) {
    last_measurement = timer_read32();
    
    read_gimbal();
    
    uint8_t prox;
    adps9660_proximity(&prox);

    //uprintf("Proximity: %d (%d)\n", prox, prox_threshold);
    
    if (prox > prox_threshold || joystick_x != 0 || joystick_y != 0) {
      if (prev_prox_state == 0) {
	measurement_interval = 10;
	prev_prox_state = 1;
	prev_prox_time = timer_read32();
      } else if (timer_elapsed32(prev_prox_time) > 200) {
	measurement_interval = 100;
	if (is_keyboard_left()) {
	  enable_mouse_layer_left();
	} else {
	  mouse_enabled = true;
	}
      }
    }
    else {
      if (prev_prox_state == 1) {
	measurement_interval = 10;
	prev_prox_state = 0;
	prev_prox_time = timer_read32();
      } else if (timer_elapsed32(prev_prox_time) > 200) {
	measurement_interval = 100;
	if (is_keyboard_left()) {
	  disable_mouse_layer_left();
	} else {
	  mouse_enabled = false;
	}
      }
    }
  }

  if (is_keyboard_master()) {
    static uint32_t last_sync = 0;
    if (timer_elapsed32(last_sync) > 100) {
      master_to_slave_t m2s = {};
      slave_to_master_t s2m = {0};
      if (transaction_rpc_exec(KEYBOARD_SYNC_MOUSE_ENABLED, sizeof(m2s), &m2s, sizeof(s2m), &s2m)) {
	last_sync = timer_read32();
	if (s2m.mouse_enabled) {
	  enable_mouse_layer_right();
	} else {
	  disable_mouse_layer_right();
	}
      }
    }
  }
}

bool is_keyboard_master(void) {
  return is_keyboard_left();
}

void keyboard_sync_mouse_enabled_slave_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
  slave_to_master_t *s2m = (slave_to_master_t*)out_data;
  s2m->mouse_enabled = mouse_enabled;
}

void keyboard_sync_led_slave_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
  bool* led_master_on = (bool*)in_data;
  if (*led_master_on) {
    rgblight_enable_noeeprom();
  } else {
    rgblight_disable_noeeprom();
  }
}

void matrix_scan_kb(void) {
  // idle_timer needs to be set one time
  if (idle_timer == 0) idle_timer = timer_read();

  if (led_on) {
    if (timer_elapsed(idle_timer) > 30000) {
      halfmin_counter++;
      idle_timer = timer_read();
    }
  
    if (halfmin_counter >= LED_TIMEOUT * 2) {
      rgblight_disable_noeeprom();
      led_on = false;
      halfmin_counter = 0;
      transaction_rpc_exec(KEYBOARD_SYNC_LED, sizeof(led_on), &led_on, 0, NULL);
    }
  }
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    wakeup();
  }
  return true;
}

layer_state_t layer_state_set_kb(layer_state_t state) {
  wakeup();
  return layer_state_set_user(state);
}

static void wakeup(void) {
  if (led_on == false) {
    rgblight_enable_noeeprom();
    led_on = true;
    transaction_rpc_exec(KEYBOARD_SYNC_LED, sizeof(led_on), &led_on, 0, NULL);
  }
  idle_timer = timer_read();
  halfmin_counter = 0;
}
