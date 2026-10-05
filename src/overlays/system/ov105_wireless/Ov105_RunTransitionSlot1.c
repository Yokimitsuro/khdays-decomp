#include "nitro/types.h"
#include "nitro/wm.h"

extern int Ov105_PollDeviceStatus(void);
extern void Ov105_SetCommandArg(int slot, int arg);
extern WMErrCode Ov105_WMi_SendCommand(WMApiid id, u16 paramNum, ...);
/* Same transition shape as 020bda94, with an argument-less first stage, into slot 1. */
int Ov105_RunTransitionSlot1(int arg) {
    int r = Ov105_PollDeviceStatus();
    if (r != 0) {
        return r;
    }
    Ov105_SetCommandArg(1, arg);
    r = Ov105_WMi_SendCommand(1, 0);
    if (r == 0) {
        r = 2;
    }
    return r;
}
