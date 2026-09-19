/* Begins the swing: advances time, reacquires and aims at the target, then
 * starts animation 5 and installs the tick callback when the sub-node is idle.
 * The algebraic zero preserves the dependency needed for retail scheduling. */
extern int func_ov107_020cab14(int obj, int out);
extern void func_0203c634(int self, int idx, int cb);
extern void VEC_Subtract(void *a, void *b, void *d);
extern int func_020050b4(int x, int z);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c9ee8(int a, int b, int c);
extern int func_ov269_020d3930;

void func_ov269_020d382c(int *self) {
    int *state = (int *)self[1];
    int aim[3];
    int target;

    state[5] = *(int *)(*self + 0x2c) * 0x1e / 10;
    target = func_ov107_020cab14(*state, 0);
    state[2] = target;
    if (target != 0) {
        VEC_Subtract((void *)(target + 0x74), (void *)state[0x10], aim);
        state[4] = func_020050b4(aim[0], aim[2]);
    }
    state[0x15] += *(int *)(*self + 0x2c);
    if (*(unsigned char *)(state[1] + 0xad) == 0) {
        unsigned int u;
        func_ov107_020c9264(*state, 5, 0);
        func_ov107_020c9ee8(*(int *)(*state + 0x3d0), 1, 0);
        u = *(unsigned short *)(*state + 0x60);
        {
            unsigned int field = ((u << 16) >> 24) | 0x40;
            u &= ~(0xff00 | (field ^ field));
            field <<= 24;
            field = u | (field >> 16);
            *(unsigned short *)(*state + 0x60) = field;
        }
        state[0xc] = 0;
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov269_020d3930);
    }
}
