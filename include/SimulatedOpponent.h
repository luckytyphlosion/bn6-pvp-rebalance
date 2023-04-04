#pragma once

#define ACTION_MAIN 0
#define ACTION_WAIT_MOVEMENT 1
#define ACTION_WAIT_ATTACK 2

#define STATE_WAIT_MOVEMENT_WAIT_MOVEMENT_START 0
#define STATE_WAIT_MOVEMENT_WAIT_MOVEMENT_FINISH 1

#define STATE_WAIT_MOVEMENT_WAIT_ATTACK_START 0
#define STATE_WAIT_MOVEMENT_WAIT_ATTACK_FINISH 1

struct GenericOpponentState {
    u8 curAction; // 0x0
    u8 changedAction; // 0x1
    u8 runAction; // 0x2
    u8 actionState; // 0x3
    u8 movementDirection; // 0x4
    u16 globalFrameCounter;
    u16 input;
    u16 stickyInput;
    union {
        // frame data
        struct {
            u8 isControllingOpponent; // overload for frame data mode
        };
        // elec cross dodging
        struct {
            u8 randomSteps;
        };
        // BDT dodging
        struct {
            u8 bdtState;
            u8 bdtChargeTimer;
        };
    };
};

struct SimulatedOpponent {
    u16 joypadHeld;
    u8 inCross;
    struct GenericOpponentState oppState;
};

extern struct SimulatedOpponent eSimulatedOpponent;
