extern int NNSi_FndFreeFromDefaultHeap();

struct S {
    char pad24[0x24];
    unsigned char flags;   /* 0x24 */
    char pad25[0x2c - 0x25];
    void *ptr;             /* 0x2c */
};

void func_ov002_020546e4(int a, struct S *s) {
    s->flags &= ~2;
    if (s->ptr != 0) {
        NNSi_FndFreeFromDefaultHeap(s->ptr);
        s->ptr = 0;
    }
}
