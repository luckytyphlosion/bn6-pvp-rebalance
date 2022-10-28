
	.definelabel GROUP_ACDC_TOWN, 0x0
	.definelabel MAP_ACDC_TOWN, 0x0

	.definelabel EVENT_HAS_BEAST_OUT, 0xe0
	.definelabel EVENT_HAS_SPOUTCROSS, 0xe7

	.definelabel EVENT_NAVICUST_ENABLE, 0xf2
	.definelabel EVENT_402, 0x402
	.definelabel EVENT_403, 0x403
	.definelabel EVENT_404_TALKED_TO_MODE_NPC, 0x404
	.definelabel EVENT_405_IN_MODE_NPC_CUTSCENE, 0x405

	.definelabel EVENT_SOLID_PARTS_COMPRESSION, 0x2664
	.definelabel EVENT_MAX_PARTS_COMPRESSION, 0x26f8

	.definelabel CS_VAR_IMM, 0xff
	
	.definelabel OW_UP, 0
	.definelabel OW_UP_RIGHT, 1
	.definelabel OW_RIGHT, 2
	.definelabel OW_DOWN_RIGHT, 3
	.definelabel OW_DOWN, 4
	.definelabel OW_DOWN_LEFT, 5
	.definelabel OW_LEFT, 6
	.definelabel OW_UP_LEFT, 7

	.definelabel JOYPAD_DEFAULT, 0xFC00
	.definelabel JOYPAD_A, 0x0001
	.definelabel JOYPAD_B, 0x0002
	.definelabel JOYPAD_SELECT, 0x0004
	.definelabel JOYPAD_START, 0x0008
	.definelabel JOYPAD_RIGHT, 0x0010
	.definelabel JOYPAD_LEFT, 0x0020
	.definelabel JOYPAD_UP, 0x0040
	.definelabel JOYPAD_DOWN, 0x0080
	.definelabel JOYPAD_ARROWS, JOYPAD_RIGHT | JOYPAD_LEFT | JOYPAD_UP | JOYPAD_DOWN
	.definelabel JOYPAD_R, 0x0100
	.definelabel JOYPAD_L, 0x0200

	.definelabel CHECKPOINT_VALUE_0, 0x12345678
	.definelabel CHECKPOINT_VALUE_1, 0x56789123

	.definelabel ITEM_TAGCHIP, 11
	.definelabel ITEM_SPINWHIT, 80
	.definelabel ITEM_SPINYLLW, 81
	.definelabel ITEM_SPINPINK, 82
	.definelabel ITEM_SPINRED, 83
	.definelabel ITEM_SPINBLUE, 84
	.definelabel ITEM_SPINGRN, 85
	.definelabel ITEM_EXPMEMRY, 113
	.definelabel ITEM_REGUP1, 114

	.definelabel SONG_NO_MUSIC, 0x00
	.definelabel SONG_TITLE_SCREEN, 0x01
	.definelabel SONG_WWW_THEME, 0x02
	.definelabel SONG_CYBER_CITY, 0x03
	.definelabel SONG_INDOORS, 0x04
	.definelabel SONG_SCHOOL, 0x05
	.definelabel SONG_SEASIDE_TOWN, 0x06
	.definelabel SONG_SKY_TOWN, 0x07
	.definelabel SONG_GREEN_TOWN, 0x08
	.definelabel SONG_GRAVEYARD_AREA, 0x09
	.definelabel SONG_MR_WEATHER_COMP, 0x0A
	.definelabel SONG_EVENT_OCCURANCE, 0x0B
	.definelabel SONG_PANIC, 0x0C
	.definelabel SONG_SAD, 0x0D
	.definelabel SONG_HAPPY, 0x0E
	.definelabel SONG_TRANSMISSION, 0x0F
	.definelabel SONG_ROBO_CONTROL_COMP, 0x10
	.definelabel SONG_AQUARIUM_COMP, 0x11
	.definelabel SONG_JUDGE_TREE_COMP, 0x12
	.definelabel SONG_NETWORK, 0x13
	.definelabel SONG_UNDERNET, 0x14
	.definelabel SONG_VIRUS_BATTLE, 0x15
	.definelabel SONG_BOSS_BATTLE, 0x16
	.definelabel SONG_FINAL_BATTLE, 0x17
	.definelabel SONG_PAVILION, 0x18
	.definelabel SONG_WINNER_0, 0x19
	.definelabel SONG_LOSER, 0x1A
	.definelabel SONG_GAME_OVER, 0x1B
	.definelabel SONG_BOSS_PRELUDE, 0x1C
	.definelabel SONG_CREDITS, 0x1D
	.definelabel SONG_NAVI_CUSTOMIZER, 0x1E
	.definelabel SONG_WINNER_1, 0x1F
	.definelabel SONG_PAVILION_COMP, 0x20
	.definelabel SONG_CYBERBEASTS, 0x21
	.definelabel SONG_CROSSOVER_BATTLE, 0x22
	.definelabel SONG_SHARK_CHASE, 0x23
	.definelabel SONG_ACDC_TOWN, 0x24
	.definelabel SONG_EXPO, 0x25

	.definelabel SOUND_BEEP_64, 0x64
	.definelabel SOUND_TYPE, 0x65
	.definelabel SOUND_UNK_66, 0x66
	.definelabel SOUND_SELECT_67, 0x67
	.definelabel SOUND_UNSELECT_68, 0x68
	.definelabel SOUND_CANT_JACK_IN, 0x69
	.definelabel SOUND_BUSTER_6A, 0x6A
	.definelabel SOUND_HIT_6B, 0x6B
	.definelabel SOUND_DELETED, 0x6C
	.definelabel SOUND_HIT_6D, 0x6D
	.definelabel SOUND_HIT_6E, 0x6E
	.definelabel SOUND_HIT_BOMB_0, 0x6F
	.definelabel SOUND_HIT_BOMB_1, 0x70
	.definelabel SOUND_BUSTER_CHARGE, 0x71
	.definelabel SOUND_UNK_72, 0x72
	.definelabel SOUND_UNK_73, 0x73
	.definelabel SOUND_UNK_74, 0x74
	.definelabel SOUND_BEEP_75, 0x75
	.definelabel SOUND_LOG_OUT_76, 0x76
	.definelabel SOUND_LOG_IN_77, 0x77
	.definelabel SOUND_BATTLE_START, 0x78
	.definelabel SOUND_SELECT_79, 0x79
	.definelabel SOUND_SELECT_7A, 0x7A
	.definelabel SOUND_UNSELECT_7B, 0x7B
	.definelabel SOUND_UNSELECT_7C, 0x7C
	.definelabel SOUND_UNK_7D, 0x7D
	.definelabel SOUND_UNK_7E, 0x7E
	.definelabel SOUND_MENU_CUR_MOVE, 0x7F
	.definelabel SOUND_CUR_MOVE_80, 0x80
	.definelabel SOUND_MENU_SELECT, 0x81
	.definelabel SOUND_SELECT_82, 0x82
	.definelabel SOUND_EXIT_SUBMENU, 0x83
	.definelabel SOUND_LOW_HP, 0x84
	.definelabel SOUND_UNK_85, 0x85
	.definelabel SOUND_SELECT_86, 0x86
	.definelabel SOUND_HIT_87, 0x87
	.definelabel SOUND_UNK_88, 0x88
	.definelabel SOUND_UNK_89, 0x89
	.definelabel SOUND_UNK_8A, 0x8A
	.definelabel SOUND_OK_8B, 0x8B
	.definelabel SOUND_UNK_8C, 0x8C
	.definelabel SOUND_UNK_8D, 0x8D
	.definelabel SOUND_FADE_8E, 0x8E
	.definelabel SOUND_UNK_8F, 0x8F
	.definelabel SOUND_UNK_90, 0x90
	.definelabel SOUND_ERR_SELECT_91, 0x91
	.definelabel SOUND_CANNON_LAUNCH_AE, 0xAE
	.definelabel SOUND_EXPLOSION_C3, 0xc3

	.definelabel MAP_GROUP_TRANSITION_TYPE_SAME_MAP_GROUP_TYPE, 0x0
	.definelabel MAP_GROUP_TRANSITION_TYPE_INTERNET_TO_REAL_WORLD, 0x1
	.definelabel MAP_GROUP_TRANSITION_TYPE_REAL_WORLD_TO_INTERNET, 0x2

	.definelabel SPRITE_NPC_MEGA_MAN, 0x37
	.definelabel SPRITE_NPC_GREEN_NAVI, 0x3e
	.definelabel SPRITE_NPC_PINK_GIRL_NAVI, 0x45
