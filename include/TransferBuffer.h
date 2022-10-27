#pragma once

struct TransferBuffer {
    u16 unk_00;
    u16 joypadHeld;
    u8 dataTransferOffset;
    u8 unk_05[11];
};

extern struct TransferBuffer unk_2039A00;
extern struct TransferBuffer eStruct2036780;

