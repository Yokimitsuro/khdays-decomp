/*
 * The session screen's state once a slot choice has been committed.
 *
 * The peer mask is set to the armed value alone, the give-up poll is run, and
 * the screen's own sub-object is stepped. While that sub-object still has work
 * the state stays put; once it is done, the choice is dispatched.
 *
 * A choice of kind one plays its value out first and then falls into the same
 * ending as kind zero, which closes the screen and goes back to the idle state.
 * Kind two goes to the confirm state instead, and anything else stays put.
 *
 * Finally, a queued slot index is retired: if the retire is refused the state
 * stays put with no transition at all, and otherwise the index is cleared.
 *
 * Two things here are load-bearing rather than style.
 *
 * The next state is declared before the context pointer, which is what gives
 * each of them the register the original uses.
 *
 * Everything after the sub-object step is nested inside its success arm rather
 * than written after an early return, so the two exits that hand back the next
 * state share one epilogue the way the original does. Written as an early
 * return the compiler emits a second copy of it.
 *
 * THUMB.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Ov002SessionScreen {
    char pad0000[8];
    char sub0008[0x12c];
    int nChoiceKind;
    int nChoiceValue;
    char pad013c[0x8a1c];
    int nState;
    char pad8b5c[4];
    int nSlotIndex;
    char pad8b64[4];
    u8 nMask;
} Ov002SessionScreen;

extern u8 data_0204be04;

extern Ov002SessionScreen *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov002_0206a804(void);
extern int func_02020e58(void *pSub);
extern int func_ov022_02083f0c(void);
extern void func_ov002_0204cee0(int a, int b);
extern void func_ov002_02069540(void);
extern void func_ov002_0206ba28(int nValue);
extern void func_ov002_0206ed7c(void);
extern int func_ov002_0206efcc(int nSlot);
extern void func_ov002_02068d54(void);
extern void func_ov002_02068cac(void);

void *func_ov002_02068c0c(void)
{
    void *pNext;
    Ov002SessionScreen *pSess;

    pNext = 0;
    pSess = NNSi_FndGetCurrentRootHeap();
    if (data_0204be04 != 0) {
        return pNext;
    }

    pSess->nMask = 0x20;
    func_ov002_0206a804();
    if (func_02020e58(pSess->sub0008) == 0) {
        if (pSess->nState == 1) {
            func_ov002_0204cee0(func_ov022_02083f0c(), 0);
        }
        func_ov002_02069540();

        switch (pSess->nChoiceKind) {
        case 1:
            func_ov002_0206ba28(pSess->nChoiceValue);
            /* fall through */
        case 0:
            func_ov002_0206ed7c();
            pNext = func_ov002_02068d54;
            break;
        case 2:
            pNext = func_ov002_02068cac;
            break;
        }

        if (pSess->nSlotIndex >= 0) {
            if (func_ov002_0206efcc(pSess->nSlotIndex) == 0) {
                return 0;
            }
            pSess->nSlotIndex = -1;
        }
    }
    return pNext;
}
