/* func_ov214_020cd8ac (x5 family: ov215/216/217/264/276) - NON-MATCHING.
 * Byte-exact except a 3-instruction register-coloring tie: the `a*2` trig index
 * temp lands in lr (mwcc) vs r7 (original) across lsl/lsl/add. Everything else -
 * negate-vec, normalize, fixed-angle(state[0x11], MAGIC64), trig dir from
 * data_0203d210, Vec3Scale, delegate guard - matches. The a*2 value is short-lived
 * (dead before the following calls); mwcc grabs the free lr while the original
 * reuses the just-freed r7 (held state[0x11]). Unsteerable coloring class; explicit
 * idx var did not move it. asm stub stays byte-exact via dsd. */
extern int func_ov107_020cab14(int a, int b);
extern void func_01ff8bc4(void *a, void *b, void *out);
extern int func_01ff8d18(void *a, void *b);
extern int func_020050b4(int x, int z);
extern int func_01ff8bf8(void *a, void *b);
extern void func_01ffa724(int scale, void *src, void *dst);
extern int func_ov214_020cd0e8(void *node, int arg);
extern void func_0203c634(void *node, int slot, void *cb);
extern short data_0203d210[];

void func_ov214_020cd8ac(int *node) {
    int *state = (int *)node[1];
    int target = func_ov107_020cab14(*state, 0);
    state[2] = target;
    if (target == 0) {
        *(signed char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)(node + 8), 0);
        return;
    }
    {
        int buf[3];
        int trig[3];
        int d;
        int a;
        func_01ff8bc4((void *)(target + 0x190), (void *)(*state + 0xb0), buf);
        buf[0] = -buf[0];
        buf[1] = 0;
        buf[2] = -buf[2];
        d = func_01ff8d18(buf, buf);
        state[0x13] = func_020050b4(buf[0], buf[2]);
        a = (int)(((unsigned)(((long long)state[0x11] * 0x28be60db9391LL
             + 0x80000000000LL) >> 0x20) << 4) >> 0x10) >> 4;
        trig[1] = 0;
        trig[0] = data_0203d210[a * 2];
        trig[2] = data_0203d210[a * 2 + 1];
        func_01ff8bf8(trig, buf);
        func_01ffa724(*(int *)(*state + 0x430), trig, state + 8);
        if (func_ov214_020cd0e8(node, d) == 0) return;
        func_0203c634(node, *(signed char *)(node + 8), 0);
    }
}
