#include "nitro/types.h"
#include "nitro/wm.h"

extern WMErrCode Ov105_WMi_CheckStateEx(s32 paramNum, ...);
extern void Ov105_WMi_SetCallbackTable(int slot, int arg);
extern WMErrCode Ov105_WMi_SendCommand(WMApiid id, u16 paramNum, ...);
/* WM_EndScan (NitroSDK): request WM_APIID_END_SCAN (0xb) in WM_STATE_SCAN. */
int Ov105_WM_EndScan(int arg) {
    int r = Ov105_WMi_CheckStateEx(1, 5);
    if (r != 0) {
        return r;
    }
    Ov105_WMi_SetCallbackTable(0xb, arg);
    r = Ov105_WMi_SendCommand(0xb, 0);
    if (r == 0) {
        r = 2;
    }
    return r;
}
