/* func_ov046_020b362c -- per-frame tick of the paired state: run the partner countdown,
 * refresh the shared block, and publish the pose.
 *
 * NONMATCHING: 304/324 bytes, 20 short.  Everything down to the flag updates is right.
 *
 * SEMANTICS, decoded and believed complete:
 *   Resolve the node handle once (func_0202aee0 on the node at +0x20), keep it for the
 *   final publish.  On message 0x31, and only when the actor's own id at +8 matches the
 *   current one, latch the partner handle into the shared block at +0x11c.  Otherwise, if
 *   that handle is already 1, accumulate elapsed time into +0x120 and once it passes
 *   0x6000 stop the effect, clear the block and reset +0x11c.
 *   Then refresh the sub-object at self+0x2644 three times over (feed, advance, query) and,
 *   if the query says idle, set bit 16 on the two flag words at +0x464 and +0x46c.
 *   Finally publish through func_ov002_020521e4 with the short at self+0x2aba and the node
 *   handle resolved at the top.
 *
 * SOLVED, do not redo:
 *  - the two `orr rN, rN, #0` sequences are REAL.  ** CORRECTED 2026-07-20: volatile does
 *    NOT emit the orr. **  It brings back the LOAD and the STORE, which is the +16 measured
 *    here (4 bytes x 2 per site), but mwcc still folds the `| 0` itself.  Five spellings
 *    were measured on the sibling func_ov033_020b3970, which has the identical block: plain
 *    `|= 0`, volatile `|= 0`, explicit `*p = *p | 0`, the same through a volatile pointer
 *    local, and reading into a plain int first.  None emits the orr.
 *    The ROM PAIRS the no-op OR with a separate base register (`add r0, r5, #0x64` then
 *    `[r0, #0x404]`, where the folded offset 0x468 would be perfectly encodable), and it
 *    does so at both sites here and again in ov033.  One construct probably produces both
 *    -- most likely a macro or inline helper taking a base pointer and a mask that is zero
 *    at these call sites.  That is the single open question for both functions.
 *  - the 0x31 dispatch is a JUMP-TO shape (`cmp #0x31 ; beq <block>` with the other path
 *    falling through), which needs the inverted spelling `if (x != 0x31) { other } else
 *    { this }`.  Same lever as func_ov046_020b3770 in this overlay.
 *  - `blk = base + 0x2c80` is computed AFTER the first call, not at its declaration.
 *
 * WHAT IS STILL MISSING, precisely: the ROM interleaves the two flag updates and reaches
 * the second one through a computed base --
 *      add r0, r7, #0x64 ; ldr r2, [r7, #0x464] ; ldr r1, [r0, #0x404]
 *      orr r2, r2, #0x10000 ; str r2, [r7, #0x464] ; orr r1, r1, #0 ; str r1, [r0, #0x404]
 * so the FIRST field is addressed off self directly and the SECOND off self+0x64, even
 * though both offsets are encodable either way.  We emit two independent read-modify-writes
 * off self.  That mixture is the thing to reproduce: it suggests the two fields are reached
 * through different expressions in the source -- one a plain member, the other through a
 * sub-object pointer at self+0x64 -- rather than both as offsets from the same base.  That
 * is the next thing to try, and it is worth trying because the same pattern repeats at
 * +0x46c / self+0x6c a few instructions later.
 */
extern int func_0202aee0(int *node, int a);
extern int func_02030788(void);
extern int func_ov022_02083f90(void);
extern void func_ov022_02083f0c(void);
extern void func_ov002_0204cdf4(int a, int b, int c);
extern int func_ov022_020ad718(char *self);
extern void func_ov022_0209145c(int a, int b);
extern void func_ov022_02091474(int a);
extern int func_ov022_020912d8(int a);
extern void func_ov002_020521e4(char *dst, char *src, int v, int w);
extern void func_ov022_020ad588(char *blk);
extern char *data_ov046_020b4b40;

void func_ov046_020b362c(char *self) {
    char *base = data_ov046_020b4b40;
    char *blk;
    int r5;

    r5 = func_0202aee0((int *)(*(int *)(self + 0x20) + 4), 0);
    blk = base + 0x2c80;

    if (*(int *)(self + 0x6bc) != 0x31) {
        if (*(int *)(blk + 0x11c) == 1) {
            *(int *)(blk + 0x120) = *(int *)(blk + 0x120) + func_ov022_02083f90();
            if (*(int *)(blk + 0x120) >= 0x6000) {
                func_ov022_02083f0c();
                func_ov002_0204cdf4(0, 0, 0);
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
            *(int *)(self + 0x464) |= 0x10000;
            *(volatile int *)(self + 0x64 + 0x404) |= 0;
        }
        if (func_02030788() == 0) {
            *(int *)(self + 0x46c) |= 0x10000;
            *(volatile int *)(self + 0x6c + 0x404) |= 0;
        }
    }

    func_ov002_020521e4(self + 0x30c + 0xc00, base + 0x2c + 0x2c00,
                        *(short *)(self + 0x2a00 + 0xba), r5);
    func_ov022_020ad588(base);
}
