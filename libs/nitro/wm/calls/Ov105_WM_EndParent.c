#include "nitro/types.h"
#include "nitro/wm.h"

extern WMErrCode Ov105_WMi_CheckStateEx(s32 paramNum, ...);
extern void Ov105_WMi_SetCallbackTable(int slot, int arg);
extern WMErrCode Ov105_WMi_SendCommand(WMApiid id, u16 paramNum, ...);
/* WM_EndParent (NitroSDK): request WM_APIID_END_PARENT (9) in WM_STATE_PARENT. */
int Ov105_WM_EndParent(int arg) {
    int r = Ov105_WMi_CheckStateEx(1, 7);
    if (r != 0) {
        return r;
    }
    Ov105_WMi_SetCallbackTable(9, arg);
    r = Ov105_WMi_SendCommand(9, 0);
    if (r == 0) {
        r = 2;
    }
    return r;
}
