
	; orgs to start in ACDC town
	; and some map related orgs to
	; give us more free space for code

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

	; enable interworking for cs_call_native_with_return_value
	.org 0x8038030
	bl call_via_r4

	; map text pointer for ACDC Town
	.org 0x80445E0
	.word ACDCTownTextScript_NEW

	; don't load in shop data
	.org 0x8048C98
	mov pc, lr

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
