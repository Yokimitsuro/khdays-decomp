extern int func_ov276_020d0cf0();
extern void func_0203c634(void *obj, int idx, void *value);
extern void MTX_RotY33_();
extern void MTX_MultVec33();
extern short data_0203d210[];
void func_ov276_020d1b44(int *node) {
    int *state = (int *)node[1];
    if (func_ov276_020d0cf0(node) < 0) {
        func_0203c634(node, *(signed char *)(node + 8), 0);
        return;
    }
    if (*(unsigned char *)(state[1] + 0xad) == 0) {
        *(signed char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)(node + 8), 0);
        return;
    }
    if (state[0x17] == 0) {
        int mtx[9];
        int angle = (int)(((unsigned)(((long long)(int)(unsigned)state[0x10] * 0x28be60db9391LL +
                           0x80000000000LL) >> 0x20) << 4) >> 0x10) >> 4;
        MTX_RotY33_(mtx, (int)data_0203d210[angle * 2], (int)data_0203d210[angle * 2 + 1]);
        MTX_MultVec33(*(int *)(*state + 0x470) + 0x2c, mtx, state + 4);
    }
}
