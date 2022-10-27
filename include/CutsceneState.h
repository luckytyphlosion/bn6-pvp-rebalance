#ifndef GUARD_CUTSCENE_H
#define GUARD_CUTSCENE_H

#define CUTSCENE_SCRIPT_UNK_MAGIC_SCRIPT_VALUE_0x1 0x1

#define CUTSCENE_FLAG_SCRIPT_1_PAUSED 0x0
#define CUTSCENE_FLAG_SCRIPT_2_PAUSED 0x1
#define CUTSCENE_FLAG_SCRIPT_3_PAUSED 0x2
#define CUTSCENE_FLAG_SCRIPT_4_PAUSED 0x3
#define CUTSCENE_FLAG_SCRIPT_1_PAUSED_LONG 0x4
#define CUTSCENE_FLAG_SCRIPT_2_PAUSED_LONG 0x5
#define CUTSCENE_FLAG_SCRIPT_3_PAUSED_LONG 0x6
#define CUTSCENE_FLAG_SCRIPT_4_PAUSED_LONG 0x7
#define CUTSCENE_FLAG_8 0x8
#define CUTSCENE_FLAG_9 0x9

struct CutsceneState {
    u8 unk_00[4]; // loc=0x0
    u8 unk_04; // loc=0x4
    u8 unk_05; // loc=0x5
    u8 unk_06; // loc=0x6
    u8 unk_07; // loc=0x7
    u8 unk_08[4]; // loc=0x8
    u8 cutsceneScript1PauseTimer; // loc=0xc
    u8 cutsceneScript2PauseTimer; // loc=0xd
    u8 cutsceneScript3PauseTimer; // loc=0xe
    u8 cutsceneScript4PauseTimer; // loc=0xf
    u8 owPlayerCoordSpecialTimer; // loc=0x10
    u8 transformPlayerNaviSpriteTimer; // loc=0x11
    u8 whichCutsceneScript; // loc=0x12
    u8 cutsceneCameraScriptActive; // loc=0x13
    u16 cutsceneScript1LongPauseTimer; // loc=0x14
    u16 cutsceneScript2LongPauseTimer; // loc=0x16
    u16 cutsceneScript3LongPauseTimer; // loc=0x18
    u16 cutsceneScript4LongPauseTimer; // loc=0x1a
    u8 * cutsceneScriptPos; // loc=0x1c
    u8 * cutsceneScriptPos2; // loc=0x20
    u8 * cutsceneScriptPos3; // loc=0x24
    u8 * cutsceneScriptPos4; // loc=0x28
    u32 cutsceneFlags; // loc=0x2c
    void * textArchivePtr; // loc=0x30
    void * unk_34; // loc=0x34
    u8 * cutsceneScriptAfterCutsceneSkip; // loc=0x38
    u8 * cutsceneCameraScriptPtr; // loc=0x3c
    u8 * originalCutsceneScriptPos_40; // loc=0x40
    u32 owMapObjectPtrs_44[11]; // loc=0x44
    u32 unk_70[8]; // loc=0x70
};

extern struct CutsceneState eCutsceneState;

//__asm__(
//    ".section .bss"
//    ".type eCutsceneState, STT_OBJECT"
//    
//);

#endif // GUARD_CUTSCENE_H
