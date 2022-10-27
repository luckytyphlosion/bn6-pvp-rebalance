#include "gba/types.h"
#include "symbols.h"

#include "AIData.h"
#include "BattleObject.h"
#include "BattleSettings.h"
#include "BattleState.h"
#include "CollisionData.h"
#include "Joypad.h"
#include "NaviStats.h"
#include "PanelData.h"

extern void CopyWords(void * src, void * dest, u32 size);
extern void ZeroFillByWord(void * src, u32 size);

u32 ZeroOutShopData (void) {
    ZeroFillByWord(eToolkit_ShopData, sizeof(eToolkit_ShopData));
    return 0;
}
