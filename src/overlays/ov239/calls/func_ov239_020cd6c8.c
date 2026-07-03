struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_01ff9010();
extern void func_01ff93bc();
extern void func_0203c634(void *obj, int idx, void *value);
extern short data_0203d210[];
void func_ov239_020cd6c8(int *node) {
    int *state = (int *)node[1];
    int mtx[9];
    int angle = (int)(((unsigned)(((long long)(int)(unsigned)state[4] * 0x28be60db9391LL +
                       0x80000000000LL) >> 0x20) << 4) >> 0x10) >> 4;
    func_01ff9010(mtx, (int)data_0203d210[angle * 2], (int)data_0203d210[angle * 2 + 1]);
    func_01ff93bc(*(int *)(*state + 0x398) + 0x2c, mtx, state + 5);
    ((struct hw60 *)(*state + 0x60))->hi &= ~0x40;
    if (*(unsigned char *)(state[1] + 0xad) == 0) {
        *(signed char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)(node + 8), 0);
    }
}
