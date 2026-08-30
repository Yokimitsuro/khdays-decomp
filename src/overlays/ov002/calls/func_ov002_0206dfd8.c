/* Ov002_UpdateLocalPeerReadyNotice (ARM).
 * The boolean conversion before the slot-bit test is present in the ROM.
 */
typedef struct Ov002RootContext {
    char pad0000[0x8c8b];
    unsigned char bPeerReadyMask;
} Ov002RootContext;

extern Ov002RootContext *data_ov002_0207fa00;
extern unsigned short func_01fffe14(void);
extern int func_ov002_0206b758(void);
extern int func_ov022_02088474(int nSlot);
extern int func_ov022_020886d0(int nSlot);
extern int func_ov002_02072754(int nSlot);
extern int func_ov002_020726dc(int nWidget);
extern int func_ov002_020726f4(int nWidget, int nState, int bRelayout);
extern int func_ov002_0207298c(void);
extern void func_ov002_0206adf8(int nFlags, int nLevel, int nReserved);

void func_ov002_0206dfd8(unsigned int nSlot, int bReady)
{
    Ov002RootContext *pRoot = data_ov002_0207fa00;
    int nWidget;
    int nLevel;
    if (nSlot != func_01fffe14())
        return;
    if (bReady == 1) {
        if ((pRoot->bPeerReadyMask != 0) & (1 << nSlot))
            return;
        pRoot->bPeerReadyMask |= 1 << nSlot;
        if (!func_ov002_0206b758())
            return;
        nLevel = 0;
        nWidget = func_ov022_02088474(nSlot);
        if (nWidget >= 0) {
            nWidget = func_ov002_02072754(nWidget);
            if (nWidget >= 0)
                nLevel = func_ov002_020726dc(nWidget);
        }
        func_ov002_0206adf8(func_ov002_0207298c(), nLevel, 0);
    } else {
        if ((pRoot->bPeerReadyMask == 0) & (1 << nSlot))
            return;
        pRoot->bPeerReadyMask &= ~(1 << nSlot);
        if (!func_ov002_0206b758())
            return;
        nWidget = func_ov002_02072754(func_ov022_02088474(func_01fffe14()));
        if (func_ov022_020886d0(func_01fffe14()))
            return;
        func_ov002_020726f4(nWidget, func_ov002_020726dc(nWidget), 1);
    }
}
