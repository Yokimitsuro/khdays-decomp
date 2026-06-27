extern void *func_0201f3d8(int a, int b);
extern int func_0201ef9c(int a, int b);
extern void func_0201f924(void *dst, int src);
extern int OS_IsThreadAvailable_0x02023650(void);

extern int data_0204bbfc[];

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
    Slot_0201f510 *p = (Slot_0201f510 *)func_0201f3d8(a, b);
    int v;

    if (p->s0 != 0) {
        p->s0++;
        data_0204bbfc[0x14 / 4] = 0;
        return p;
    }

    v = data_0204bbfc[0x14 / 4];
    if (v == 0) {
        v = OS_IsThreadAvailable_0x02023650();
    }
    p->w8 = v;
    p->wc = func_0201ef9c(a, b);
    if (a & 0x80000000) {
        p->w10 = a;
    } else {
        func_0201f924(&p->w10, a);
    }
    p->s0 = 1;
    p->s2 = 0;
    p->s4 = 0;
    p->s6 = (unsigned short)b;
    return p;
}
