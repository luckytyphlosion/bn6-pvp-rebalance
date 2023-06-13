#pragma once

extern void CopyWords(void * src, void * dest, u32 size);
extern void ZeroFillByWord(void * src, u32 size);
extern bool32 battle_isPaused(void);
extern void PlaySoundEffect(u32 soundEffect);
extern u32 GetRNG1(void);
extern u32 GetRNG2(void);
extern bool32 battle_isTimeStop(void);
extern bool32 TestEventFlag_CBind(u16 eventFlag);
extern u32 battle_getFlags(void);
