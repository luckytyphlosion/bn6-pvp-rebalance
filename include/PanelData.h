#ifndef GUARD_PANEL_DATA_H
#define GUARD_PANEL_DATA_H

#include "BattleObject.h"

struct PanelData {
	u8 visible; // loc=0x0
	u8 unk_01; // loc=0x1
	u8 type; // loc=0x2
	u8 alliance; // loc=0x3
	u8 unk_04; // loc=0x4
	u8 unk_05; // loc=0x5
	u8 animation; // loc=0x6
	u8 unk_07; // loc=0x7
	u8 unk_08; // loc=0x8
	u8 unk_09; // loc=0x9
	u8 unk_0a[3]; // loc=0xa
	u8 unk_0d; // loc=0xd
	u8 unk_0e[2]; // loc=0xe
	u16 unk_10; // loc=0x10
	u16 unk_12; // loc=0x12
	u32 flags; // loc=0x14
	// 0x00000002 - blocks movement
	// 0x00800000 - neutral support object
	// 0x01000000 - enemy support object
	// 0x02000000 - ally support object
	// 0x04000000 - enemy alliance
	// 0x08000000 - ally alliance
	// 0x10000000 - enemy attack object
	// 0x20000000 - ally attack object
	// 0x40000000 - enemy attack
	// 0x80000000 - ally attack
	u32 unk_18; // loc=0x18
	struct BattleObject * reserverObjectPtr; // loc=0x1c
};

#endif // GUARD_PANEL_DATA_H
