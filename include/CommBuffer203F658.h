#pragma once

#include "BattleObject.h"

struct CommBuffer203F658 {
    u8 chosenForm;
    u8 unk_01[3];
    u8 unk_04;
    u8 unk_05[3];
    struct BattleObject * unkBattleObjectPtr;
};

extern struct CommBuffer203F658 byte_203F558;
extern struct CommBuffer203F658 byte_203F658;
extern struct CommBuffer203F658 byte_203CED0;
