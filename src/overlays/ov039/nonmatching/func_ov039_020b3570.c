/*
 * func_ov039_020b3570 -- UNFINISHED. 792/792 bytes, 198/198 instructions.
 * x4 family (ov058_020b5d70 / ov078_020b8450 / ov095_020bab10) -> worth 4.
 * A FOUR-REGISTER ROTATION and nothing else. The C below is semantically complete, verified
 * against the disassembly, and the instruction SHAPE is exact.
 *
 * WHAT IT DOES: the ov039 ApplyModeChange (family template in references/families.md). First
 * switch: 0x2e re-inits; 0x2f clears the block at self+0x2cd4 and its +0x10, rearms the
 * sub-action at +0x18, and -- if this actor owns the current slot (02030788) and the busy bit
 * 0x10000 is clear -- fires sound 10 (0204cb70, a THUMB callee reached by blx). 0x32 does the
 * same with value 1, rearms a second sub-action at +0x124, fires 10, then rewrites the mode to
 * 0x2f while caching 0x32 as the mode actually reached. 0x33 rewrites the mode to 0xb. 0x30/0x31
 * share an arm firing sound 8. The mode then goes to the main UI band. The SECOND switch maps
 * the mode to a secondary UI id (0x11/0x12 -> 0/1; 0x17/0x18/0x19 -> 2/3/4 quietly; 0x2f -> 8 if
 * it was reached via 0x32 else 5; 0x30/0x31 -> 6/7; 0x1e..0x2d -> the mode itself, quietly), and
 * that id drives a second 02052024 -- or, when there is no id, the band's byte is set to -1 and
 * the "loud" bit at self+0xf0c is cleared.
 *
 * THE GAP, precisely: the ROM allocates flag=r5, id=r6, quiet=r7, ret=sl. This C gets
 * flag=sl, quiet=r5, ret=r6, id=r7. Same instructions, same order, same size -- a pure 4-way
 * rename of the callee-saved set.
 *
 * THE SHAPE IS ALREADY RIGHT, which is the useful part. The ROM's tell is that ONE zero is
 * shared three ways:
 *      mov   r5, #0      <- flag = 0     (flag OWNS the constant)
 *      mov   r7, r5      <- quiet = 0    (borrows it)
 *      sub   r6, r5, #1  <- id = -1      (borrows it)
 *      moveq r5, #1      <- flag = 1     (and flag keeps r5)
 * This C reproduces that exactly -- `mov sl,#0 ; mov r5,sl ; sub r7,sl,#1 ; moveq sl,#1` --
 * flag owning the constant, the other two borrowing. Only the names differ. Getting here needed
 * `flag = 0; quiet = 0; id = -1;` written BEFORE the `if (reached >= 0)`; written after it (the
 * obvious order) mwcc makes QUIET own the zero and flag borrow, which is structurally wrong.
 *
 * RULED OUT, on these axes:
 *  - ARITY of every callee, against the tree AND the callees' own prologues -- the rule that
 *    cracked ov046 in this same family: 02030788(void)->uint per its real definition in
 *    src/calls/, 02083f0c(void), 020b3f18(2), 020519b0(3), 020521a4(4), 02052024(5),
 *    020a384c(2). 0204cb70 has NO C call site, so its prologue was read directly: THUMB, 300 B,
 *    `push {r3,r4,r5,lr}` where the r3 is 8-byte alignment padding (3 regs + lr is odd), and no
 *    incoming stack-arg load -> at most 3 args, which is what the ROM passes.
 *  - DECLARATION ORDER: all 24 permutations of (flag, quiet, id, ret), swept TWICE -- once on
 *    the statement order below and once on the earlier one. 48 compiles, all 48 byte-identical
 *    to each other. This is the fourth independent measurement of the same negative (ov048 x4,
 *    ov038 x4+2, ov000_02057dc4 x5): declaration order does not drive allocation when every
 *    value lives across the whole region. It is not a coin worth flipping again.
 *  - STATEMENT ORDER: init-before-020a384c (diffs at 0x154, worse); quiet/id-before-flag (0x180
 *    -- moves the diff LATER but makes quiet own the zero, so it is further from the ROM's
 *    structure, not closer: the byte offset lies here); decl-initialisers instead of assignments
 *    (788 B, one instruction short -- so the ROM is not that form).
 *
 * NOT TRIED, and where to go next: the rotation is decided where mwcc reuses r5. `p`
 * (self+0x2cd4) lives in r5 through the first switch and dies at it, and the ROM hands r5
 * straight to flag. The whole first half (0x000-0x15c) is ALREADY byte-exact, so `p` is in the
 * right register; what is unknown is what makes mwcc prefer flag over quiet for the freed r5.
 * Worth trying: changing `p`'s live range -- inline the expression in each case body instead of
 * using a local, or scope the local inside the switch. That is the only lever found so far that
 * touches allocation without touching the shape.
 */
extern void WM_EndKeySharing_0x020b3e80(int self);
extern void func_ov039_020b3f18(int p, int v);
extern unsigned short func_02030788(void);
extern int func_ov022_02083f0c(void);
extern void func_ov002_0204cb70(int a, int b, int c);
extern void func_ov022_020a384c(int self, int mode);
extern int func_ov002_020519b0(int a, int b, int c);
extern void func_ov002_02052024(void *a, int b, int c, int d, int e);
extern void func_ov002_020521a4(void *a, int b, int c, int d);

void func_ov039_020b3570(int self, int mode) {
    int p = self + 0x2cd4;
    int reached = -1;
    int flag;
    int quiet;
    int id;
    int ret;

    switch (mode - 0x2e) {
    case 0:
        if (*(int *)(self + 0x6bc) != mode) { WM_EndKeySharing_0x020b3e80(self); }
        break;
    case 1:
        if (*(int *)(self + 0x6bc) != mode) {
            *(int *)p = 0;
            *(int *)(p + 0x10) = 0;
            func_ov039_020b3f18(p + 0x18, 0);
            if (*(unsigned char *)(self + 8) == func_02030788()
                && (*(int *)self & 0x10000) == 0) {
                func_ov002_0204cb70(func_ov022_02083f0c(), 10, 0);
            }
        }
        break;
    case 4:
        if (*(int *)(self + 0x6bc) != mode) {
            *(int *)p = 1;
            *(int *)(p + 0x10) = 0;
            func_ov039_020b3f18(p + 0x18, 1);
            func_ov039_020b3f18(p + 0x124, 2);
            if (*(unsigned char *)(self + 8) == func_02030788()
                && (*(int *)self & 0x10000) == 0) {
                func_ov002_0204cb70(func_ov022_02083f0c(), 10, 0);
            }
        }
        reached = mode;
        mode = 0x2f;
        break;
    case 5:
        reached = mode;
        mode = 0xb;
        break;
    case 2:
    case 3:
        if (*(int *)(self + 0x6bc) != mode && *(unsigned char *)(self + 8) == func_02030788()
            && (*(int *)self & 0x10000) == 0) {
            func_ov002_0204cb70(func_ov022_02083f0c(), 8, 0);
        }
        break;
    }
    func_ov022_020a384c(self, mode);
    flag = 0;
    quiet = 0;
    id = -1;
    if (reached >= 0) { *(int *)(self + 0x6bc) = reached; }
    if (*(signed char *)(self + 0x2bb2) == 2) { flag = 1; }
    ret = func_ov002_020519b0(mode, *(int *)(self + 0x6bc), *(int *)(self + 0xc));
    if (mode >= 0x2e) {
        flag = 2;
        func_ov002_02052024((void *)(self + 0xda8), self + 0x2c2c, mode, flag, ret);
    } else {
        func_ov002_020521a4((void *)(self + 0xda8), self + 0x2c2c, mode, flag);
    }
    switch (mode) {
    case 0x11: id = 0; break;
    case 0x12: id = 1; break;
    case 0x17: id = 2; quiet = 1; break;
    case 0x18: id = 3; quiet = 1; break;
    case 0x19: id = 4; quiet = 1; break;
    case 0x30: id = 6; break;
    case 0x31: id = 7; break;
    case 0x2f: id = (reached == 0x32) ? 8 : 5; break;
    default:
        if (mode >= 0x1e && mode < 0x2e) { id = mode; quiet = 1; }
        break;
    }
    if (id >= 0) {
        if (!quiet && *(signed char *)(self + 0xf0d) != 0) {
            *(unsigned char *)(self + 0xf0c) |= 1;
        }
        func_ov002_02052024((void *)(self + 0xf0c), self + 0x2c80, id, flag, ret);
        return;
    }
    if (*(signed char *)(self + 0xf0d) != 0) {
        *(unsigned char *)(self + 0xf0c) &= ~1;
    }
    *(char *)(self + 0x2c80) = -1;
}
