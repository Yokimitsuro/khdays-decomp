struct Vec3_020cf740 { int x, y, z; };
extern const struct Vec3_020cf740 data_02041dc8;
extern void func_0203c634(int *a, int i, int v);
extern void func_ov283_020cf7d4(void);

struct node60_020cf740 { unsigned short lo : 8; unsigned short hi : 8; };

void func_ov283_020cf740(int param_1) {
    int child = *(int *)(param_1 + 4);

    *(int *)(*(int *)child + 0x388) = 0;

    {
        unsigned short *p = (unsigned short *)(*(int *)child + 0x60);
        unsigned int hi = ((unsigned int)*p << 0x10) >> 0x18;
        hi |= 0x80;
        *p = (unsigned short)((*p & ~0xff00) | ((hi << 0x18) >> 16));
    }
    ((struct node60_020cf740 *)(*(int *)child + 0x60))->hi &= ~1;

    *(struct Vec3_020cf740 *)(child + 8) = data_02041dc8;

    func_0203c634((int *)param_1, *(signed char *)(param_1 + 0x20), (int)&func_ov283_020cf7d4);
}
