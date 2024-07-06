LTO_ENABLE = yes               			# link time optimization -- achieves a smaller compiled size
CONSOLE_ENABLE = no						# connect to keyboard consoles to get debugging messages - https://docs.qmk.fm/cli_commands#qmk-console
COMMAND_ENABLE = no						# change keyboards behavior without having to flash - https://docs.qmk.fm/features/command

VIA_ENABLE = no							# VIA compatibility - https://www.caniusevia.com/docs/configuring_qmk
BOOTMAGIC_ENABLE = yes         			# Enable Bootmagic Lite - by default, hold ESC while plugging in keyboard to enter bootloader - https://docs.qmk.fm/features/bootmagic

IDLE_TIMEOUT_ENABLE = yes				# enables idle timeout of RGB
ENCODER_DEFAULTACTIONS_ENABLE = no		# encoder default actions

STARTUP_NUMLOCK_ON = no					# default numlock behavior
INVERT_NUMLOCK_INDICATOR = no			# invert numlock rgb indicator