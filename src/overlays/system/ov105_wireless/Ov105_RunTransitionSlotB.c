#include "nitro/types.h"
#include "nitro/wm.h"

extern WMErrCode Ov105_WMi_CheckStateEx(s32 paramNum, ...);
extern void Ov105_SetCommandArg(int slot, int arg);
extern WMErrCode Ov105_WMi_SendCommand(WMApiid id, u16 paramNum, ...);
/* Run phase 1->2 of the transition: bail out with the first stage's code if it is busy, else
 * arm slot 2 and report its status (0 meaning "still running" is reported as 2). */
int Ov105_RunTransitionSlotB(int arg) {
    int r = Ov105_WMi_CheckStateEx(1, 5);
    if (r != 0) {
        return r;
    }
    Ov105_SetCommandArg(0xb, arg);
    r = Ov105_WMi_SendCommand(0xb, 0);
    if (r == 0) {
        r = 2;
    }
    return r;
}
