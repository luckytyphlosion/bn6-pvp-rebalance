
ACDCTown_OnInitMapScript_NEW:
	ms_jump_if_flag_set CS_VAR_IMM, EVENT_402, @@alreadyInitialized
	ms_set_event_flag CS_VAR_IMM, EVENT_402
	ms_set_enter_map_screen_fade 0x1c, 0xff
	ms_start_cutscene ACDCTown_GiveFolder2NaviCustAllProgsAllChipsScript, 0x0
@@alreadyInitialized:
	ms_end

ACDCTown_ContinuousMapScript_NEW:
	.if ENABLE_TRAINING_MODE == 1
	ms_jump_if_flag_clear CS_VAR_IMM, EVENT_403_START_TRAINING_MODE_CUTSCENE, @@doNotStartBattle
	ms_start_cutscene ACDCTown_StartTrainingModeCutsceneScript, 0x0
	ms_clear_event_flag CS_VAR_IMM, EVENT_403_START_TRAINING_MODE_CUTSCENE
@@doNotStartBattle:
	ms_jump_if_flag_clear CS_VAR_IMM, EVENT_404_TALKED_TO_MODE_NPC, @@notTalkedToModeNPC
	ms_start_cutscene ACDCTown_SetTrainingModeCutsceneScript, 0x0
	ms_clear_event_flag CS_VAR_IMM, EVENT_404_TALKED_TO_MODE_NPC
@@notTalkedToModeNPC:
	ms_end
	.else
 	ms_jump_if_flag_clear CS_VAR_IMM, EVENT_406_NON_TRAINING_MODE_START_BATTLE, @@notTalkedToMegaMan
 	ms_start_cutscene StartBattleGeneric, 0x1ff0018
 	ms_clear_event_flag CS_VAR_IMM, EVENT_406_NON_TRAINING_MODE_START_BATTLE
@@notTalkedToMegaMan:
 	ms_end
	.endif

	.if ENABLE_TRAINING_MODE == 1
	.align 4, 0
ACDCTown_NPCScripts_NEW:
	.word ACDCTown_MegaManNPCScript
	.word ACDCTown_TrainingModeNPCScript
	.word ACDCTown_ChipLockoutNPCScript
	.word 0xff

ACDCTown_MegaManNPCScript:
	npc_set_active_and_visible
	npc_set_text_script_index 1
	npc_set_sprite SPRITE_NPC_MEGA_MAN ; scientist man
	npc_set_coords 65520, 162, 0
	npc_set_animation 7 ; up left
	npc_jump_with_link NPCScript_StationaryNPC

ACDCTown_TrainingModeNPCScript:
	npc_set_active_and_visible
	npc_set_text_script_index 2
	npc_set_sprite SPRITE_NPC_PINK_GIRL_NAVI ; scientist man
	npc_set_coords 65520, 80, 0
	npc_set_animation 7 ; up left
	npc_jump_with_link NPCScript_StationaryNPC

ACDCTown_ChipLockoutNPCScript:
	npc_set_active_and_visible
	npc_set_text_script_index 10
	npc_set_sprite SPRITE_NPC_GREEN_NAVI ; scientist man
	npc_set_coords 20, 162, 0
	npc_set_animation 7 ; up left
	npc_jump_with_link NPCScript_StationaryNPC

	.else

	.align 4, 0
ACDCTown_NPCScripts_NEW:
	.word ACDCTown_ProtoManNPCScript
	.word 0xff

ACDCTown_ProtoManNPCScript:
	npc_set_active_and_visible
	npc_set_text_script_index 6
	npc_set_sprite SPRITE_NPC_PROTO_MAN ; scientist man
	npc_set_coords 65520, 162, 0
	npc_set_animation 7 ; up left
	npc_jump_with_link NPCScript_StationaryNPC
	.endif

ACDCTown_GiveFolder2NaviCustAllProgsAllChipsScript:
	cs_lock_player_for_non_npc_dialogue_809e0b0
	cs_run_text_script CS_VAR_IMM, 0
	cs_set_event_flag CS_VAR_IMM, EVENT_NAVICUST_ENABLE
	cs_set_event_flag_range 136, EVENT_SOLID_PARTS_COMPRESSION
	cs_set_event_flag_range 12, EVENT_MAX_PARTS_COMPRESSION
	cs_give_item ITEM_SPINWHIT, 1
	cs_give_item ITEM_SPINYLLW, 1
	cs_give_item ITEM_SPINPINK, 1
	cs_give_item ITEM_SPINRED, 1
	cs_give_item ITEM_SPINBLUE, 1
	cs_give_item ITEM_SPINGRN, 1
	cs_give_item ITEM_EXPMEMRY, 2
	cs_give_item ITEM_REGUP1, 46
	cs_give_item ITEM_TAGCHIP, 1
	cs_set_event_flag_range 5, EVENT_HAS_SPOUTCROSS
	cs_set_event_flag CS_VAR_IMM, EVENT_HAS_BEAST_OUT
	cs_give_bugfrags 9999
	cs_call_native_with_return_value ZeroOutShopData|1
	cs_wait_chatbox 0x80
	cs_warp_cmd_8038040_2 0x0, MAP_GROUP_TRANSITION_TYPE_SAME_MAP_GROUP_TYPE, ACDCTown_CutsceneWarpData
	cs_unlock_player_after_non_npc_dialogue_809e122
	cs_end_for_map_reload_maybe_8037c64

	.if ENABLE_TRAINING_MODE == 1
ACDCTown_StartTrainingModeCutsceneScript:
	cs_lock_player_for_non_npc_dialogue_809e0b0
	cs_jump_if_byte_equals eTrainingModeConfig_Mode, @@undernetBGBattle, 0
	cs_start_fixed_battle 9
	cs_jump @@afterStartBattle
@@undernetBGBattle:
	cs_start_fixed_battle 8
@@afterStartBattle:
	cs_unlock_player_after_non_npc_dialogue_809e122
	cs_end_for_map_reload_maybe_8037c64

ACDCTown_SetTrainingModeCutsceneScript:
	cs_set_event_flag CS_VAR_IMM, EVENT_405_IN_MODE_NPC_CUTSCENE
	cs_set_var 4, 0
	cs_set_var 5, 0
	cs_wait_var_equal 5, 1
	cs_call_native_with_return_value SaveChosenTrainingMode|1
	cs_end_for_map_reload_maybe_8037c64
	.endif

ACDCTown_MapObjects_NEW:
	.byte 0xff

	.align 4, 0
ACDCTown_CutsceneWarpData:
	.byte GROUP_ACDC_TOWN
	.byte MAP_ACDC_TOWN
	.byte 0 ; fade to black
	.byte OW_DOWN_RIGHT
	.word 0xffff0000
	.word 0x380000
	.word 0

	.align 4, 0
ACDCTownTextScript_NEW:
	.import "temp/ACDCTownScript.msg.lz"
