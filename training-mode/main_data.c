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
        .inputCallback = ElecCrossDodging_InputCallback,
        .custConfirmCallback = ElecCrossDodging_CustConfirmCallback
    },
    {
        .inputCallback = BDTDodging_InputCallback,
        .custConfirmCallback = BDTDodging_CustConfirmCallback
    }
};

struct GenericOpponentInfo dElecCrossDodgingInfo = {
    .decideActionMainCallback = ElecCrossDodging_DecideActionMain  
};

struct GenericOpponentInfo dBDTDodgingInfo = {
    .decideActionMainCallback = BDTDodging_DecideActionMain  
};
