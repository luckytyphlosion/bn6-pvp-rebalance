#pragma once

struct BattleHand {
    u16 curChipIndex;
    u16 chips[6]; // 6th entry is sentinel
    u16 damages[5];
    u8 unk_18[0x38];
};

extern struct BattleHand ePlayerBattleHandSource_203F4A4; // p1 source hand buffer
extern struct BattleHand ePlayerBattleHand;
extern struct BattleHand eOpponentBattleHand;
