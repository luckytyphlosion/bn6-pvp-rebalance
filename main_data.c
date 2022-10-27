#include "gba/types.h"
#include "TrainingModeInfo.h"

// hook for player and opp input
// hook for exiting cust menu

struct TrainingModeInfo dTrainingModeInfos[] = {
    {
        .inputCallback = FrameData_InputCallback,
        .custConfirmCallback = FrameData_CustConfirmCallback
    },
    {
        .inputCallback = FrameData_InputCallback,
        .custConfirmCallback = FrameData_CustConfirmCallback
    }
};
