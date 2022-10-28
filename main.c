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
#include "TrainingModeInfo.h"

#include "xoshiro128pp.h"

extern void CopyWords(void * src, void * dest, u32 size);
extern void ZeroFillByWord(void * src, u32 size);
extern bool32 battle_isPaused(void);
extern void PlaySoundEffect(u32 soundEffect);
extern u32 GetRNG1(void);
extern u32 GetRNG2(void);

void SetOpponentFormCheckpointStoreBattleObjectAndPlayConfirmSound(u8 chosenForm);
void CopyNaviStats1ToBattleNaviStats1(void);
void SetTrainingModeRNG(void);
bool32 ShouldOverrideOpponentTransferBuffer(void);
u8 DecayRandom1in4(void);

u32 ZeroOutShopData (void) {
    ZeroFillByWord(eToolkit_ShopData, sizeof(eToolkit_ShopData));
    return 0;
}

u32 OnAfterBattleInit_C (void) {
    SetTrainingModeRNG();
    CopyNaviStats1ToBattleNaviStats1();
    if (eTrainingModeConfig.mode == 1) {
        eBattleNaviStats[1].charge = 4;
    }
}

void SetTrainingModeRNG (void) {
    SeedXoshiro128ppRNG(GetRNG1(), GetRNG2());
}

void CopyNaviStats1ToBattleNaviStats1 (void) {
    CopyWords(&eNaviStats[0], &eBattleNaviStats[1], sizeof(struct NaviStats));
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
        playerAndOpponentInput = dTrainingModeInfos[eTrainingModeConfig.mode].inputCallback();
    } else {
        playerAndOpponentInput.playerInput = eJoypad.held;
        playerAndOpponentInput.opponentInput = JOYPAD_DEFAULT;
    }
    eSimulatedOpponent.joypadHeld = playerAndOpponentInput.opponentInput;
    return playerAndOpponentInput.playerInput;
}

struct PlayerAndOpponentInput FrameData_InputCallback (void) {
    struct PlayerAndOpponentInput playerAndOpponentInput;

    u16 joypadHeld = eJoypad.held;
    if (joypadHeld & JOYPAD_SELECT) {
        if (joypadHeld & JOYPAD_L) {
            eT1BattleObject0.hp = eT1BattleObject0.maxHP;
            eT1BattleObject1.hp = eT1BattleObject1.maxHP;
            playerAndOpponentInput.playerInput = JOYPAD_DEFAULT;
            playerAndOpponentInput.opponentInput = JOYPAD_DEFAULT;
        } else {
            joypadHeld &= ~JOYPAD_SELECT;
            // lazy invert
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

    return playerAndOpponentInput;
}

void GenericOpponent_SetAction (struct GenericOpponentState * oppState, u8 newAction, u8 runAction) {
    oppState->curAction = newAction;
    oppState->runAction = runAction;
    oppState->changedAction = TRUE;
    oppState->actionState = 0;
}

void GenericOpponent_SetActionState (struct GenericOpponentState * oppState, u8 newActionState) {
    oppState->actionState = newActionState;
}

void GenericOpponent_AddStickyInput (struct GenericOpponentState * oppState, u16 input) {
    oppState->stickyInput |= input;
}

void GenericOpponent_RemoveStickyInput (struct GenericOpponentState * oppState, u16 input) {
    oppState->stickyInput &= ~input;
}

bool32 GenericOpponent_IsMoving (void) {
    return eT1BattleObject1.curAction == 0x10;
}

bool32 GenericOpponent_IsAttacking (void) {
    return eT1BattleObject1.curAction > 0x10;
}

bool32 GenericOpponent_IsDeleted (void) {
    return eT1BattleObject1.curAction == 0x2;
}

bool32 GenericOpponent_IsFlinchingParalyzedPushedFreezedOrBubbled (void) {
    return eT1BattleObject1.curAction >= 0x3 && eT1BattleObject1.curAction <= 0x7;
}

struct PlayerAndOpponentInput GenericOpponent_HandleInput (struct GenericOpponentInfo * oppInfo) {
    struct PlayerAndOpponentInput playerAndOpponentInput;
    struct GenericOpponentState * oppState = &eSimulatedOpponent.oppState;

    if (GenericOpponent_IsDeleted()) {
        playerAndOpponentInput.opponentInput = JOYPAD_DEFAULT;
    } else {
        do {
            oppState->runAction = FALSE;
            oppState->input = 0;
            if (oppState->curAction == ACTION_MAIN) {
                oppInfo->decideActionMainCallback(oppInfo);
            } else if (oppState->curAction == ACTION_WAIT_MOVEMENT) {
                switch (oppState->actionState) {
                default:
                case STATE_WAIT_MOVEMENT_WAIT_MOVEMENT_START:
                    if (GenericOpponent_IsMoving() || GenericOpponent_IsFlinchingParalyzedPushedFreezedOrBubbled()) {
                        GenericOpponent_RemoveStickyInput(oppState, JOYPAD_ARROWS);
                        GenericOpponent_SetActionState(oppState, STATE_WAIT_MOVEMENT_WAIT_MOVEMENT_FINISH);
                    }
                    break;
                case STATE_WAIT_MOVEMENT_WAIT_MOVEMENT_FINISH:
                    if (!GenericOpponent_IsMoving()) {
                        GenericOpponent_SetAction(oppState, ACTION_MAIN, TRUE);
                    }
                    break;
                }
            } else if (oppState->curAction == ACTION_WAIT_ATTACK) {
                switch (oppState->actionState) {
                default:
                case STATE_WAIT_MOVEMENT_WAIT_ATTACK_START:
                    if (GenericOpponent_IsAttacking() || GenericOpponent_IsFlinchingParalyzedPushedFreezedOrBubbled()) {
                        GenericOpponent_SetActionState(oppState, STATE_WAIT_MOVEMENT_WAIT_ATTACK_FINISH);
                    }
                    break;
                case STATE_WAIT_MOVEMENT_WAIT_ATTACK_FINISH:
                    if (!GenericOpponent_IsAttacking()) {
                        GenericOpponent_SetAction(oppState, ACTION_MAIN, TRUE);
                    }
                    break;
                }
            }
            playerAndOpponentInput.opponentInput = oppState->stickyInput | oppState->input | JOYPAD_DEFAULT;
            oppState->changedAction = FALSE;
        } while (oppState->runAction);
    }

    playerAndOpponentInput.playerInput = eJoypad.held;
    return playerAndOpponentInput;
}

void ElecCrossDodging_DecideActionMain (struct GenericOpponentInfo * oppInfo) {
    struct GenericOpponentState * oppState = &eSimulatedOpponent.oppState;

    if (oppState->randomSteps == 0) {
        oppState->randomSteps = DecayRandom1in4() + 6;
        GenericOpponent_AddStickyInput(oppState, JOYPAD_B);
    }

    if (--oppState->randomSteps == 0) {
        GenericOpponent_RemoveStickyInput(oppState, JOYPAD_B);
        GenericOpponent_SetAction(oppState, ACTION_WAIT_ATTACK, FALSE);
    } else {
        u8 playerPanelY = eT1BattleObject0.panelY;
        u8 oppPanelY = eT1BattleObject1.panelY;
        u16 moveDirection;
        if (playerPanelY < oppPanelY) {
            moveDirection = JOYPAD_UP;
        } else if (playerPanelY > oppPanelY) {
            moveDirection = JOYPAD_DOWN;
        } else {
            if (oppPanelY == 1) {
                moveDirection = JOYPAD_DOWN;
            } else if (oppPanelY == 3) {
                moveDirection = JOYPAD_UP;
            } else {
                moveDirection = (RNGNextIntBounded(2) == 1) ? JOYPAD_DOWN : JOYPAD_UP;
            }
        }
        GenericOpponent_AddStickyInput(oppState, moveDirection);
        GenericOpponent_SetAction(oppState, ACTION_WAIT_MOVEMENT, FALSE);
    }
}

struct PlayerAndOpponentInput ElecCrossDodging_InputCallback (void) {
    return GenericOpponent_HandleInput(&dElecCrossDodgingInfo);
}

u8 ElecCrossDodging_CustConfirmCallback (void) {
    if (!eSimulatedOpponent.inCross) {
        eSimulatedOpponent.inCross = TRUE;
        return CROSS_ELEC;
    } else {
        return 0xff;
    }
}

u8 DecayRandom1in4 (void) {
    u8 count = 0;

    while (TRUE) {
        if (RNGNextIntBounded(4) == 2) {
            break;
        }
        count++;
        if (count == 255) {
            break;
        }
    }
    return count;
}

u8 FrameData_CustConfirmCallback (void) {
    return 0xff;
}

void OnCustMenuConfirm_C (void) {
    u8 chosenForm = dTrainingModeInfos[eTrainingModeConfig.mode].custConfirmCallback();
    SetOpponentFormCheckpointStoreBattleObjectAndPlayConfirmSound(chosenForm);
}

void SetOpponentFormCheckpointStoreBattleObjectAndPlayConfirmSound (u8 chosenForm) {
    byte_203F658.chosenForm = chosenForm;
    byte_203F658.unk_04 = 0xff;
    byte_203F658.unkBattleObjectPtr = &eT1BattleObject1;
    dword_203F5A0 = CHECKPOINT_VALUE_1;
    PlaySoundEffect(SOUND_SELECT_82);
}
