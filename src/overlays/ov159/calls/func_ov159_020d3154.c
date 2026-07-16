/* func_ov159_020d3154 -- face the target and arm the timed follow-up.
 * Without a target the owner drops to state 2 (+0x1c7) and the action is dispatched with no
 * continuation. With one, the offset from the reference point (+0x4c) to the target (+0x190) is
 * taken, FLATTENED to the ground plane (y forced to 0) and normalised, and its bearing cached at
 * +0x10. Flag 8 is set on the owner's +0x1ae halfword, the follow-up delay at +0x14 is computed
 * from the caller's per-tick amount, and the action is dispatched with func_ov159_020d322c.
 *
 * The delay is `x * 30 / 5` -- kept unfolded on purpose. mwcc emits mul #0x1e then the 0x66666667
 * magic with asr #1 (that shift is /5, not the /10 you get with asr #2); hand-folding it to `x * 6`
 * would change behaviour, since the x*30 intermediate can overflow. */

typedef struct {
    int x;
    int y;
    int z;
} Vec3;

extern int func_ov107_020cab14(int owner, int kind);
extern void func_0203c634(int self, int action, void (*cb)(void));
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int func_020050b4(int x, int z);
extern void func_ov159_020d322c(void);

void func_ov159_020d3154(int self) {
    int *ctx;
    Vec3 v;
    int target;

    ctx = *(int **)(self + 4);
    target = func_ov107_020cab14(ctx[0], 0);
    ctx[2] = target;
    if (target == 0) {
        *(unsigned char *)(ctx[0] + 0x1c7) = 2;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }

    VEC_Subtract((const Vec3 *)(target + 0x190), (const Vec3 *)ctx[0x13], &v);
    v.y = 0;
    func_01ff8d18(&v, &v);
    ctx[4] = func_020050b4(v.x, v.z);

    *(unsigned short *)(ctx[0] + 0x1ae) |= 8;
    ctx[5] = *(int *)(*(int *)self + 0x2c) * 30 / 5;
    func_0203c634(self, *(signed char *)(self + 0x20), func_ov159_020d322c);
}
