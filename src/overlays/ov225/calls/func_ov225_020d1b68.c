extern int func_0203c634();

typedef struct {
    unsigned short f : 8;
    unsigned short g : 8;
} Bits;

void func_ov225_020d1b68(int *r0) {
    int *r2 = (int *)r0[1];
    Bits *p = (Bits *)((char *)r2[0] + 0x60);
    int *q;
    if (!(p->f & 1)) return;
    *((char *)r2 + 0x74) = 6;
    *(int *)((char *)r2 + 0x78) = 1;
    q = (int *)r2[0];
    *((char *)q + 0x1c7) = *((signed char *)q + 0x1c9);
    func_0203c634(r0, *((signed char *)r0 + 0x20), 0, q);
}
