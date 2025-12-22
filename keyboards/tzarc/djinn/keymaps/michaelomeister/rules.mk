DEBUG_MATRIX_SCAN_RATE_ENABLE ?= api
ENCODER_MAP_ENABLE = yes
SWAP_HANDS_ENABLE = no
AUDIO_ENABLE = no
NKRO_ENABLE = yes
DYNAMIC_TAPPING_TERM_ENABLE = yes
KEYCODE_STRING_ENABLE = yes
VPATH += $(KEYMAP_PATH)/graphics
SRC += \
	theme.c \
	frieren.qgf.c \
	lock-caps-ON.qgf.c \
	lock-scrl-ON.qgf.c \
	lock-num-ON.qgf.c \
	lock-caps-OFF.qgf.c \
	lock-scrl-OFF.qgf.c \
	lock-num-OFF.qgf.c \
	unispace18.qff.c
