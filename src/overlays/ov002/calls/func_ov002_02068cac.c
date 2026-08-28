/*
 * The session screen's resume state: what a committed choice of kind two
 * enters, and what hands the screen back to its per-frame tick.
 *
 * The pending slot request is withdrawn, and while a slot token is still held
 * the screen leaves its blanked state and drops the busy flag. A completion
 * hook, if one was queued, is taken along with its argument, both slots are
 * cleared before it runs so it can queue another, and only then is it called.
 *
 * The last gate pokes the global byte the shop path watches. It fires outright
 * on the boot-mode flag, and otherwise only while the link is idle: the entry's
 * flag word must not carry bit twenty-eight, the first poll must come back
 * clear, and the second must come back positive.
 *
 * Finally the armed bit the committed-choice state set is cleared and the tick
 * is returned as the next state.
 *
 * The last gate's zero argument is held in nEntry rather than written as a
 * literal, because the ROM materialises it before testing the flag word; the
 * pragma is what keeps that store, which is otherwise propagated into the call
 * and dropped.  Ov002_StepSessionEvent needs the same pair for the same reason.
 *
 * THUMB.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Ov002SessionScreen {
    char pad0000[0x8b44];
    void (*pCallback)(int);
    int nCallbackArg;
    char pad8b4c[0x1c];
    u8 nMask;
    char pad8b69[0x63];
    int nSlotToken;
} Ov002SessionScreen;

extern u8 data_0204be04;
extern u8 data_0204c240;

extern Ov002SessionScreen *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov002_0206aae4(int a, int b);
extern void func_ov002_0206eaf8(void);
extern void func_ov002_0206f514(int a);
extern int *func_01fffde0(int a);
extern int func_ov022_020886d0(int a);
extern int func_ov022_020882e0(int a);
extern void func_02020878(int a);
extern void func_ov002_02068118(void);

#pragma opt_propagation off
void *func_ov002_02068cac(void)
{
    Ov002SessionScreen *pSess;
    void (*pCallback)(int);
    int nArg;
    int nFlags;
    int nEntry;

    pSess = NNSi_FndGetCurrentRootHeap();
    if (data_0204be04 != 0) {
        return 0;
    }

    func_ov002_0206aae4(0, 0);
    if (pSess->nSlotToken != -1) {
        func_ov002_0206eaf8();
        func_ov002_0206f514(0);
    }

    pCallback = pSess->pCallback;
    if (pCallback != 0) {
        nArg = pSess->nCallbackArg;
        pSess->pCallback = 0;
        pSess->nCallbackArg = 0;
        pCallback(nArg);
    }

    if ((data_0204c240 & 4) != 0
        || ((nFlags = func_01fffde0(0)[281], nEntry = 0,
             nFlags & 0x10000000) == 0
            && func_ov022_020886d0(nEntry) == 0
            && func_ov022_020882e0(0) > 0)) {
        func_02020878(1);
    }

    pSess->nMask &= ~0x20;
    return func_ov002_02068118;
}
#pragma opt_propagation on
