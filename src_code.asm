
	.align 2, 0

CopyNaviStats1ToBattleNaviStats1:
	push lr
	mov r0, 4
	str r0, [r5]
	mov r0, r10
	ldr r0, [r0, oToolkit_NaviStatsPtr]
	ldr r1, =eBattleNaviStats1
	mov r2, oNaviStats_Size
	bl CopyWords
	pop pc

; HookOpponentTransferBuffer:
; 	push r4,lr
; 	mov r4, r10
; 	ldr r4, [r4, oToolkit_BattleStatePtr]
; 	ldrb r3, [r4, oBattleState_Unk_00]
; 	tst r3, r3
; 	beq @@copyFullStruct
; 	ldrb r3, [r4, oBattleState_Unk_05]
; 	tst r3, r3
; 	beq @@copyFullStruct
; 	ldr r0, =eSimulatedOpponent
; 	ldr r1, =unk_2039A00
; 	ldrh r2, [r0, oSimulatedOpponent_JoypadHeld]
; 	strh r2, [r1, 2]
; 	; just in case
; 	mov r0, 0xff
; 	strb r0, [r1, 4]
; 	b @@done
; @@copyFullStruct:
; 	ldr r0, =eStruct2036780
; 	ldr r1, =unk_2039A00
; 	mov r2, 0x10
; 	bl CopyWords
; @@done:
; 	pop r4,pc

; r0 = toolkit
; return player joypad in r1
HookPlayerAndOpponentInput:
	push lr
	mov r0, r12
	push r0
	bl HookPlayerAndOpponentInput_C
	mov r1, r0
	pop r0
	mov r12, r0
	pop pc

OnCustMenuConfirm:
	push lr
	mov r0, r12
	push r0
	bl OnCustMenuConfirm_C
	pop r0
	mov r12, r0
	pop pc

SetOpponentCheckpointAfterRunning:
	ldr r0, =dword_203F5A0
	ldr r1, =CHECKPOINT_VALUE_1
	str r1, [r0]
	; code replaced with bl
	mov r0, 0x14
	strb r0, [r5, 1]
	mov pc, lr

Override_sub_800F964_MovementCheckFunction:
	push r6,r7

	mov r6, r0
	bl object_getFlag
	mov r1, 1
	lsl r1, r1, 0xc
	tst r0, r1
	bne @@loc_800F994
	mov r0, r6
	ldrb r1, [r5, oBattleObject_Alliance]
	bl sub_800F9DE
	ldrb r6, [r5, oBattleObject_PanelX]
	add r6, r6, r0
	ldrb r7, [r5, oBattleObject_PanelY]
	add r7, r7, r1
	mov r0, r6
	mov r1, r7
	bl CheckIfPanelInFieldAndExtendedField
	beq @@loc_800F994
	mov r0, r6
	mov r1, r7
	pop r6,r7
	; hack return value
	ldr r2, =0x80eb0d0|1
	bx r2
@@loc_800F994:
	pop r6,r7
	mov r0, #0
	ldr r2, =0x80eb0cc|1
	bx r2

CheckIfPanelInFieldAndExtendedField:
	add r2, r0, 1 ; negative check
	beq @@doNotMove
	cmp r0, 8
	bge @@doNotMove

	add r2, r1, 1 ; negative check
	beq @@doNotMove
	cmp r1, 5
	bge @@doNotMove
	mov r0, 1
	b @@done
@@doNotMove:
	mov r0, 0
@@done:
	mov pc, lr

	.pool

	.align 4, 0
	.importobj "main.o"
