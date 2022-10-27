
	.align 2, 0
; SetOpponentCheckpoint0:
; 	mov r0, 4
; 	str r0, [r5]
; 	ldr r0, =CHECKPOINT_VALUE_0
; 	ldr r1, =dword_203F5A0
; 	str r0, [r1]
; 	mov pc, lr

HookOpponentTransferBuffer:
	push r4,lr
	mov r4, r10
	ldr r4, [r4, oToolkit_BattleStatePtr]
	ldrb r3, [r4, oBattleState_Unk_00]
	tst r3, r3
	beq @@copyFullStruct
	ldrb r3, [r4, oBattleState_Unk_05]
	tst r3, r3
	beq @@copyFullStruct
	ldr r0, =eSimulatedOpponent
	ldr r1, =unk_2039A00
	ldrh r2, [r0, oSimulatedOpponent_JoypadHeld]
	strh r2, [r1, 2]
	; just in case
	mov r0, 0xff
	strb r0, [r1, 4]
	b @@done
@@copyFullStruct:
	ldr r0, =eStruct2036780
	ldr r1, =unk_2039A00
	mov r2, 0x10
	bl CopyWords
@@done:
	pop r4,pc

; r0 = toolkit
; return player joypad in r1
HookPlayerAndOpponentInput:
	push r4-r7,lr
	ldr r0, [r0, oToolkit_JoypadPtr]
	ldrh r0, [r0, oJoypad_Held]
	mov r1, JOYPAD_SELECT
	tst r0, r1
	bne @@setOpponentJoypad
	mov r1, r0
	ldr r0, =JOYPAD_DEFAULT
	b @@storeOpponentInput
@@setOpponentJoypad:
	bic r0, r1
	mov r1, JOYPAD_LEFT
	tst r0, r1
	bne @@mirrorLeft
	mov r1, JOYPAD_RIGHT
	tst r0, r1
	beq @@loadPlayerInputThenStoreOpponentInput
; mirror right
	bic r0, r1
	mov r1, JOYPAD_LEFT
	b @@setNewLeftRightInput
@@mirrorLeft:
	bic r0, r1
	mov r1, JOYPAD_RIGHT
@@setNewLeftRightInput:
	orr r0, r1
@@loadPlayerInputThenStoreOpponentInput:
	ldr r1, =JOYPAD_DEFAULT
@@storeOpponentInput:
	ldr r2, =eSimulatedOpponent
	strh r0, [r2, oSimulatedOpponent_JoypadHeld]
	pop r4-r7,pc

SetOpponentCheckpointFormAndStoreBattleObject:
	push r4-r7,pc
	ldr r0, =byte_203F658
	mov r1, 0xff
	strb r1, [r0]
	strb r1, [r0, 4]
	ldr r1, =eT1BattleObject1
	str r1, [r0, 8]
	ldr r0, =dword_203F5A0
	ldr r1, =CHECKPOINT_VALUE_1
	str r1, [r0]
	mov r0, SOUND_SELECT_82
	bl PlaySoundEffect
	pop r4-r7,pc

SetOpponentCheckpointAfterRunning:
	ldr r0, =dword_203F5A0
	ldr r1, =CHECKPOINT_VALUE_1
	str r1, [r0]
	; code replaced with bl
	mov r0, 0x14
	strb r0, [r5, 1]
	mov pc, lr
	.pool
