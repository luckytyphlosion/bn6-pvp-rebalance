#pragma once

struct BattleHand {
    u16 curChipIndex;
    u16 chips[6]; // 6th entry is sentinel
    u16 damages[5];
};

extern struct BattleHand eOpponentBattleHand;
