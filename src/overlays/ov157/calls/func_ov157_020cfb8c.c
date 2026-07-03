struct bf { unsigned b : 8; };
extern void func_ov157_020ce7e4(void *state, void *p);
extern long long func_01ff8a14(int a, int b);
extern void func_ov157_020ce8c8(void *state, int a, int b, void *p);
extern int func_02023eb4(int);
extern void func_0203c634(void *obj, int idx, void *value);

void func_ov157_020cfb8c(int *node) {
    int a = node[0];
    int *state = (int *)node[1];
    state[0xb] += *(int *)(a + 0x2c);
    if (*(unsigned char *)((char *)state + 0x38) == 0) {
        if (state[0xb] >= 0x4cc) {
            func_ov157_020ce7e4(state, (char *)state + 0x20);
            *(unsigned char *)((char *)state + 0x38) = 1;
        }
    } else if (*(unsigned char *)((char *)state + 0x38) == 1) {
        if (state[0xb] >= 0x911) {
            ((struct bf *)(*(int *)(*state + 0x38c) + 8))->b |= 1;
        }
    }
    if (state[0xb] >= 0x4cc && state[0xb] <= 0xbba) {
        long long res = func_01ff8a14(state[0xb] - 0x4cc, 0x6ee);
        func_ov157_020ce8c8(state, (int)res, (int)(res >> 32), (char *)state + 0x20);
    }
    if (*(unsigned char *)state[1] == 0) {
        int lo, hi, d;
        *(signed char *)(*state + 0x1c7) = 2;
        lo = *(int *)(*state + 0x224);
        hi = *(int *)(*state + 0x228);
        d = hi - lo;
        if (d < 0) d = -d;
        state[0xd] = lo + func_02023eb4(d + 1);
        func_0203c634(node, *(signed char *)(node + 8), (void *)0);
    }
}
