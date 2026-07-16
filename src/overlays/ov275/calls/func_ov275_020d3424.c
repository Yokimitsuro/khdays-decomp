/* func_ov275_020d3424 -- accumulate time and, once past the threshold, re-face and hand on.
 * The elapsed counter at +0x24 always advances by the caller's per-tick amount (+0x2c of self[0])
 * and is always stored back; below 0x6ee that is all that happens.
 * Past it, the target is re-acquired and, if there is one, the bearing from the cached point
 * (+0x8) to the target's +0x74 is written to BOTH +0x40 and +0x44. Flags 0x82 are then cleared
 * from the high byte of the owner's +0x60 halfword, the owner is retuned (mode 0), and the action
 * dispatched with func_ov275_020d34ec.
 *
 * The +0x60 update uses the BITFIELD form on purpose, unlike func_ov206_020cd464's explicit
 * extract/reassemble. Both are in the ROM and they are not interchangeable: the bitfield form
 * emits a redundant `lsl #0x10 ; lsr #0x10` truncation, which this function HAS and 020cd464 does
 * not. Match the presence of that pair to pick the form -- see codegen-cracks.md. */

typedef struct {
    unsigned short lo : 8;
    unsigned short hi : 8;
} Hw60;

typedef struct {
    int x;
    int y;
    int z;
} Vec3;

extern int func_ov107_020cab14(int owner, int kind);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_020050b4(int x, int z);
extern void func_ov107_020c9264(int owner, int mode, int arg);
extern void func_0203c634(int self, int action, void (*cb)(void));
extern void func_ov275_020d34ec(void);

void func_ov275_020d3424(int self) {
    int *ctx;
    Vec3 v;
    int target;

    ctx = *(int **)(self + 4);
    ctx[9] = ctx[9] + *(int *)(*(int *)self + 0x2c);
    if (ctx[9] < 0x6ee) {
        return;
    }

    target = func_ov107_020cab14(ctx[0], 0);
    ctx[4] = target;
    if (target != 0) {
        VEC_Subtract((const Vec3 *)(target + 0x74), (const Vec3 *)ctx[2], &v);
        ctx[0x11] = func_020050b4(v.x, v.z);
        ctx[0x10] = ctx[0x11];
    }

    ((Hw60 *)(ctx[0] + 0x60))->hi &= ~0x82;
    func_ov107_020c9264(ctx[0], 0, 0);
    func_0203c634(self, *(signed char *)(self + 0x20), func_ov275_020d34ec);
}
