struct bf { unsigned b : 8; };
extern void func_0203c634(int obj, int idx, void *cb, int flag);
extern void func_ov287_020d0728(void);

void func_ov287_020d06b4(int this_) {
    int *state = *(int **)(this_ + 4);
    {
        unsigned short *p = (unsigned short *)(*state + 0x60);
        unsigned int u = *p;
        *p = (unsigned short)((u & ~0xff00) | ((((u << 0x10) >> 0x18 | 0x80) << 0x18) >> 0x10));
    }
    ((struct bf *)(*(int *)(*state + 0x388) + 8))->b &= ~1;
    *(int *)(*state + 0x394) = 0;
    func_0203c634(this_, *(signed char *)(this_ + 0x20), func_ov287_020d0728, 0);
}
