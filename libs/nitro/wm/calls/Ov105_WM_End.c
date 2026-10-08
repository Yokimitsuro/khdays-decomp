#include "nitro/types.h"
#include "nitro/wm.h"

extern WMErrCode Ov105_WMi_CheckStateEx(s32 paramNum, ...);
extern void Ov105_WMi_SetCallbackTable(int slot, int arg);
extern WMErrCode Ov105_WMi_SendCommand(WMApiid id, u16 paramNum, ...);
/* WM_End (NitroSDK): request WM_APIID_END (2) in WM_STATE_IDLE. */
int Ov105_WM_End(int arg) {
    int r = Ov105_WMi_CheckStateEx(1, 2);
    if (r != 0) {
        return r;
    }
    Ov105_WMi_SetCallbackTable(2, arg);
    r = Ov105_WMi_SendCommand(2, 0);
    if (r == 0) {
        r = 2;
    }
    return r;
}
