
	.gba

	.include "macros.asm"
	.include "defines.asm"
	.include "constants.asm"

	INPUT_ROM equ "bn6f.gba"
	OUTPUT_ROM equ "bn6f-pvp-rebalance.gba"
	; start of map scripts, shouldn't do anything bad as long as we restrict to acdc
	CODE_FREESPACE_START equ 0x804d104
	CODE_FREESPACE_SIZE equ 0x807f68f - 0x804d104

	.open INPUT_ROM, OUTPUT_ROM, 0x8000000
ROMStart:

	; == orgs ==
	.include "common/src_orgs.asm"
	.if ENABLE_TRAINING_MODE == 1
	.include "training-mode/src_orgs.asm"
	.endif
	.include "rebalance/src_orgs.asm"

	; == code ==
	.org CODE_FREESPACE_START
	.area CODE_FREESPACE_SIZE
	.include "common/src_code.asm"
	.if ENABLE_TRAINING_MODE == 1
	.include "training-mode/src_code.asm"
	.endif
	.include "rebalance/src_code.asm"
	.endarea

	; == farspace ==
	.org 0x087FE380
	.include "common/src_farspace.asm"
	.if ENABLE_TRAINING_MODE == 1
	.include "training-mode/src_farspace.asm"
	.endif
	.include "rebalance/src_farspace.asm"
	; MUST BE LAST
	.include "allstars/src.s"

	.close
