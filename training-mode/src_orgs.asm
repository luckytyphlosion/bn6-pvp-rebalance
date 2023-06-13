
	; .org 0x800f988
	; bl CheckIfPanelInFieldAndExtendedField

	; hook after battle init
	.org 0x8007a3a
	bl OnAfterBattleInit

	; chip lockout check
	.org 0x80107de
	bl ChipLockoutCheck
	nop
	nop
	nop

	;;; enable alpha while invis happens
	;;.org 0x8016958
	;;bl DoInvisFlashingFlickerAndRemoveShadow
	;;b 0x8016964
	;;
	;;; disable alpha after invis stops
	;;.org 0x801A634
	;;bl HookEnableShadowForInvis
	;;
	;;; disable alpha after flashing stops
	;;.org 0x801B326
	;;bl HookEnableShadowForInvis

	; buffer copy ask your uncle weenie
	.org 0x801FEDC
	bl HookOpponentTransferBuffer
	pop r4,r6,pc

	; force game to copy opponent inputs
	.org 0x801ff5a
	nop

	.org 0x801FF88
	bl HookPlayerAndOpponentInput

	.org 0x8026ffc
	bl SetOpponentCheckpointAfterRunning

	.org 0x8028D62
	bl OnCustMenuConfirm
	nop

	; battleSettingsList0
	.org 0x80aee70 + 8 * 0x10
; ACDCTown_TrainingModeBattle:
	.byte 0x00 ; Battlefield
	.byte 0x00 ; byte1
	.byte 0x15 ; Music
	.byte 0x00 ; Battle Mode
	.byte 15 ; Background (Undernet)
	.byte 0x00 ; Battle Count
	.byte 0x38 ; Panel pattern
	.byte 0x00 ; byte7
	.word 0x004198D5 | 0x20
	.word ACDCTown_TrainingModeBattleLayout

	.byte 0x00 ; Battlefield
	.byte 0x00 ; byte1
	.byte 0x15 ; Music
	.byte 0x00 ; Battle Mode
	.byte 0x7 ; Background (Generic BG)
	.byte 0x00 ; Battle Count
	.byte 0x38 ; Panel pattern
	.byte 0x00 ; byte7
	.word 0x004198D5 | 0x20
	.word ACDCTown_TrainingModeBattleLayout

	.align 4, 0
ACDCTown_TrainingModeBattleLayout:
	; player
	.byte 0x00, 0x22
	.halfword 0
	; opponent
	.byte 0x11, 0x25
	.halfword 0x1a0 ; enemy megaman
	.byte 0xF0

	.org 0x80eb0a4
	; override panel validity check when moving
	bl Override_sub_800F964_MovementCheckFunction

	; custom gauge always full
	.org 0x801DF92
	push lr
	ldr r0, [pc, 0x1c] ; =0x4000
	bl SetCustGauge
	mov r0, 0x10
	bl battle_clearFlags
	pop pc

	; beast over doesn't auto-open cust gauge
 	.org 0x800A200
Org_CheckIfCustGaugeFullForBeastOver:
 	bl CheckIfCustGaugeFullForBeastOver
 	pop pc

	; disable folder shuffling
	.org ShuffleFolderSlice
	mov pc, lr

	; treat gigas as standard chips (keeps them in place)
	.org 0x800a590
	nop

	; opponent copies player hand in frame data mode
	.org 0x800B3D8
	push r4, lr
	bl CopyHandBuffersToPlayers
	b 0x800B408

	; ignore chip codes when selecting
	.org 0x8028f00
	b 0x8028f3e

	; undernet BGAnimData, just replace palette
	.org 0x8081188
	.word UndernetBGAnimDataPalette_NEW
