struct S2 {
    short pad0;     /* 0 */
    unsigned short h6; /* will use byte offset 6 instead */
    int padc;       /* placeholder */
};

void func_020191e0(int *out, void *pp, int v) {
    void *base = ((void **)pp)[2];   /* p->f8 at offset 8 */
    int t = ((int *)pp)[0];          /* p->f0 at offset 0 */
    unsigned short hv = *(unsigned short *)((char *)base + 6);
    int idx = (t >> 12) * (int)hv + v;
    int *arr = (int *)((char *)base + 0xc);
    *out = arr[(unsigned)idx >> 5] & (1 << (idx & 0x1f));
}
