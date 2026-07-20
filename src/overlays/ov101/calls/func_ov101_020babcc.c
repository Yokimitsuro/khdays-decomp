/*
 * Per-frame tick of the paired state: resolve the node handle, run the partner countdown in
 * the shared block (+0x11c / +0x120, expiring at 0x6000), refresh the sub-object at +0x2644
 * three times, raise the 64-bit flag pairs at +0x464 and +0x46c when it reports idle, and
 * publish the pose.
 *
 * THE 64-BIT OR.  The ROM's `orr rN, rN, #0` is not a no-op and not a macro artifact: it is
 * the HIGH HALF of a 64-bit OR on a pair of adjacent flag words.  `*(long long *)(p) |= mask`
 * emits exactly two loads, `orr` low with the mask, `orr` high with zero, two stores.
 * Everything else tried on this -- plain `|= 0`, volatile `|= 0`, explicit `*p = *p | 0`,
 * volatile pointer locals -- recovers the load and the store but never the orr, because there
 * is no `| 0` in the source to preserve.  It also explains the second oddity: the two-step
 * base (`add r0, r5, #0x64` then `[r0, #0x404]`) is just how mwcc addresses the high half,
 * not a separate source construct.
 *
 * Two more levers: func_ov022_02083f0c's RETURN VALUE is func_ov002_0204cdf4's first argument
 * (the ROM sets only r1 and r2 before that call), and the locals are declared base, handle,
 * blk -- any other order permutes r5 and r6.
 */
extern int func_0202aee0(int *node, int a);
extern int func_02030788(void);
extern int func_ov022_02083f90(void);
extern int func_ov022_02083f0c(void);
extern void func_ov002_0204cdf4(int a, int b, int c);
extern int func_ov022_020ad718(char *self);
extern void func_ov022_0209145c(int a, int b);
extern void func_ov022_02091474(int a);
extern int func_ov022_020912d8(int a);
extern void func_ov002_020521e4(char *dst, char *src, int v, int w);
extern void func_ov022_020ad588(char *blk);
extern char *data_ov101_020bc0e0;

void func_ov101_020babcc(char *self) {
    char *base = data_ov101_020bc0e0;
    int r5;
    char *blk;

    r5 = func_0202aee0((int *)(*(int *)(self + 0x20) + 4), 0);
    blk = base + 0x2c80;

    if (*(int *)(self + 0x6bc) != 0x31) {
        if (*(int *)(blk + 0x11c) == 1) {
            *(int *)(blk + 0x120) = *(int *)(blk + 0x120) + func_ov022_02083f90();
            if (*(int *)(blk + 0x120) >= 0x6000) {
                func_ov002_0204cdf4(func_ov022_02083f0c(), 0, 0);
                *(int *)(blk + 0x11c) = 0;
            }
        }
    } else if (*(unsigned char *)(self + 8) == func_02030788()) {
        *(int *)(blk + 0x11c) = func_ov022_020ad718(self);
    }

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

    func_ov002_020521e4(self + 0x30c + 0xc00, base + 0x2c + 0x2c00,
                        *(short *)(self + 0x2a00 + 0xba), r5);
    func_ov022_020ad588(base);
}
