#include "game/engine.h"

extern void *ResCache_FindSlot(int a, int b);
extern int Archive_LoadFile(int a, int b);
extern void strcpy(void *dst, int src);

extern int gFileLoader[];

typedef struct {
    unsigned short s0;
    unsigned short s2;
    unsigned short s4;
    unsigned short s6;
    int w8;
    int wc;
    int w10;
} Slot_0201f510;

void *SND_RegisterSeq(int a, int b) {
    Slot_0201f510 *p = (Slot_0201f510 *)ResCache_FindSlot(a, b);
    int v;

    if (p->s0 != 0) {
        p->s0++;
        gFileLoader[0x14 / 4] = 0;
        return p;
    }

    v = gFileLoader[0x14 / 4];
    if (v == 0) {
        v = (int)Heap_GetCurrent();
    }
    p->w8 = v;
    p->wc = Archive_LoadFile(a, b);
    if (a & 0x80000000) {
        p->w10 = a;
    } else {
        strcpy(&p->w10, a);
    }
    p->s0 = 1;
    p->s2 = 0;
    p->s4 = 0;
    p->s6 = (unsigned short)b;
    return p;
}
