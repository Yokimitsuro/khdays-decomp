#include "nitro/types.h"
#include "nitro/wm.h"

extern int Ov105_WMi_CheckIdle(void);
extern void Ov105_WMi_SetCallbackTable(int slot, int arg);
extern WMErrCode Ov105_WMi_SendCommand(WMApiid id, u16 paramNum, ...);
/* WM_Reset (NitroSDK): request WM_APIID_RESET (1) once WM is idle (WMi_CheckIdle). */
int Ov105_WM_Reset(int arg) {
    int r = Ov105_WMi_CheckIdle();
    if (r != 0) {
        return r;
    }
    Ov105_WMi_SetCallbackTable(1, arg);
    r = Ov105_WMi_SendCommand(1, 0);
    if (r == 0) {
        r = 2;
    }
    return r;
}
