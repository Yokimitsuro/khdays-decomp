extern void func_01ff8bc4();
extern int func_020050b4();
extern int func_01ff8d18();
extern void func_01ff9010();
extern void func_01ff93bc();
extern void func_0203c634(void *obj, int idx, void *value);
extern short data_0203d210[];
void func_ov240_020cfa6c(int *node) {
    int *state = (int *)node[1];
    int buf[3];
    int mtx[9];
    int obj0, diff, angle;
    func_01ff8bc4(*state + 0x190, state[2], buf);
    state[4] = func_020050b4(buf[0], buf[2]);
    obj0 = *state;
    diff = func_01ff8d18(buf, buf) - *(int *)(obj0 + 0x80);
    angle = (int)(((unsigned)(((long long)(int)(unsigned)state[4] * 0x28be60db9391LL +
                   0x80000000000LL) >> 0x20) << 4) >> 0x10) >> 4;
    func_01ff9010(mtx, (int)data_0203d210[angle * 2], (int)data_0203d210[angle * 2 + 1]);
    func_01ff93bc(*(int *)(*state + 0x398) + 0x2c, mtx, state + 5);
    if (diff < 0x2000) {
        *(signed char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)(node + 8), 0);
    }
}
