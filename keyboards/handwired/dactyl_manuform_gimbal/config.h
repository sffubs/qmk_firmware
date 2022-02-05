/*
Copyright 2015 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID    0xFEED
#define PRODUCT_ID   0x6465
#define DEVICE_VER   0x0001
#define MANUFACTURER QMK

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 6

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* define if matrix has ghost (lacks anti-ghosting diodes) */
//#define MATRIX_HAS_GHOST

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define IGNORE_MOD_TAP_INTERRUPT
#define TAPPING_TERM 150
#define TAPPING_TERM_PER_KEY

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

/* disable these deprecated features by default */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

/* Bootmagic Lite key configuration */
//#define BOOTMAGIC_LITE_ROW 0
//#define BOOTMAGIC_LITE_COLUMN 0
/* Copyright 2019
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

#define PRODUCT Onekey Blackpill STM32F401

#define MATRIX_COL_PINS {A4, A5, A6, A7, B0, B1} // {B1, B0, A7, A6, A5, A4}
#define MATRIX_ROW_PINS {B5, A15, B3, B4} //, NO_PIN, NO_PIN, NO_PIN, NO_PIN}; // {A12, A15, B3, B4}
#define UNUSED_PINS

#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 5

#define BOOTMAGIC_LITE_ROW_LEFT 0
#define BOOTMAGIC_LITE_COLUMN_LEFT 5

#define BOOTMAGIC_LITE_ROW_RIGHT 4
#define BOOTMAGIC_LITE_COLUMN_RIGHT 5

#define BACKLIGHT_PIN         A0
#define BACKLIGHT_PWM_DRIVER  PWMD5
#define BACKLIGHT_PWM_CHANNEL 1

#define ADC_PIN A0

#define RGBLED_NUM 24
//#define RGBLED_SPLIT {21, 24}
#define RGB_DI_PIN A8
#define RGBLIGHT_ANIMATIONS
//#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_LAYERS
//#define NOP_FUDGE 0.5
//#define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_RGB
#define WS2812_PWM_DRIVER PWMD1  // default: PWMD2
#define WS2812_PWM_CHANNEL 1
#define WS2812_PWM_PAL_MODE 1
#define WS2812_DMA_STREAM STM32_DMA2_STREAM5  // DMA Stream for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#define WS2812_DMA_CHANNEL 6  // DMA Channel for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
//#define WS2812_DMAMUX_ID STM32_DMAMUX1_TIM2_UP // DMAMUX configuration for TIMx_UP -- only required if your MCU has a DMAMUX peripheral, see the respective reference manual for the appropriate values for your MCU.

#define I2C1_SCL_PAL_MODE 4
#define I2C1_SDA_PAL_MODE 4
#define I2C1_SCL_BANK GPIOB
#define I2C1_SCL 6
#define I2C1_SDA_BANK GPIOB
#define I2C1_SDA 7

#define OLED_TIMEOUT 3000

// Haptic stuff
#define FB_ERM_LRA 1
#define FB_BRAKEFACTOR 3 /* For 1x:0, 2x:1, 3x:2, 4x:3, 6x:4, 8x:5, 16x:6, Disable Braking:7 */
#define FB_LOOPGAIN 3 /* For  Low:0, Medium:1, High:2, Very High:3 */

#define RATED_VOLTAGE 1.8
#define V_RMS 1.8
#define V_PEAK 1.9
#define F_LRA 235 /* resonance freq */

#define DRV_GREETING 0
#define DRV_MODE_DEFAULT 6
#define NO_HAPTIC_FN
#define NO_HAPTIC_ALPHA
#define NO_HAPTIC_PUNCTUATION
#define NO_HAPTIC_LOCKKEYS
#define NO_HAPTIC_NAV
#define NO_HAPTIC_NUMERIC

// Joystick
#define JOYSTICK_AXES_COUNT 2
#define JOYSTICK_BUTTON_COUNT 0

// Split serial
#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN A9
#define SERIAL_USART_RX_PIN A10
#define SERIAL_USART_DRIVER SD1
#define SERIAL_USART_TX_PAL_MODE 7
#define SERIAL_USART_RX_PAL_MODE 7
#define SERIAL_USART_TIMEOUT 20

// Split
#define SPLIT_HAND_PIN B10
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LAYER_STATE_SET
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_TRANSACTION_IDS_KB KEYBOARD_SYNC_MOUSE_ENABLED, KEYBOARD_SYNC_LED

// Combos
#define COMBO_COUNT (27 + 38)
#define EXTRA_LONG_COMBOS
