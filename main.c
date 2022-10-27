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

#include "constants.h"

#include "CommBuffer203F658.h"
#include "CutsceneState.h"
#include "TrainingModeConfig.h"
#include "SimulatedOpponent.h"
#include "PlayerAndOpponentInput.h"
#include "TransferBuffer.h"

extern void CopyWords(void * src, void * dest, u32 size);
extern void ZeroFillByWord(void * src, u32 size);
extern bool32 battle_isPaused(void);
extern void PlaySoundEffect(u32 soundEffect);
extern void SetOpponentFormCheckpointStoreBattleObjectAndPlayConfirmSound(u8 chosenForm);

bool32 ShouldOverrideOpponentTransferBuffer(void);

u32 ZeroOutShopData (void) {
    ZeroFillByWord(eToolkit_ShopData, sizeof(eToolkit_ShopData));
    return 0;
}

u32 SaveChosenTrainingMode (void) {
    if (eCutsceneState.unk_04 != 0xff) {
        eTrainingModeConfig.mode = eCutsceneState.unk_04;
    }

    return 0;
}

void HookOpponentTransferBuffer (void) {
    if (ShouldOverrideOpponentTransferBuffer()) {
        unk_2039A00.joypadHeld = eSimulatedOpponent.joypadHeld;
        unk_2039A00.dataTransferOffset = 0xff;
    } else {
        CopyWords(&eStruct2036780, &unk_2039A00, sizeof(struct TransferBuffer));
    }
}

bool32 ShouldOverrideOpponentTransferBuffer(void) {
    return (eBattleState.unk_00 != 0 && eBattleState.unk_05 != 0);
}

// return player input
u16 HookPlayerAndOpponentInput_C (void) {
    struct PlayerAndOpponentInput playerAndOpponentInput;

    if (ShouldOverrideOpponentTransferBuffer() && !battle_isPaused()) {
        u16 joypadHeld = eJoypad.held;
        if (joypadHeld & JOYPAD_SELECT) {
            if (joypadHeld & JOYPAD_L) {
                eT1BattleObject0.hp = eT1BattleObject0.flags;
                eT1BattleObject1.hp = eT1BattleObject1.maxHP;
                playerAndOpponentInput.playerInput = JOYPAD_DEFAULT;
                playerAndOpponentInput.opponentInput = JOYPAD_DEFAULT;
            } else {
                joypadHeld &= ~JOYPAD_SELECT;
                if (joypadHeld & JOYPAD_LEFT) {
                    joypadHeld = (joypadHeld & ~JOYPAD_LEFT) | JOYPAD_RIGHT;
                } else if (joypadHeld & JOYPAD_RIGHT) {
                    joypadHeld = (joypadHeld & ~JOYPAD_RIGHT) | JOYPAD_LEFT;
                }
                playerAndOpponentInput.playerInput = JOYPAD_DEFAULT;
                playerAndOpponentInput.opponentInput = joypadHeld;
            }
        } else {
            playerAndOpponentInput.playerInput = joypadHeld;
            playerAndOpponentInput.opponentInput = JOYPAD_DEFAULT;
        }
    } else {
        playerAndOpponentInput.playerInput = eJoypad.held;
        playerAndOpponentInput.opponentInput = JOYPAD_DEFAULT;
    }
    eSimulatedOpponent.joypadHeld = playerAndOpponentInput.opponentInput;
    return playerAndOpponentInput.playerInput;
}

void OnCustMenuConfirm_C (void) {
    SetOpponentFormCheckpointStoreBattleObjectAndPlayConfirmSound(0xff);
}

void SetOpponentFormCheckpointStoreBattleObjectAndPlayConfirmSound (u8 chosenForm) {
    byte_203F658.chosenForm = chosenForm;
    byte_203F658.unk_04 = 0xff;
    byte_203F658.unkBattleObjectPtr = &eT1BattleObject1;
    dword_203F5A0 = CHECKPOINT_VALUE_1;
    PlaySoundEffect(SOUND_SELECT_82);
}
