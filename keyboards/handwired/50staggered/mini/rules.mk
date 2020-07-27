# MCU name
MCU = atmega32u4

# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = atmel-dfu

AUDIO_ENABLE = no           # Audio output on port C6
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
BOOTMAGIC_ENABLE = lite     # Virtual DIP switch configuration
COMBO_ENABLE = no           # Key combos
COMMAND_ENABLE = no         # Commands for debug and configuration
CONSOLE_ENABLE = no         # Console for debug
EXTRAKEY_ENABLE = yes       # Audio control and System control
FAUXCLICKY_ENABLE = no      # Use buzzer to emulate clicky switches
HD44780_ENABLE = no         # Enable support for HD44780 based LCDs
KEY_LOCK_ENABLE = no        # Leader to hold down keys until pressed a second time
LEADER_ENABLE = no          # Leader key chording
MIDI_ENABLE = no            # MIDI support
MOUSEKEY_ENABLE = yes       # Mouse keys
NKRO_ENABLE = no            # USB Nkey Rollover
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
TAP_DANCE_ENABLE = yes      # Key tapping
TERMINAL_ENABLE = no        # Terminal access to keyboard
UNICODE_ENABLE = no         # Unicode
