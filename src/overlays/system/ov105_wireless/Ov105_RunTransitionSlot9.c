#include "nitro/types.h"
#include "nitro/wm.h"

extern WMErrCode Ov105_WMi_CheckStateEx(s32 paramNum, ...);
extern void Ov105_SetCommandArg(int slot, int arg);
extern WMErrCode Ov105_WMi_SendCommand(WMApiid id, u16 paramNum, ...);
/* Same transition shape as 020bda94, driving stage 7 into slot 9. */
int Ov105_RunTransitionSlot9(int arg) {
    int r = Ov105_WMi_CheckStateEx(1, 7);
    if (r != 0) {
        return r;
    }
    Ov105_SetCommandArg(9, arg);
    r = Ov105_WMi_SendCommand(9, 0);
    if (r == 0) {
        r = 2;
    }
    return r;
}
