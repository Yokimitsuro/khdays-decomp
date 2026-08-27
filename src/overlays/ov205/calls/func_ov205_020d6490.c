extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern void func_ov107_020c9ee8(int a, int b, int c);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov205_020d6544(void);

void func_ov205_020d6490(int *node) {
    int *state = (int *)node[1];
    int thr = 0x111;
    if (*(unsigned char *)((char *)state + 0x45) == 0) {
        int t = state[0xb] + *(int *)(*node + 0x2c);
        state[0xb] = t;
        if (t >= thr) {
            *(unsigned char *)((char *)state + 0x45) = 1;
            func_ov107_020c5af8(*state, thr + 0x21, 6, state[9]);
        }
    }
    if (*(unsigned char *)state[10] != 0) return;
    func_ov107_020c9ee8(*(int *)(*state + 0x390), 5, 0);
    func_ov107_020c9264(*state, 0xe, 0);
    state[0xb] = 0;
    *((char *)state + 0x44) = 0;
    state[0x16] = 0;
    func_0203c634(node, *(signed char *)(node + 8), func_ov205_020d6544);
}
