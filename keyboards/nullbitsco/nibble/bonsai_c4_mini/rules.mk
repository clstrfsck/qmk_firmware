# MCU name
MCU = STM32F411
BOARD = BONSAI_C4

# Bootloader selection
BOOTLOADER = stm32-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE       = yes     # Enable Bootmagic Lite
MOUSEKEY_ENABLE        = no      # Mouse keys
EXTRAKEY_ENABLE        = no      # Audio control and System control
CONSOLE_ENABLE         = yes     # Console for debug
COMMAND_ENABLE         = no      # Commands for debug and configuration
NKRO_ENABLE            = yes     # Enable N-Key Rollover
BACKLIGHT_ENABLE       = no      # Enable keyboard backlight functionality
AUDIO_ENABLE           = no      # Audio output
ENCODER_ENABLE         = yes     # Use rotary encoder
CUSTOM_MATRIX          = lite    # Lite custom matrix

BACKLIGHT_ENABLE       = no      # Enable keyboard backlight functionality
BACKLIGHT_DRIVER       = pwm

RGBLIGHT_ENABLE        = yes     # Enable keyboard RGB underglow
RGBLIGHT_DRIVER        = WS2812
WS2812_DRIVER          = pwm

# Project specific files
SRC += matrix.c nibble.c
