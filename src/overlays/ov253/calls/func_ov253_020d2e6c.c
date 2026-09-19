/* func_ov253_020d2e6c -- shrink tick: the +0x1c timer runs up and its 32.32 ratio over 0.125
 * (clamped to 1.0) drives the actor's +0x38c / +0x394 scale from 0.5 up to 1.0 and the +0x390
 * scale from 3.0 down to 1.0; once the ratio reaches 1.0 sub-state 2 is requested and the node
 * slot released. */
extern long long func_01ff8a14(int num, int den);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov253_020d2e6c(int *node) {
    int *state = (int *)node[1];
    long long q;

    state[7] += *(int *)(node[0] + 0x2c);
    q = func_01ff8a14(state[7], 0x200);
    if (q > 0x100000000LL) {
        q = 0x100000000LL;
    }
    *(int *)(*state + 0x38c) = (int)((q * 0x800LL + 0x80000000LL) >> 32) + 0x800;
    *(int *)(*state + 0x390) = (int)((q * -0x2000LL + 0x80000000LL) >> 32) + 0x3000;
    *(int *)(*state + 0x394) = (int)((q * 0x800LL + 0x80000000LL) >> 32) + 0x800;
    if (q < 0x100000000LL) {
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
