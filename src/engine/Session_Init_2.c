/* Binds the session work, lays out the packet slots, clears the counters, installs the message
 * queue and the mode's send hook; returns the idle step. */

#include "nitro/types.h"

struct Foo {
    u32 _00;
    u32 _04;
    u32 _08;
    u32 arr[23];
    u32 _68;
    u32 _6c;
};

extern struct Foo *NNSi_FndGetCurrentRootHeap(void);
extern u32 Session_GetLinkMode(void);
extern void Session_LayoutPacketSlots(u32 linkMode);
extern void MsgQueue_Init(void);
extern int Ov105_WM_SetPortCallback(unsigned short port, void (*callback)(void *), void *arg);
extern void SubmitEntryIfActive(int arg0);
extern void DrawTileIfReady(int arg0);
extern void EffectList_StepIfIdle(void);

extern struct Foo *data_0204c22c;

void (*Session_Init_2(void))(void)
{
    struct Foo *p;
    u32 r;
    int i;

    p = NNSi_FndGetCurrentRootHeap();
    data_0204c22c = p;
    Session_LayoutPacketSlots(Session_GetLinkMode());
    p->_6c = 0;
    p->_68 = 0;
    for (i = 0; i < 20; i++) {
        p->arr[i] = 0;
    }
    MsgQueue_Init();
    r = Session_GetLinkMode();
    switch (r) {
    case 2:
        Ov105_WM_SetPortCallback(12, (void (*)(void *))SubmitEntryIfActive, 0);
        break;
    case 3:
        Ov105_WM_SetPortCallback(12, (void (*)(void *))DrawTileIfReady, 0);
        break;
    }
    p->_00 = 0;
    return EffectList_StepIfIdle;
}
