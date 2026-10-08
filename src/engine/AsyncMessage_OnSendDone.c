/* The send callback of AsyncMessage_Flush (WM_SetMPDataToPortEx's completion, its argument the
 * message): while the message queue exists, a message whose buffer is the one just sent is no
 * longer pending. */

#include "nitro/types.h"
#include "nitro/wm.h"

typedef struct AsyncMessage {
    int active00;               /* 0x00: sent, waiting for the completion */
    const void *data04;         /* 0x04 */
    u16 size08;                 /* 0x08 */
} AsyncMessage;

extern int gMsgQueue;

void AsyncMessage_OnSendDone(void *arg) {
    WMPortSendCallback *cb = (WMPortSendCallback *)arg;
    AsyncMessage *message;
    const u16 *sent;
    if (*(int *)&gMsgQueue == 0) return;
    message = (AsyncMessage *)cb->arg;
    sent = cb->data;
    if (message->data04 == sent) message->active00 = 0;
}
