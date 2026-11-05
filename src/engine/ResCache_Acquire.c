/* Returns the cached slot for the file (adding a reference), or starts loading it into a new slot;
 * returns 1 when it was already cached. */

#include "game/engine.h"

extern void *ResCache_FindSlot(int a, int b);
extern int Loader_RequestFile(int a, int b);
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
} Slot_0201f468;

int ResCache_Acquire(int a, Slot_0201f468 **out, int c) {
    Slot_0201f468 *p = (Slot_0201f468 *)ResCache_FindSlot(a, (int)out);
    int v;

    if (p->s0 != 0) {
        p->s0++;
        *out = p;
        gFileLoader[0x14 / 4] = 0;
        return 1;
    }

    v = gFileLoader[0x14 / 4];
    if (v == 0) {
        v = (int)Heap_GetCurrent();
    }
    p->w8 = v;
    p->wc = Loader_RequestFile(a, c);
    if (a & 0x80000000) {
        p->w10 = a;
    } else {
        strcpy(&p->w10, a);
    }
    p->s0 = 1;
    p->s2 = 0;
    p->s4 = 0;
    p->s6 = (unsigned short)c;
    *out = p;
    return 0;
}
