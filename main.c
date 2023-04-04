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
#include "BattleHand.h"

#include "xoshiro128pp.h"

extern void CopyWords(void * src, void * dest, u32 size);
extern void ZeroFillByWord(void * src, u32 size);
extern bool32 battle_isPaused(void);
extern void PlaySoundEffect(u32 soundEffect);
extern u32 GetRNG1(void);
extern u32 GetRNG2(void);
extern bool32 battle_isTimeStop(void);
extern bool32 TestEventFlag_CBind(u16 eventFlag);
extern void sprite_forceWhitePalette_CBind(struct BattleObject * obj);
extern void sprite_clearFinalPalette_CBind(struct BattleObject * obj);
extern void sprite_setFinalPalette_CBind(struct BattleObject * obj, u8 palette);
extern void sprite_setColorShader_CBind(struct BattleObject * obj, u16 colorShader);
extern void sprite_zeroColorShader_CBind(struct BattleObject * obj);
extern u32 battle_getFlags(void);

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

void CopyHandBuffersToPlayers (void) {
    if ((eTrainingModeConfig.mode == 0 && !(eJoypad.held & JOYPAD_L)) || eTrainingModeConfig.mode != 0) {
        if (ePlayerBattleHandSource_203F4A4.curChipIndex != 0xff) {
            CopyWords(&ePlayerBattleHandSource_203F4A4, &ePlayerBattleHand, 0x50);
        }
    }

    if (eTrainingModeConfig.mode == 0 && !(eJoypad.held & JOYPAD_R) && ePlayerBattleHandSource_203F4A4.curChipIndex != 0xff) {
        CopyWords(&ePlayerBattleHandSource_203F4A4, &eOpponentBattleHand, 0x50);
    }
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

bool32 CheckIfCustGaugeFullForBeastOver (void) {
    if (eTrainingModeConfig.mode == 0) {
        return FALSE;
    }

    if (battle_getFlags() & 0x12) {
        return TRUE;
    } else {
        return FALSE;
    }
}

struct PlayerAndOpponentInput FrameData_InputCallback (void) {
    struct PlayerAndOpponentInput playerAndOpponentInput;

    u16 joypadHeld = eJoypad.held;

    if (eJoypad.pressed & JOYPAD_SELECT) {
        eSimulatedOpponent.oppState.isControllingOpponent ^= TRUE;
    }

    if (eSimulatedOpponent.oppState.isControllingOpponent) {
        joypadHeld &= ~JOYPAD_SELECT;
        // lazy invert
        if (joypadHeld & JOYPAD_LEFT) {
            joypadHeld = (joypadHeld & ~JOYPAD_LEFT) | JOYPAD_RIGHT;
        } else if (joypadHeld & JOYPAD_RIGHT) {
            joypadHeld = (joypadHeld & ~JOYPAD_RIGHT) | JOYPAD_LEFT;
        }
        playerAndOpponentInput.playerInput = JOYPAD_DEFAULT;
        playerAndOpponentInput.opponentInput = joypadHeld;
    } else if ((joypadHeld & (JOYPAD_SELECT | JOYPAD_L)) == (JOYPAD_SELECT | JOYPAD_L)) {
        eT1BattleObject0.hp = eT1BattleObject0.maxHP;
        eT1BattleObject1.hp = eT1BattleObject1.maxHP;
        playerAndOpponentInput.playerInput = JOYPAD_DEFAULT;
        playerAndOpponentInput.opponentInput = JOYPAD_DEFAULT;
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

bool32 GenericOpponent_GiveChipAtSlot0 (u16 chip, u16 damage) {
    eOpponentBattleHand.curChipIndex = 0;
    eOpponentBattleHand.chips[0] = chip;
    eOpponentBattleHand.chips[1] = 0xffff;
    eOpponentBattleHand.damages[0] = damage;
}
    
struct PlayerAndOpponentInput GenericOpponent_HandleInput (struct GenericOpponentInfo * oppInfo) {
    struct PlayerAndOpponentInput playerAndOpponentInput;
    struct GenericOpponentState * oppState = &eSimulatedOpponent.oppState;

    if (GenericOpponent_IsDeleted()) {
        playerAndOpponentInput.opponentInput = JOYPAD_DEFAULT;
    } else {
        if (oppState->globalFrameCounter > 0) {
            oppState->globalFrameCounter--;
        }
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

enum BDTState {
    BDT_STATE_GIVE_BDT = 0,
    BDT_STATE_USE_BDT,
    BDT_STATE_MOVE_RIGHT,
    BDT_STATE_CHARGE_BDT,
    BDT_STATE_RELEASE_BDT
};

void BDTDodging_DecideActionMain (struct GenericOpponentInfo * oppInfo) {
    struct GenericOpponentState * oppState = &eSimulatedOpponent.oppState;

    switch (oppState->bdtState) {
    case BDT_STATE_GIVE_BDT:
        GenericOpponent_GiveChipAtSlot0(CHIP_BGDTHTHD, 0);
        oppState->bdtState = BDT_STATE_USE_BDT;
    case BDT_STATE_USE_BDT:
        GenericOpponent_AddStickyInput(oppState, JOYPAD_A);
        GenericOpponent_SetAction(oppState, ACTION_WAIT_ATTACK, FALSE);
        oppState->bdtState = BDT_STATE_MOVE_RIGHT;
        break;
    case BDT_STATE_MOVE_RIGHT:
        GenericOpponent_AddStickyInput(oppState, JOYPAD_RIGHT);
        GenericOpponent_SetAction(oppState, ACTION_WAIT_MOVEMENT, FALSE);
        oppState->bdtState = BDT_STATE_CHARGE_BDT;
    case BDT_STATE_CHARGE_BDT:
        GenericOpponent_AddStickyInput(oppState, JOYPAD_B);
        oppState->globalFrameCounter = 201;
        oppState->bdtState = BDT_STATE_RELEASE_BDT;
    case BDT_STATE_RELEASE_BDT:
        if (oppState->globalFrameCounter == 0) {
            GenericOpponent_RemoveStickyInput(oppState, JOYPAD_B);
            GenericOpponent_SetAction(oppState, ACTION_WAIT_ATTACK, FALSE);
            oppState->bdtState = BDT_STATE_CHARGE_BDT;
        } else {
            u8 playerPanelY = eT1BattleObject0.panelY;
            u8 oppPanelY = eT1BattleObject1.panelY;
            if (playerPanelY != oppPanelY) {
                u16 moveDirection;
                if (playerPanelY < oppPanelY) {
                    moveDirection = JOYPAD_UP;
                } else {
                    moveDirection = JOYPAD_DOWN;
                }
                GenericOpponent_AddStickyInput(oppState, moveDirection);
                GenericOpponent_SetAction(oppState, ACTION_WAIT_MOVEMENT, FALSE);
            }
        }
    }
}

struct PlayerAndOpponentInput BDTDodging_InputCallback (void) {
    return GenericOpponent_HandleInput(&dBDTDodgingInfo);
}

u8 BDTDodging_CustConfirmCallback (void) {
    return 0xff;
}

u8 FrameData_CustConfirmCallback (void) {
    u8 chosenForm = byte_203CED0.chosenForm;
    if (eJoypad.held & JOYPAD_B) {
        byte_203CED0.chosenForm = 0xff;
    } else if (eJoypad.held & JOYPAD_START) {
        chosenForm = 0xff;
    }

    return chosenForm;
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

void ChipLockoutCheck_C (struct AIData * aiData, struct BattleObject * obj) {
    bool32 chipLockoutFramesEnabled = TestEventFlag_CBind(EVENT_CHIP_LOCKOUT_FRAMES);
    if (aiData->chipLockoutTimer) {
        aiData->chipLockoutTimer--;
        if (chipLockoutFramesEnabled) {
            if (aiData->chipLockoutTimer) {
                sprite_setColorShader_CBind(obj, RGB(0, 31, 0));
            } else {
                sprite_zeroColorShader_CBind(obj);
            }
        }
    }
}
