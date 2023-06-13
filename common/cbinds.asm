
TestEventFlag_CBind:
	push lr
	bl TestEventFlag
	and r0, r1
	pop pc

sprite_forceWhitePalette_CBind:
	push r5, lr
	mov r5, r0
	bl sprite_forceWhitePalette
	pop r5, pc

sprite_setFinalPalette_CBind:
	push r5, lr
	mov r5, r0	
	bl sprite_setFinalPalette
	pop r5, pc

sprite_clearFinalPalette_CBind:
	push r5, lr
	mov r5, r0
	bl sprite_clearFinalPalette
	pop r5, pc

sprite_setColorShader_CBind:
	push r5, lr
	mov r5, r0
	mov r0, r1
	bl sprite_setColorShader
	pop r5, pc

sprite_zeroColorShader_CBind:
	push r5, lr
	mov r5, r0
	bl sprite_zeroColorShader
	pop r5, pc
