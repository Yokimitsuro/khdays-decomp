#include "nitro/types.h"
#include "nitro/wm.h"

extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern int Ov105_WMi_CheckInitialized(void);
extern WMErrCode Ov105_WMi_CheckStateEx(s32 paramNum, ...);
extern void Ov105_ClearSharedRequestBit(void);
extern void PXI_SetFifoRecvCallback(int tag, void *callback);
extern char data_ov105_020bfa20;

/* Shuts the wireless stack down: refuses if a session is still up, otherwise unhooks the PXI
 * handler and clears the session slot. */
int Ov105_ShutdownWireless(void) {
    int enabled = OS_DisableInterrupts();
    int err;
    if (Ov105_WMi_CheckInitialized() != 0) {
        OS_RestoreInterrupts(enabled);
        return 3;
    }
    err = Ov105_WMi_CheckStateEx(1, 0);
    if (err != 0) {
        return err;
    }
    Ov105_ClearSharedRequestBit();
    PXI_SetFifoRecvCallback(0xa, 0);
    *(int *)((char *)&data_ov105_020bfa20 + 4) = 0;
    *(short *)&data_ov105_020bfa20 = 0;
    OS_RestoreInterrupts(enabled);
    return 0;
}
