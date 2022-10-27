#ifndef GUARD_BATTLE_OBJECT_H
#define GUARD_BATTLE_OBJECT_H

#include "CollisionData.h"
#include "AIData.h"

#define OBJECT_FLAG_ACTIVE                   0x01
#define OBJECT_FLAG_VISIBLE                  0x02
#define OBJECT_FLAG_PAUSE_UPDATE             0x04
#define OBJECT_FLAG_STOP_SPRITE_UPDATE       0x08
#define OBJECT_FLAG_UPDATE_DURING_TIMESTOP   0x10
#define OBJECT_FLAG_UNK_20                   0x20
#define OBJECT_FLAG_UNK_40                   0x40
#define OBJECT_FLAG_UNK_80                   0x80

#define CUR_STATE_INITIALIZE  0x00
#define CUR_STATE_UPDATE      0x04
#define CUR_STATE_DESTROY     0x08

#define DAMAGE_DOUBLE                0x8000
#define DAMAGE_PARALYZE              0x4000
#define DAMAGE_UNINSTALL             0x2000
#define DAMAGE_ERASECROSS_SKULL_HIT  0x1000
#define DAMAGE_NOTHING               0x0800

struct BattleObject {
    u8 flags; // loc=0x0
    u8 index; // loc=0x1
    union {
        u8 typeAndSpriteOffset; // loc=0x2
        struct {
            u8 type:4; // 0X
            u8 spriteOffset:4; // X0
        };
    };
    u8 listIndex; // loc=0x3

    union {
        u32 params; // loc=0x4
        struct {
            u8 param1; // loc=0x4
            u8 param2; // loc=0x5
            u8 param3; // loc=0x6
            u8 param4; // loc=0x7
        };
    };

    union {
        struct {
            u8 curState; // loc=0x8
            u8 curAction; // loc=0x9
            u8 curPhase; // loc=0xa
            bool8 phaseInitialized; // loc=0xb
        };
        struct {
            u16 curState_curAction; // loc=0x8
            u16 curPhaseAndPhaseInitialized; // loc=0xa
        };
        struct {
            u32 curStateActionPhaseAndPhaseInitialized; // loc=0x8
        };
    };

    u8 unk_0c; // loc=0xc
    u8 unk_0d; // loc=0xd
    u8 element; // loc=0xe
    u8 unk_0f; // loc=0xf

    union {
        struct {
            u8 curAnim; // loc=0x10
            u8 curAnimCopy; // loc=0x11
        };
        u16 curAnimAndCurAnimCopy; // loc=0x10
    };

    union {
        struct {
            u8 panelX; // loc=0x12
            u8 panelY; // loc=0x13
        };
        u16 panelXY; // loc=0x12
    };

    union {
        struct {
            u8 futurePanelX; // loc=0x14
            u8 futurePanelY; // loc=0x15
        };
        u16 futurePanelXY; // loc=0x14
    };

    union {
    // Alliance: 0 = friend, 1 = enemy
        struct {
            bool8 alliance; // loc=0x16
            u8 directionFlip; // loc=0x17
        };
        u16 allianceAndDirectionFlip; // loc=0x16
    };

    u8 preventAnim; // loc=0x18
    u8 unk_19; // loc=0x19
    u8 chipsHeld;  // loc=0x1a
    u8 unk_1b; // loc=0x1b
    u8 unk_1c; // loc=0x1c
    u8 unk_1d; // loc=0x1d

    union {
        struct {
            u8 unk_1e; // loc=0x1e
            u8 unk_1f; // loc=0x1f
        };
        u16 unk_1e_unk_1f; // loc=0x1e
    };

    union {
        struct {
            u16 timer; // loc=0x20
            u16 timer2; // loc=0x22
        };
        u32 timerAndTimer2; // loc=0x20
    };

    u16 hp; // loc=0x24
    u16 maxHP; // loc=0x26

    union {
        struct {
            u16 nameID; // loc=0x28
            u16 chip; // loc=0x2a
        };
        u32 nameIDAndChip; // loc=0x28
    };

    // Damage: also includes flags. 0x7FF is damage
    // StaminaDamageCounterDisabler: ???
    union {
        struct {
            u16 damage; // loc=0x2c
            u16 staminaDamageCounterDisabler; // loc=0x2e
        };
        u32 damageAndStaminaDamageCounterDisabler; // loc=0x2c
    };

    u16 unk_30; // loc=0x30
    u16 unk_32; // loc=0x32
    union {
        struct {
            u16 x16L; // loc=0x34
            u16 x16; // loc=0x36
            u16 y16L; // loc=0x38
            u16 y16; // loc=0x3a
            u16 z16L; // loc=0x3c
            u16 z16; // loc=0x3e
        };
        struct {
            u32 x; // loc=0x34
            u32 y; // loc=0x38
            u32 z; // loc=0x3c
        };
        u32 coords[3]; // loc=0x34
    };

    u32 xVelocity; // loc=0x40
    u32 yVelocity; // loc=0x44
    u32 zVelocity; // loc=0x48
    struct BattleObject * relatedObject1; // loc=0x4c
    struct BattleObject * relatedObject2; // loc=0x50
    struct CollisionData * collisionData; // loc=0x54
    struct AIData * aiData; // loc=0x58
    u32 unk_5c; // loc=0x5c
    
    union {
        u8 extraVars8[0]; // 0x60
        u16 extraVars16[0]; // 0x60
        u32 extraVars32[0]; // 0x60
    };
};

extern struct BattleObject eT1BattleObject0;
extern struct BattleObject eT1BattleObject1;

#endif // GUARD_BATTLE_OBJECT_H
