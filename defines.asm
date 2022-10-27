
	; ignore the byte/word/dword prefix it means nothing
	; but want to keep labels consistent with disassembly
	.definelabel eStruct2036780, 0x2036780
	.definelabel unk_2039A00, 0x2039A00
	.definelabel byte_203F658, 0x203F658
	.definelabel dword_203F5A0, 0x203f5a0

	.definelabel CopyWords, 0x800093c
	.definelabel battle_isBattleOver, 0x0800a18e
	.definelabel object_getFlag, 0x0801a166

	.definelabel eOverworldNPCObject0_X, 0x20057d4

	.definelabel NPCScript_StationaryNPC, 0x809f6cc

	.definelabel STARTING_MAP_ADDR, 0x80050e4

	.definelabel PlaySoundEffect, 0x80005cc

	.definelabel sub_800F964, 0x800F964
	.definelabel sub_800F9DE, 0x800F9DE

	.definelabel eT1BattleObject0, 0x203a9b0
	.definelabel eT1BattleObject1, 0x203aa88

; ewram freespace at 203f7f0

	.definelabel eSimulatedOpponent, 0x203f7f0
	.definelabel oSimulatedOpponent_JoypadHeld, 0x0

	.definelabel oNaviStats_Attack, 0x1
	.definelabel oNaviStats_Speed, 0x2
	.definelabel oNaviStats_Charge, 0x3
	.definelabel oNaviStats_RegUP, 0x9
	.definelabel oNaviStats_MaxBaseHP, 0x3e
	.definelabel oNaviStats_CurHP, 0x40
	.definelabel oNaviStats_MaxHP, 0x42
	.definelabel oNaviStats_Folder1Tag2, 0x57
	.definelabel oNaviStats_ChipShuffle, 0x60

	.definelabel oToolkit_JoypadPtr, 0x4
	.definelabel oToolkit_BattleStatePtr, 0x18
	.definelabel oToolkit_NaviStats, 0x74

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
