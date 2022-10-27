#ifndef GUARD_BATTLE_STATE_H
#define GUARD_BATTLE_STATE_H

#include "BattleSettings.h"

struct BattleState {
    u8 unk_00; // loc=0x0
    u8 unk_01; // loc=0x1
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
    u8 unk_16; // loc=0x16
    u8 unk_17; // loc=0x17
    u8 unk_18; // loc=0x18
    u8 unk_19; // loc=0x19
    u8 unk_1a; // loc=0x1a
    u8 unk_1b; // loc=0x1b
    u8 unk_1c; // loc=0x1c
    u8 unk_1d; // loc=0x1d
    u8 unk_1e; // loc=0x1e
    u8 unk_1f; // loc=0x1f
    u16 unk_20; // loc=0x20
    u16 unk_22[3]; // loc=0x22
    u16 unk_28; // loc=0x28
    u16 unk_2a[2]; // loc=0x2a
    u16 unk_32; // loc=0x32
    u16 unk_34; // loc=0x34
    u16 unk_36; // loc=0x36
    u16 unk_38; // loc=0x38
    u16 unk_3a; // loc=0x3a
    struct BattleSettings * battleSettings; // loc=0x3c
    u32 unk_40; // loc=0x40
    // todo: figure out where these are accessed
    // analyzer detects these but obviously not an imm read
    u8 unk_44; // loc=0x44
    u8 unk_45; // loc=0x45
    u8 unk_46[22]; // loc=0x46
    u32 unk_5c; // loc=0x5c
    u32 unk_60; // loc=0x60
    u32 unk_64; // loc=0x64
    u32 unk_68[6]; // loc=0x68

    union {
        struct {
            struct BattleObject * alivePlayerActors[4]; // loc=0x80
            struct BattleObject * aliveOpponentActors[4]; // loc=0x90
        };
        struct BattleObject * aliveBattleActors[8]; // loc=0x80
    };

    u32 unk_a0[12]; // loc=0xa0
    union {
        struct {
            struct BattleObject * playerActors[4]; // loc=0xd0
            struct BattleObject * opponentActors[4]; // loc=0xe0
        };
        struct BattleObject * battleActors[8]; // loc=0xd0
    };
};

extern struct BattleState eBattleState;

#endif // GUARD_BATTLE_STATE_H
