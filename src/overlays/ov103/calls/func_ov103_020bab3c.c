/* func_ov103_020bab3c -- enemy per-frame housekeeping, head of a 4-member family.
 * States 0x30/0x31 are the "hand over to the shared handler" pair: when the owner byte at +8
 * matches the current one, re-arm the slot at +0x2c2c+4 from func_ov022_020ad718. In every other
 * state, an armed slot (== 1) is released back through func_ov002_0204cdf4 and cleared.
 * Either way the frame ends with func_ov022_020ad588(self).
 *
 * Parked for 12 bytes as "mwcc duplicates a one-instruction epilogue where the ROM branches to a
 * single exit", with five source shapes ruled out. The single exit is real but it is not an
 * epilogue: the block at the join is `mov r0,r5 ; bl func_ov022_020ad588 ; pop`, i.e. that call
 * happens on EVERY path. It had been read as belonging to the else branch. Hoisting it out of the
 * `if` matches at the first compile.
 *
 * Worth generalising: when a park says "the ROM shares an exit that mwcc duplicates", look at what
 * is actually AT the join before looking for a codegen lever. Three branches converging on the
 * same address is what a common tail looks like, and a common tail is a statement in the source.
 */
extern int func_ov022_02083f0c(void);
extern void func_ov002_0204cdf4(int a, int b, int c);
extern int func_02030788(void);
extern int func_ov022_020ad718(int self);
extern void func_ov022_020ad588(int self);

void func_ov103_020bab3c(int self) {
    int st = *(int *)(self + 0x6bc);
    int *blk = (int *)(self + 0x2c + 0x2c00);
    if (st != 0x30 && st != 0x31) {
        if (blk[1] == 1) {
            func_ov002_0204cdf4(func_ov022_02083f0c(), 0, 0);
            blk[1] = 0;
        }
    } else {
        if (*(unsigned char *)(self + 8) == func_02030788()) {
            blk[1] = func_ov022_020ad718(self);
        }
    }
    func_ov022_020ad588(self);
}
