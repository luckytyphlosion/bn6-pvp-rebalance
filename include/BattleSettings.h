#ifndef GUARD_BATTLE_SETTINGS_H
#define GUARD_BATTLE_SETTINGS_H

struct BattleSettings {
    u8 battlefield;
    u8 unk_01;
    u8 music;
    u8 battleMode;
    u8 background;
    u8 battleCount;
    u8 panelColumnPattern;
    u8 unk_07;
    u32 battleEffects;
    u32 * objectSetupPtr;
};

#endif // GUARD_BATTLE_SETTINGS_H
