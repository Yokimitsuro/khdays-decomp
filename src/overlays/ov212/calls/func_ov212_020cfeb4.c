/* Fire the twin projectiles once the wind-up completes (x3: ov212/266/267).
 * Accumulate dt into the phase timer (ctx+0x40); once it reaches 0x1c28 and the
 * one-shot byte at ctx+0x5a is still clear, convert the cached heading (ctx+0x34,
 * Q12 radians) to a table index and build the unit direction {sin, 0, cos}. Launch
 * both barrels from it -- owner+0x5cc with +1 and owner+0x5d0 with -1, i.e. mirrored
 * about the heading -- then latch the one-shot. Once the actor is no longer held
 * (ctx[1]+0xad), publish slot 2 and advance.
 *
 * NOTE the extern for func_ov212_020d0a48 declares its 3rd parameter with its REAL
 * pointer type, and that is load-bearing: passing `(int)&v` through an `int` parameter
 * makes mwcc CSE the address into a callee-saved register and emit `mov r2, r5` at each
 * call site (+4B, plus r6 in the push list). With the pointer type it rematerialises
 * `add r2, sp, #0` per call, which is what the ROM does. The tree's own definition of
 * the callee spells that parameter `int b`; it matches there, but callers need the
 * pointer. See codegen-cracks.md. */
struct vec3 { int x, y, z; };

extern void func_ov212_020d0a48(int obj, int a, struct vec3 *v, int c);
extern void func_0203c634(void *self, int idx, void *cb);
extern short data_0203d210[];

void func_ov212_020cfeb4(void *self) {
    int *c0 = ((int **)self)[0];
    int *ctx = ((int **)self)[1];
    int t;

    t = ctx[0x10] + c0[0xb];
    ctx[0x10] = t;
    if (t >= 0x1c28 && *(unsigned char *)((char *)ctx + 0x5a) == 0) {
        struct vec3 v;
        unsigned int idx =
            (unsigned short)(((long long)ctx[0xd] * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4;
        v.x = data_0203d210[idx * 2];
        v.y = 0;
        v.z = data_0203d210[idx * 2 + 1];
        func_ov212_020d0a48(*(int *)(*ctx + 0x5cc), *ctx + 0x55c, &v, 1);
        func_ov212_020d0a48(*(int *)(*ctx + 0x5d0), *ctx + 0x55c, &v, -1);
        *(char *)((char *)ctx + 0x5a) = 1;
    }
    if (*(unsigned char *)(ctx[1] + 0xad) != 0) {
        return;
    }
    *(char *)(*ctx + 0x1c7) = 2;
    func_0203c634(self, *(signed char *)((char *)self + 0x20), 0);
}
