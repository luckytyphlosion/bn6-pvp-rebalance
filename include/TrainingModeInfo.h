#pragma once

#include "PlayerAndOpponentInput.h"

struct TrainingModeInfo {
    struct PlayerAndOpponentInput (*inputCallback)(void);
    u8 (*custConfirmCallback)(void);
};

struct PlayerAndOpponentInput FrameData_InputCallback(void);
u8 FrameData_CustConfirmCallback(void);

extern struct TrainingModeInfo dTrainingModeInfos[];
