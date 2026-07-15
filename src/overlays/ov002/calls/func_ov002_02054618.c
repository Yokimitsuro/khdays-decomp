/* Build a 0x30-byte tracker node: store param_2/param_4 into the header word, a Q-format
 * position from param_6/param_7 scaled by 0x82ea (64-bit multiply, >>6 across the split),
 * param_5, then allocate a param_4-entry index and fill it by resolving each u16 tag in
 * param_3 through func_ov002_020547e4. */
typedef unsigned short u16;
typedef unsigned char u8;
extern void *func_ov002_02053f8c(int a);
extern void MI_CpuFill8(void *dst, int val, unsigned int size);
extern void *NNSi_FndAllocFromDefaultExpHeap(unsigned int size);
extern int func_ov002_020547e4(int a, unsigned int tag);
unsigned int *func_ov002_02054618(int param_1, u16 param_2, int param_3, int param_4,
                                  unsigned int param_5, unsigned int param_6, int param_7) {
    int i;
    unsigned int *n = (unsigned int *)func_ov002_02053f8c(param_1);
    unsigned long long prod;
    unsigned int hi;
    MI_CpuFill8(n, 0, 0x30);
    *(u16 *)n = param_2;
    prod = (unsigned long long)param_6 * 0x82ea;
    hi = param_7 * 0x82ea + (unsigned int)(prod >> 32);
    *(short *)((char *)n + 2) = (short)param_4;
    *(u16 *)((char *)n + 4) = 0;
    n[2] = param_5;
    n[3] = (hi << 26) | ((unsigned int)prod >> 6);
    n[4] = hi >> 6;
    n[5] = 0;
    n[6] = 0;
    n[0xb] = (unsigned int)NNSi_FndAllocFromDefaultExpHeap(param_4 << 2);
    *(u8 *)((char *)n + 0x24) |= 2;
    n[0xa] = 0x7fffffff;
    for (i = 0; i < param_4; i++) {
        ((int *)n[0xb])[i] = func_ov002_020547e4(param_1, ((u16 *)param_3)[i]);
    }
    return n;
}
