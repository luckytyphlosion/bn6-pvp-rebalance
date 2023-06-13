
	.gba

	.include "macros.asm"
	.include "defines.asm"
	.include "constants.asm"

	INPUT_ROM equ "bn6f.gba"
	OUTPUT_ROM equ "bn6f-training-mode.gba"
	; start of map scripts, shouldn't do anything bad as long as we restrict to acdc
	CODE_FREESPACE_START equ 0x804d104
	CODE_FREESPACE_SIZE equ 0x807f68f - 0x804d104

	.open INPUT_ROM, OUTPUT_ROM, 0x8000000

	.include "training-mode/src_orgs.asm"
	.include "rebalance/src_orgs.asm"

	.org CODE_FREESPACE_START
	.include "training-mode/src_code.asm"
	.include "rebalance/src_code.asm"

	.org 0x087FE380
	.include "training-mode/src_farspace.asm"
	.include "rebalance/src_farspace.asm"
	.include "allstars/src.s"

	.close
