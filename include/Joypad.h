#ifndef GUARD_JOYPAD_H
#define GUARD_JOYPAD_H

#define JOYPAD_DEFAULT  0xFC00
#define JOYPAD_A  0x0001
#define JOYPAD_B  0x0002
#define JOYPAD_SELECT  0x0004
#define JOYPAD_START  0x0008
#define JOYPAD_RIGHT  0x0010
#define JOYPAD_LEFT  0x0020
#define JOYPAD_UP  0x0040
#define JOYPAD_DOWN  0x0080
#define JOYPAD_ARROWS  (JOYPAD_RIGHT | JOYPAD_LEFT | JOYPAD_UP | JOYPAD_DOWN)
#define JOYPAD_R  0x0100
#define JOYPAD_L  0x0200

struct Joypad {
	u16 held; // loc=0x0
	// no unused flags set to one, only used signals
	u16 pressed; // loc=0x2
	u16 lowSensitivityHeld; // loc=0x4
	u16 held2; // loc=0x6
	u8 aHeldTimer; // loc=0x8
	u8 bHeldTimer; // loc=0x9
	u8 selectHeldTimer; // loc=0xa
	u8 startHeldTimer; // loc=0xb
	u8 rightHeldTimer; // loc=0xc
	u8 leftHeldTimer; // loc=0xd
	u8 upHeldTimer; // loc=0xe
	u8 downHeldTimer; // loc=0xf
	u8 rHeldTimer; // loc=0x10
	u8 lHeldTimer; // loc=0x11
	u8 undetected_12; // loc=0x12
	u8 lowSensitivityTimer; // loc=0x13
};

#endif // GUARD_JOYPAD_H
