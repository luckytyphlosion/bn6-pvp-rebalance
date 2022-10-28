
	.arm
	; dumb workaround when linking
	; armips has no way to indicate a label is data
	; which means in the linking stage, externed symbols from an object
	; will always be treated as functions
	; thus, temporarily enable arm so that the thumb bit isn't set

	; MEMORY
	.definelabel eToolkit_ShopData, 0x20032c8
	.definelabel eTrainingModeConfig, 0x20032c8
	.definelabel eTrainingModeConfig_Mode, 0x20032c8
	.definelabel oTrainingModeConfig_Mode, 0x0

	.definelabel TRAINING_MODE_FRAME_DATA, 0
	.definelabel TRAINING_MODE_ELEC_CROSS_DODGING, 1
	
	.definelabel eCutsceneState, 0x2011c50
	.definelabel eJoypad, 0x0200a270
	.definelabel eBattleState, 0x02034880

	.definelabel eT1BattleObject0, 0x203a9b0
	.definelabel eT1BattleObject1, 0x203aa88

	.definelabel eBattleNaviStats, 0x203ce00
	.definelabel eBattleNaviStats1, 0x0203ce64

	.definelabel eOverworldNPCObject0_X, 0x20057d4
	.definelabel eOpponentBattleHand, 0x2034a10

	; NEW MEMORY
	.definelabel eXoshiro128ppState, 0x203f7f0
	.definelabel eSimulatedOpponent, 0x203f800

	.definelabel oSimulatedOpponent_JoypadHeld, 0x0

	.definelabel eNaviStats, 0x20047cc

	.definelabel oNaviStats_Attack, 0x1
	.definelabel oNaviStats_Speed, 0x2
	.definelabel oNaviStats_Charge, 0x3
	.definelabel oNaviStats_RegUP, 0x9
	.definelabel oNaviStats_MaxBaseHP, 0x3e
	.definelabel oNaviStats_CurHP, 0x40
	.definelabel oNaviStats_MaxHP, 0x42
	.definelabel oNaviStats_Folder1Tag2, 0x57
	.definelabel oNaviStats_ChipShuffle, 0x60
	.definelabel oNaviStats_Size, 0x64

	.definelabel oToolkit_JoypadPtr, 0x4
	.definelabel oToolkit_BattleStatePtr, 0x18
	.definelabel oToolkit_ShopDataPtr, 0x54
	.definelabel oToolkit_NaviStatsPtr, 0x74

	.definelabel oJoypad_Held, 0x0

	.definelabel oBattleState_Unk_00, 0x0
	.definelabel oBattleState_Unk_01, 0x1
	.definelabel oBattleState_Unk_05, 0x5

	.definelabel oBattleObject_PanelX, 0x12
	.definelabel oBattleObject_PanelY, 0x13
	.definelabel oBattleObject_Alliance, 0x16
	.definelabel oBattleObject_HP, 0x24
	.definelabel oBattleObject_MaxHP, 0x26
	.definelabel oBattleObject_RelatedObject1Ptr, 0x4c
	.definelabel oBattleObject_AIDataPtr, 0x58

	; ignore the byte/word/dword prefix it means nothing
	; but want to keep labels consistent with disassembly
	.definelabel eStruct2036780, 0x2036780
	.definelabel unk_2039A00, 0x2039A00
	.definelabel byte_203F658, 0x203F658
	.definelabel dword_203F5A0, 0x203f5a0

	.thumb
	; FUNCTIONS

	.definelabel ZeroFillByWord, 0x80008e0
	.definelabel CopyWords, 0x800093c
	.definelabel battle_isBattleOver, 0x0800a18e
	.definelabel object_getFlag, 0x0801a166
	.definelabel battle_isPaused, 0x0800a03c

	.definelabel NPCScript_StationaryNPC, 0x809f6cc

	.definelabel STARTING_MAP_ADDR, 0x80050e4

	.definelabel PlaySoundEffect, 0x80005cc

	.definelabel GetRNG2, 0x0800151c
	.definelabel GetRNG1, 0x0800154c

	.definelabel ShuffleFolderSlice, 0x8000d12
	.definelabel battle_clearFlags, 0x800a2e4
	.definelabel sub_800F964, 0x800F964
	.definelabel sub_800F9DE, 0x800F9DE
	.definelabel SetCustGauge, 0x801DFA2

	; eToolkit_ShopData equ 0x20032c8

	.definelabel call_via_r4, 0x814da70
	.definelabel umodsi3, 0x0814db34

	.definelabel battle_isTimeStop, 0x0800a098
	.definelabel TestEventFlag, 0x0802f168

	.definelabel sprite_forceWhitePalette, 0x08002db0
	.definelabel sprite_setFinalPalette, 0x08002db4
	.definelabel sprite_getFinalPalette, 0x08002dc8
	.definelabel sprite_clearFinalPalette, 0x08002dd8

; ewram freespace at 203f7f0

