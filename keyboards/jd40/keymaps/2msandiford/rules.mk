ifndef QUANTUM_DIR
        include ../../../../Makefile
endif

API_SYSEX_ENABLE    = no         # Control through Sysex API
AUDIO_ENABLE        = no         # Audio output on port C6
BACKLIGHT_ENABLE    = yes        # Enable keyboard backlight functionality on B7 by default
BLUETOOTH_ENABLE    = no         # Enable Bluetooth with the Adafruit EZ-Key HID
BOOTMAGIC_ENABLE    = no         # Virtual DIP switch configuration (+1000)
COMBO_ENABLE        = no         # Enable key combinations
COMMAND_ENABLE      = yes        # Commands for debug and configuration
CONSOLE_ENABLE      = no         # Console for debug (+4700)
EXTRAKEY_ENABLE     = yes        # Audio control and System control (+450)
FAUXCLICKY_ENABLE   = no         # Use buzzer to emulate clicky switches
LCD_ENABLE          = no         # LCD displays
MIDI_ENABLE         = no         # MIDI support (+2400 to 4200, depending on config)
MUSIC_ENABLE        = no         # Music support
MOUSEKEY_ENABLE     = no         # Mouse keys (+4000)
NKRO_ENABLE         = yes        # USB Nkey Rollover
PRINTING_ENABLE     = no         # Printing
RGBLIGHT_ENABLE     = no         # Adafruit WS2812 RGB lights
SERIAL_LINK_ENABLE  = no         # Serial link between boards
STENO_ENABLE        = no         # Steography enable
TAP_DANCE_ENABLE    = no         # Key tapping
UCIS_ENABLE         = no
UNICODEMAP_ENABLE   = no
UNICODE_ENABLE      = no         # Unicode
VIRTSER_ENABLE      = no         # Virtual serial (required for Steno)
