typedef unsigned char u8;
typedef signed char s8;

typedef struct Ov002Slot {
    u8 pad0000[4];
    void (*pfnClose)(struct Ov002Slot *pSlot);  /* +0x04 */
    u8 pad0008[9];
    s8 nState;                                  /* +0x11 */
} Ov002Slot;

extern int data_ov002_0207fa04;

extern void func_ov002_0206f6e4(int nArg, int nState);
extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern void func_ov002_0206ea04(int nHandle);

void func_ov002_0206e99c(int id) {
    int base = data_ov002_0207fa04;
    int bAlt = 0;
    Ov002Slot *pSlot;
    int nAux;

    if (id & 0x1000) {
        base += 0x12c;
        bAlt = 1;
        id &= ~0x1000;
    } else {
        base += 0xc;
    }

    pSlot = ((Ov002Slot **)base)[id];
    if (pSlot != 0) {
        if (pSlot->pfnClose != 0) {
            pSlot->pfnClose(pSlot);
        }
        if (bAlt == 0 && pSlot->nState >= 0) {
            func_ov002_0206f6e4(0, pSlot->nState);
        }
        NNSi_FndFreeFromDefaultHeap(pSlot);
        ((Ov002Slot **)base)[id] = 0;
    }

    base += 0x80;
    nAux = ((int *)base)[id];
    if (nAux != 0) {
        func_ov002_0206ea04(nAux);
        ((int *)base)[id] = 0;
    }
}
