/* Per-frame step of the charge: keep steering, and end it when the timer runs out.
 *
 * Re-runs the steering helper with the stored direction at ctx+0x28 -- note that direction
 * is passed BY VALUE.  The ROM's `ldm r1, {r1, r2, r3}` is not a bulk load of three
 * separate arguments, it is mwcc putting a 12-byte struct into r1-r3, which is what the
 * calling convention does with a Vec3.  Writing it as three int arguments compiles but
 * does not match.
 *
 * The state ends only when all three of the owner's nodes at +0x398 have gone idle (their
 * +0x38c cleared), the countdown at ctx[0x10] has been spent, and the steering helper's
 * own result is under 0x20000 -- i.e. everything has settled AND the target is close.
 * Otherwise it falls through to the keep-going tail, which re-aims at the tracked node and
 * pokes the owner with mode 3, unless the flag byte at ctx[1]+0xad says to stop.
 *
 * The node walk uses the displacement form, `(char *)*ctx + i * sizeof(int)` with +0x398
 * at the access, which is what keeps the ROM's `add r1, r3, r2, lsl #2`.  mwcc hoists the
 * `*ctx` load out of the loop by itself; doing it by hand is not needed.
 */
typedef struct { int x, y, z; } Vec3;

extern int func_ov148_020d0770(int *ctx, Vec3 v, int flag);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *dst);
extern void func_0203c634(int *self, int action, void *cb);
extern void func_ov107_020c9264(int owner, int mode, int arg);
extern void func_ov148_020d1230(void);

void func_ov148_020d114c(int *self) {
    int *ctx = (int *)self[1];
    int reach;
    int i;

    reach = func_ov148_020d0770(ctx, *(Vec3 *)((char *)ctx + 0x28), 1);

    for (i = 0; i < 3; i++) {
        if (*(int *)(*(int *)((char *)*ctx + i * sizeof(int) + 0x398) + 0x38c) != 0) {
            break;
        }
    }

    if (i >= 3) {
        ctx[0x10] = ctx[0x10] - *(int *)(self[0] + 0x2c);
        if (ctx[0x10] <= 0) {
            ctx[0x10] = 0;
            if (reach < 0x20000) {
                *(int *)(*ctx + 0x3e8) = 0;
                func_0203c634(self, *(signed char *)((char *)self + 0x20), &func_ov148_020d1230);
                return;
            }
        }
    }

    if (*(unsigned char *)(ctx[1] + 0xad) != 0) {
        return;
    }
    if (*(int *)(*ctx + 0x394) != 0) {
        VEC_Subtract((const Vec3 *)(*(int *)(*ctx + 0x394) + 0x190), (const Vec3 *)ctx[3],
                     (Vec3 *)((char *)ctx + 0x28));
    }
    func_ov107_020c9264(*ctx, 3, 0);
}
