#ifndef GUARD_COLLISION_DATA_H
#define GUARD_COLLISION_DATA_H

#define OBJECT_FLAGS_GUARD                   0x00000001
#define OBJECT_FLAGS_INVIS                   0x00000002
#define OBJECT_FLAGS_UNK_4                   0x00000004
#define OBJECT_FLAGS_INVULNERABLE            0x00000008
#define OBJECT_FLAGS_AIRSHOE                 0x00000010
#define OBJECT_FLAGS_FLOATSHOE               0x00000020
#define OBJECT_FLAGS_CANNOT_SLIDE            0x00000040
#define OBJECT_FLAGS_UNK_8                   0x00000080
#define OBJECT_FLAGS_DEAD                    0x00000100
#define OBJECT_FLAGS_FLASHING                0x00000200
#define OBJECT_FLAGS_FLINCHING               0x00000400
#define OBJECT_FLAGS_PARALYZED               0x00000800
#define OBJECT_FLAGS_SLIDING                 0x00001000
#define OBJECT_FLAGS_BLIND                   0x00002000
#define OBJECT_FLAGS_IMMOBILIZED             0x00004000
#define OBJECT_FLAGS_CONFUSED                0x00008000
#define OBJECT_FLAGS_FROZEN                  0x00010000
#define OBJECT_FLAGS_SUPERARMOR              0x00020000
#define OBJECT_FLAGS_UNDERSHIRT              0x00040000
#define OBJECT_FLAGS_MOVE_COMPLETE           0x00080000
#define OBJECT_FLAGS_DRAG                    0x00100000
#define OBJECT_FLAGS_ANGER                   0x00200000
#define OBJECT_FLAGS_USING_ACTION            0x00400000
#define OBJECT_FLAGS_UNK_24                  0x00800000
#define OBJECT_FLAGS_UNK_25                  0x01000000
#define OBJECT_FLAGS_AFFECTED_BY_ICE         0x02000000
#define OBJECT_FLAGS_UNK_26                  0x04000000
#define OBJECT_FLAGS_UNAFFECTED_BY_POISON    0x08000000
#define OBJECT_FLAGS_UNK_28                  0x10000000
#define OBJECT_FLAGS_UNK_29                  0x20000000
#define OBJECT_FLAGS_UNK_30                  0x40000000
#define OBJECT_FLAGS_BUBBLED                 0x80000000

#define OBJECT_FLAGS_IMMOBILIZED_BIT         14
#define OBJECT_FLAGS_FROZEN_BIT              16
#define OBJECT_FLAGS_SUPERARMOR_BIT          17
#define OBJECT_FLAGS_CURRENTLY_MOVING_1_BIT  19
#define OBJECT_FLAGS_UNK_BIT_20_BIT          20
#define OBJECT_FLAGS_UNK_BIT_21_BIT          21
#define OBJECT_FLAGS_UNK_BIT_22_BIT          22

struct CollisionData {
    bool8 enabled; // loc=0x0
    u8 region; // loc=0x1
    u8 primaryElement; // loc=0x2
    u8 unk_03; // loc=0x3
    
    union {
        struct {
            u8 alliance; // loc=0x4
            u8 flip; // loc=0x5
        };
        u16 allianceAndDirectionFlip; // loc=0x4
    };

    u8 barrier; // loc=0x6; // barrier
    u8 staminaDamageCounterDisabler; // loc=0x7
    u8 poisonPanelTimer; // loc=0x8
    u8 hitEffect; // loc=0x9

    union {
        struct {
            u8 panelX; // loc=0xa
            u8 panelY; // loc=0xb
        };
        u16 panelXY; // loc=0xa
    };
    
    u8 direction; // loc=0xc
    u8 counterTimer; // loc=0xd
    u8 hitModifierBase; // loc=0xe
    u8 hitModifierFinal; // loc=0xf
    u8 statusEffectBase; // loc=0x10
    u8 statusEffectFinal; // loc=0x11
    u16 bugs; // loc=0x12
    u8 unk_14; // loc=0x14
    u8 unk_15; // loc=0x15
    u8 unk_16; // loc=0x16
    u8 unk_17; // loc=0x17
    u8 secondaryElementWeakness; // loc=0x18
    u8 secondaryElement; // loc=0x19
    
    union {
        struct {
            u8 unk_1a; // loc=0x1a
            u8 unk_1b; // loc=0x1b
        };
        u16 unk_1a_1b; // loc=0x1a
    };

    u16 unk_1c; // loc=0x1c
    u16 unk_1e; // loc=0x1e
    u16 unk_20; // loc=0x20
    u16 unk_22; // loc=0x22
    u16 unk_24; // loc=0x24
    u16 unk_26; // loc=0x26
    u16 unk_28; // loc=0x28
    u16 unk_2a; // loc=0x2a
    u16 unk_2c; // loc=0x2c
    u16 selfDamage; // loc=0x2e
    u32 selfCollisionTypeFlags; // loc=0x30
    u32 targetCollisionTypeFlags; // loc=0x34
    u32 parentObjectPtr; // loc=0x38
    u32 objectFlags1; // loc=0x3c
    u32 objectFlags2; // loc=0x40
    u32 collisionIndexBit; // loc=0x44
    u32 unk_48; // loc=0x48
    u32 unk_4c[2]; // loc=0x4c
    u32 unk_54; // loc=0x54
    u32 unk_58; // loc=0x58
    u32 unk_5c; // loc=0x5c
    u32 unk_60; // loc=0x60
    u32 unk_64; // loc=0x64
    u32 unk_68; // loc=0x68
    u32 unk_6c; // loc=0x6c
    u32 flagsFromCollision; // loc=0x70
    u8 exclamationIndicator; // loc=0x74
    u8 damageMultiplier; // loc=0x75
    u8 damageElements; // loc=0x76
    u8 unk_77; // loc=0x77
    u32 unk_78; // loc=0x78
    u32 unk_7c; // loc=0x7c
    u16 finalDamage; // loc=0x80
    u16 panelDamage1; // loc=0x82
    u16 panelDamage2; // loc=0x84
    u16 panelDamage3; // loc=0x86
    u16 panelDamage4; // loc=0x88
    u16 panelDamage5; // loc=0x8a
    u16 panelDamage6; // loc=0x8c

    u16 unk_8e; // loc=0x8e
    u16 unk_90; // loc=0x90
    u16 unk_92; // loc=0x92

    union {
        struct {
            u16 nullElementDamage; // loc=0x94
            u16 heatElementDamage; // loc=0x96
            u16 aquaElementDamage; // loc=0x98
            u16 elecElementDamage; // loc=0x9a
            u16 woodElementDamage; // loc=0x9c
        };
        u16 primaryElementDamages[5]; // loc=0x94
    };

    u16 unk_9e; // loc=0x9e
    u32 unk_a0; // loc=0xa0
    u32 inflictedBugs; // loc=0xa4
};

#endif // GUARD_COLLISION_DATA_H
