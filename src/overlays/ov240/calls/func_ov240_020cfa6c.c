extern void VEC_Subtract();
extern int func_020050b4();
extern int func_01ff8d18();
extern void MTX_RotY33_();
extern void MTX_MultVec33();
extern void func_0203c634(void *obj, int idx, void *value);
extern short data_0203d210[];
void func_ov240_020cfa6c(int *node) {
    int *state = (int *)node[1];
    int buf[3];
    int mtx[9];
    int obj0, diff, angle;
    VEC_Subtract(*state + 0x190, state[2], buf);
    state[4] = func_020050b4(buf[0], buf[2]);
    obj0 = *state;
    diff = func_01ff8d18(buf, buf) - *(int *)(obj0 + 0x80);
    angle = (int)(((unsigned)(((long long)(int)(unsigned)state[4] * 0x28be60db9391LL +
                   0x80000000000LL) >> 0x20) << 4) >> 0x10) >> 4;
    MTX_RotY33_(mtx, (int)data_0203d210[angle * 2], (int)data_0203d210[angle * 2 + 1]);
    MTX_MultVec33(*(int *)(*state + 0x398) + 0x2c, mtx, state + 5);
    if (diff < 0x2000) {
        *(signed char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)(node + 8), 0);
    }
}
