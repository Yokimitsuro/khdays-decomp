/* Per-frame tick of the ov102 panel: refreshes the sub-object at +0x2644 three times --
 * advance it by the frame delta, step it, then ask whether it has gone idle -- and when it
 * has, raises the 64-bit flag pairs at +0x464 and +0x46c, each guarded by its own check.
 * Finally republishes the pose.
 *
 * THE 64-BIT OR. The ROM's `orr rN, rN, #0` is not a no-op and not a macro artifact: it is
 * the HIGH HALF of a 64-bit OR on a pair of adjacent flag words. `*(long long *)(p) |= mask`
 * emits exactly two loads, `orr` low with the mask, `orr` high with zero, two stores. It also
 * explains the two-step base (`add r0, r4, #0x64` then `[r0, #0x404]`): that is just how mwcc
 * addresses the high half, not a separate source construct. */
extern int func_02030788(void);
extern int func_ov022_02083f90(void);
extern void func_ov022_0209145c(int a, int b);
extern void func_ov022_02091474(int a);
extern int func_ov022_020912d8(int a);
extern void func_ov022_020ad588(char *self);

void func_ov102_020b3630(char *self)
{
    func_ov022_0209145c(*(int *)(self + 0x2644), func_ov022_02083f90());
    func_ov022_02091474(*(int *)(self + 0x2644));
    if (func_ov022_020912d8(*(int *)(self + 0x2644)) == 0) {
        if (func_02030788() == 0) {
            *(long long *)(self + 0x464) |= 0x10000;
        }
        if (func_02030788() == 0) {
            *(long long *)(self + 0x46c) |= 0x10000;
        }
    }
    func_ov022_020ad588(self);
}
