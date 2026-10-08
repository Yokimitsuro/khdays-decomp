/* Sends or applies the pending message according to the session mode, then clears it; returns 1
 * when there was one. */

#include "nitro/types.h"
#include "nitro/wm.h"

typedef struct AsyncMessage {
    int active00;
    void *data04;
    u16 size08;
} AsyncMessage;

extern int Session_GetLinkMode(void);
extern u16 GetGlobalU16At4(void);
extern void AsyncMessage_OnSendDone(void *arg);
extern WMErrCode Ov105_WM_SetMPDataToPortEx(WMCallbackFunc callback, void *arg, const u16 *sendData, u16 sendDataSize, u16 destBitmap, u16 port, u16 prio);
extern void AsyncMessage_FlushHookNoOp(void);
extern void dispatchByObjTypeBits(void *data, int size);

int AsyncMessage_Flush(AsyncMessage *message)
{
    int result;

    if (message->size08 == 0) {
        return 0;
    }

    switch (Session_GetLinkMode()) {
    case 2:
        message->active00 = 1;
        result = Ov105_WM_SetMPDataToPortEx(AsyncMessage_OnSendDone, message,
                                    message->data04, message->size08,
                                    (u16)(GetGlobalU16At4() & 0xfffe), 12, 0);
        if (result != 2) {
            AsyncMessage_FlushHookNoOp();
        }
        dispatchByObjTypeBits(message->data04, message->size08);
        break;
    case 1:
        dispatchByObjTypeBits(message->data04, message->size08);
        break;
    case 3:
        message->active00 = 1;
        result = Ov105_WM_SetMPDataToPortEx(AsyncMessage_OnSendDone, message,
                                    message->data04, message->size08,
                                    0, 12, 0);
        if (result != 2) {
            AsyncMessage_FlushHookNoOp();
        }
        break;
    }

    message->size08 = 0;
    return 1;
}
