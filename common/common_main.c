#include "gba/types.h"
#include "symbols.h"
#include "functions.h"

u32 ZeroOutShopData (void) {
    ZeroFillByWord(eToolkit_ShopData, sizeof(eToolkit_ShopData));
    return 0;
}
