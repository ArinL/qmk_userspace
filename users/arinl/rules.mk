SRC += arinl.c
ifdef ENCODER_ENABLE
	# include encoder related code when enabled
	ifeq ($(strip $(ENCODER_DEFAULTACTIONS_ENABLE)), yes)
		OPT_DEFS += -DENCODER_DEFAULTACTIONS_ENABLE
	endif
	SRC += arinl_encoder.c
endif
ifeq ($(strip $(IDLE_TIMEOUT_ENABLE)), yes)
    OPT_DEFS += -DIDLE_TIMEOUT_ENABLE
endif
ifeq ($(strip $(STARTUP_NUMLOCK_ON)), yes)
    OPT_DEFS += -DSTARTUP_NUMLOCK_ON
endif
ifeq ($(strip $(INVERT_NUMLOCK_INDICATOR)), yes)
    OPT_DEFS += -DINVERT_NUMLOCK_INDICATOR
endif
