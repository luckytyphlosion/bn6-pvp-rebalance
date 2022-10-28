#ifndef GUARD_AI_DATA_H
#define GUARD_AI_DATA_H

#define ACTOR_TYPE_VIRUS 0x00
#define ACTOR_TYPE_NAVI 0x01
#define ACTOR_TYPE_PLAYER 0x02

struct AIState {
    u8 unk_00; // loc=0x0
    u8 unk_01; // loc=0x1
    u8 unk_02; // loc=0x2
    u8 unk_03; // loc=0x3
    u8 unk_04; // loc=0x4
    u8 unk_05; // loc=0x5
    u8 unk_06; // loc=0x6
    u8 unk_07; // loc=0x7
    u16 unk_08; // loc=0x8
    u16 unk_0a; // loc=0xa
    u8 unk_0c; // loc=0xc
    u8 unk_0d; // loc=0xd
    u8 unk_0e; // loc=0xe
    u8 unk_0f; // loc=0xf
    u8 unk_10[0x10]; // loc=0x10
};

struct AIAttackVars {
    u8 unk_00; // loc=0x0
    u8 unk_01; // loc=0x1
    u8 unk_02; // loc=0x2
    u8 unk_03; // loc=0x3
    u8 unk_04; // loc=0x4
    u8 unk_05; // loc=0x5
    u16 unk_06; // loc=0x6
    u16 unk_08; // loc=0x8
    u16 unk_0a; // loc=0xa
    u8 unk_0c; // loc=0xc
    u8 unk_0d; // loc=0xd
    u8 unk_0e; // loc=0xe
    u8 unk_0f; // loc=0xf
    u16 unk_10; // loc=0x10
    u16 unk_12; // loc=0x12
    u16 unk_14; // loc=0x14
    u8 unk_16; // loc=0x16
    u8 unk_17; // loc=0x17
    u16 unk_18; // loc=0x18
    u8 unk_1a; // loc=0x1a
    u8 unk_1b; // loc=0x1b
    u8 unk_1c; // loc=0x1c
    u8 unk_1d; // loc=0x1d
    u8 unk_1e; // loc=0x1e
    u8 unk_1f[9]; // loc=0x1f
    u32 unk_28; // loc=0x28
    u32 unk_2c; // loc=0x2c
    u16 unk_30; // loc=0x30 // also size 4
    u16 unk_32; // loc=0x32
    u16 unk_34; // loc=0x34 // also size 4
    u16 unk_36; // loc=0x36
    u32 unk_38; // loc=0x38
    u32 unk_3c; // loc=0x3c
    u32 unk_40; // loc=0x40
    u32 unk_44; // loc=0x44
    u32 unk_48[2]; // loc=0x50
};

struct AIData {
    u8 actorType; // loc=0x0
    u8 aiIndex; // loc=0x1
    u8 unk_02; // loc=0x2
    u8 unk_03; // loc=0x3
    u8 unk_04; // loc=0x4
    u8 unk_05; // loc=0x5
    u8 unk_06; // loc=0x6
    u8 unk_07; // loc=0x7
    u8 unk_08; // loc=0x8
    u8 unk_09; // loc=0x9
    u8 unk_0a; // loc=0xa
    u8 unk_0b; // loc=0xb
    u8 unk_0c; // loc=0xc
    u8 unk_0d; // loc=0xd
    u8 unk_0e; // loc=0xe
    u8 unk_0f; // loc=0xf
    u8 unk_10; // loc=0x10
    u8 unk_11; // loc=0x11
    u8 unk_12; // loc=0x12
    u8 unk_13; // loc=0x13
    u8 unk_14; // loc=0x14
    u8 unk_15; // loc=0x15
    u8 version_16; // loc=0x16
    u8 version_17; // loc=0x17
    u8 unk_18; // loc=0x18
    u8 chipLockoutTimer; // loc=0x19
    u8 unk_1a; // loc=0x1a
    u8 unk_1b; // loc=0x1b
    u8 unk_1c; // loc=0x1c
    u8 unk_1d; // loc=0x1d
    u8 unk_1e; // loc=0x1e
    u8 unk_1f; // loc=0x1f
    u16 totalDamageTaken; // loc=0x20
    u16 joypadHeld; // loc=0x22
    u16 joypadPressed; // loc=0x24
    u16 joypadUp; // loc=0x26
    u16 joypadReleased; // loc=0x28
    u16 unk_2a; // loc=0x2a
    u16 unk_2c; // loc=0x2c
    u16 unk_2e; // loc=0x2e
    u16 unk_30; // loc=0x30
    u16 unk_32; // loc=0x32
    u16 anger; // loc=0x34
    u16 unk_36; // loc=0x36
    u16 unk_38; // loc=0x38
    u16 unk_3a; // loc=0x3a
    u16 unk_3c; // loc=0x3c
    u16 unk_3e; // loc=0x3e
    u32 unk_40; // loc=0x40
    u32 unk_44; // loc=0x44
    u32 unk_48; // loc=0x48
    u32 unk_4c; // loc=0x4c
    u32 unk_50; // loc=0x50
    u32 unk_54; // loc=0x54
    u32 unk_58; // loc=0x58
    u32 unk_5c; // loc=0x5c
    u32 unk_60; // loc=0x60
    u32 unk_64[2]; // loc=0x64
    u32 unk_68; // loc=0x68
    u32 unk_6c; // loc=0x6c
    u32 unk_70; // loc=0x70
    u32 unk_74; // loc=0x74
    u32 unk_78; // loc=0x78
    u32 unk_7c; // loc=0x7c
    struct AIState aiState; // loc=0x80
    struct AIAttackVars aiAttackVars; // loc=0xa0
};

#endif // GUARD_AI_DATA_H
