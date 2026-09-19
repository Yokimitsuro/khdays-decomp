/* Consume the pending pose request (+0x1c7 of the actor): when one is queued (!= -1) it becomes
 * the current kind (+0x1c6), flag 2 is raised and flags 0x84 cleared in the high byte at +0x60,
 * and kind 0 / 2 dispatch slot 1 to 020d1d8c / 020d1e40; the request is then cleared to -1. */
typedef unsigned short u16;
extern void func_0203c634(int self, int index, void *cb);
extern void func_ov273_020d59cc(void);
extern void func_ov273_020d5a80(void);

void func_ov273_020d58d4(int self) {
    int obj = *(int *)(self + 4);
    signed char kind = *(signed char *)(*(int *)obj + 0x100 + 0xc7);
    if (kind != -1) {
        *(signed char *)(*(int *)obj + 0x1c6) = kind;
        {
            unsigned short *p = (unsigned short *)(*(int *)obj + 0x60);
            unsigned int hi = ((unsigned int)*p << 0x10) >> 0x18;
            hi |= 2;
            *p = (unsigned short)((*p & ~0xff00) | ((hi << 0x18) >> 16));
        }
        {
            int actor = *(int *)obj;
            u16 hw = *(u16 *)(actor + 0x60);
            *(u16 *)(actor + 0x60) = (hw & ~0xff00) |
                (((unsigned int)(unsigned short)((((unsigned int)hw << 0x10) >> 0x18) & ~0x84) << 0x18) >> 0x10);
        }
        switch (*(signed char *)(*(int *)obj + 0x100 + 0xc6)) {
        case 0:
            func_0203c634(self, 1, &func_ov273_020d59cc);
            break;
        case 2:
            func_0203c634(self, 1, &func_ov273_020d5a80);
            break;
        }
    }
    *(signed char *)(*(int *)obj + 0x1c7) = -1;
}
