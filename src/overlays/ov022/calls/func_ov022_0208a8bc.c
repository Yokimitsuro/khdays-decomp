extern void func_02014dc4(unsigned int *pool, int handle);
extern void func_0202accc(int anim, unsigned short slot, int block, short arg);
extern int *func_01fff774(unsigned short *anim, unsigned short slot, int frame);

void func_ov022_0208a8bc(int unused, int block, unsigned short *anim,
                         int bindingIndex) {
    unsigned int i = 0;

    do {
        if (((int *)anim)[i + 3] != 0) {
            func_02014dc4((unsigned int *)(anim + 0x10),
                          ((int *)anim)[i + 3]);
            ((int *)anim)[i + 3] = 0;
        }
        func_0202accc((int)anim, i, block, (short)bindingIndex);
        func_01fff774(anim, i, 0);
        i = i + 1;
    } while ((int)i < 5);
}
