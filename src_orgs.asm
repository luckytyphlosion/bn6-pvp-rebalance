
	.org STARTING_MAP_ADDR
	.byte GROUP_ACDC_TOWN
	.byte MAP_ACDC_TOWN

	; prevent warps
	.org 0x80058d0
	mov pc, lr

	; set max HP to 1000
	.org 0x8013b80
	mov r0, 1000 >> 2
	lsl r0, r0, 2

	; prevent jacking in at all
	.org 0x8034d34
	b loc_8034d44

	.org 0x8034d44
loc_8034d44:

	; map text pointer for ACDC Town
	.org 0x80445E0
	.word ACDCTownTextScript_NEW

	; off_804CF9C, map object pointer for ACDC Town
	.org 0x804CF9C
	.word ACDCTown_MapObjects_NEW

	; ACDCTown_OnInitMapScripts_804d0a4
	.org 0x804d0a4
	.word ACDCTown_OnInitMapScript_NEW

	; ACDCTown_ContinuousMapScripts_804d0ac
	.org 0x804d0ac
	.word ACDCTown_ContinuousMapScript_NEW

	; ACDCTown_MapGroupNPCScriptPointers_804d0b4
	.org 0x804d0b4
	.word ACDCTown_NPCScripts_NEW

	; ACDCTown_CoordInteractionTextIndicesPointers_804d0bc
	.org 0x804d0bc
	.word 0x804d0d4 ; Class6A_CoordInteractionTextIndices_804d0d4

	; battleSettingsList0
	.org 0x80aee70 + 8 * 0x10
; ACDCTown_TrainingModeBattle:
	.byte 0x00 ;Battlefield
	.byte 0x00 ;byte1
	.byte 0x15 ;Music
	.byte 0x00 ;Battle Mode
	.byte 0x07 ;Background (Generic Comp)
	.byte 0x00 ;Battle Count
	.byte 0x38 ;Panel pattern
	.byte 0x00 ;byte7
	.word 0x004198D7 | 0x20
	.word ACDCTown_TrainingModeBattleLayout

	.align 4, 0
ACDCTown_TrainingModeBattleLayout:
;player
	.byte 0x00, 0x22
	.halfword 0
;opponent
	.byte 0x11, 0x25
	.halfword 0x1a0 ; enemy megaman
	.byte 0xF0
