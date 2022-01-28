# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = yes        # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = yes           # USB Nkey Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = yes       # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
OLED_ENABLE = yes

# MCU name
MCU = STM32F401

# Bootloader selection
BOOTLOADER = stm32-dfu

KEYBOARD_SHARED_EP = yes

WS2812_DRIVER = pwm
HAPTIC_ENABLE += DRV2605L
JOYSTICK_ENABLE = yes
JOYSTICK_DRIVER = analog
POINTING_DEVICE_ENABLE = yes
SPLIT_KEYBOARD = yes
SPLIT_TRANSPORT = serial
SERIAL_DRIVER = usart
SRC += adps9660.c
COMBO_ENABLE = yes
