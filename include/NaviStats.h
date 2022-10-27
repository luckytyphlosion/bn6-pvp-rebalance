#ifndef GUARD_NAVI_STATS_H
#define GUARD_NAVI_STATS_H

struct NaviStats {
    u8 unk_00; // loc=0x0
    u8 attack; // loc=0x1
    u8 speed; // loc=0x2
    u8 charge; // loc=0x3
    u8 unk_04[2]; // loc=0x4
    u8 fstBarr; // loc=0x6
    u8 bLeftAbility; // loc=0x7
    u8 unk_08; // loc=0x8
    u8 regUP; // loc=0x9
    u8 customLevel; // loc=0xa
    u8 megaLevel; // loc=0xb
    u8 gigaLevel; // loc=0xc
    u8 unk_0d; // loc=0xd
    u8 mood; // loc=0xe
    u8 unk_0f[10]; // loc=0xf
    u8 custHPBug; // loc=0x19
    u8 unk_1a[7]; // loc=0x1a
    u8 beastOutCounter; // loc=0x21
    u8 unk_22; // loc=0x22
    u8 superArmor; // loc=0x23
    u8 unk_24[8]; // loc=0x24
    u8 transformation; // loc=0x2c
    u8 unk_2d; // loc=0x2d
    u8 folder1Reg; // loc=0x2e
    u8 folder2Reg; // loc=0x2f
    u8 unk_30; // loc=0x30
    u8 processingBug; // loc=0x31
    u8 unk_32[12]; // loc=0x32
    u16 maxBaseHP; // loc=0x3e
    u16 curHP; // loc=0x40
    u16 maxHP; // loc=0x42
    u8 unk_44[8]; // loc=0x44
    u8 unk_4c; // loc=0x4c
    u8 unk_4d[3]; // loc=0x4d
    u16 chipRecovery; // loc=0x50
    u8 unk_52[4]; // loc=0x52
    u8 folder1Tag1; // loc=0x56
    u8 folder1Tag2; // loc=0x57
    u8 folder2Tag1; // loc=0x58
    u8 folder2Tag2; // loc=0x59
    u8 unk_5a[9]; // loc=0x5a
    u8 turnsUntilCustBugActivates; // loc=0x63
};

extern struct NaviStats eNaviStats[2];
extern struct NaviStats eBattleNaviStats[2];

#endif // GUARD_NAVI_STATS_H
