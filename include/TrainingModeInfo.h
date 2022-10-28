#pragma once

#include "PlayerAndOpponentInput.h"
#include "SimulatedOpponent.h"

struct TrainingModeInfo {
    struct PlayerAndOpponentInput (*inputCallback)(void);
    u8 (*custConfirmCallback)(void);
};

struct GenericOpponentInfo {
    void (*decideActionMainCallback)(struct GenericOpponentInfo *);
};

struct PlayerAndOpponentInput FrameData_InputCallback(void);
u8 FrameData_CustConfirmCallback(void);

struct PlayerAndOpponentInput ElecCrossDodging_InputCallback(void);
u8 ElecCrossDodging_CustConfirmCallback(void);

void ElecCrossDodging_DecideActionMain(struct GenericOpponentInfo * oppInfo);

extern struct TrainingModeInfo dTrainingModeInfos[];
extern struct GenericOpponentInfo dElecCrossDodgingInfo;
