/*
 * Apply a mode change to the actor.
 *
 * `mode - 0x2f` selects a per-mode setup arm (0x2f/0x30/0x31 bind an animation config block at
 * self+0x2ce4; 0x32 binds one and clears its counter; 0x33 fires event 0xc6 and then REWRITES
 * mode to 0x31 while caching 0x33 as the mode actually reached). Every arm no-ops when the mode
 * did not change -- +0x6bc caches the previous one.
 *
 * Afterwards the mode is forwarded: below 0x2e it goes straight to the UI band (020521a4, with
 * the "loop" flag set when the actor's anim state at +0x2bb2 is 2); at or above 0x2e it re-inits
 * on 0x2e and, when the cached UI mode byte at +0x2c2c is stale, drives the animation channel
 * (0202accc) with the mode's zero-based index and caches it. Then the mode is handed down
 * (020a384c) and, only if an arm asked for it, the cache at +0x6bc is set to that arm's value.
 *
 * Three catalogued spellings, in the order they were needed:
 *  - ARITY: 020521a4 takes FOUR args, not five. Its own prologue settles it -- 64 bytes,
 *    `push {r3,r4,r5,r6,r7,lr}`, and it never reads [sp,#0x18]. That `push` of r3 is ALIGNMENT
 *    padding (5 saved regs + lr is odd), not an argument slot. Its sibling 02052024 really does
 *    take five and proves the contrast: 9 regs + `sub sp,#4`, then `ldr r0,[sp,#0x28]`.
 *  - `int p2 = self + 0x2ce4;` is a local declared INSIDE the `mode >= 0x2e` block, distinct
 *    from the one the switch uses. That is why the ROM rebuilds the same address into r4 with
 *    two adds and reads `[r4,#0x130]` instead of splitting self+0x2e14 generically -- and why it
 *    re-issues `cmp r6,#0x2e` rather than reusing the flags the `bge` left behind.
 *  - the UI loop flag is `int loop = 0; if (x == 2) loop = 1;`, not `loop = (x == 2)`. The
 *    zero-init plus one `moveq` is what the ROM emits; the comparison form gives the full
 *    predicated `moveq/movne` pair.
 */
extern void func_ov090_020bc704(int self, int p);
extern void func_ov090_020bc780(int self, int p);
extern void func_ov090_020bc818(int self, int p);
extern void func_ov090_020bc8b0(int self, int p);
extern void func_ov090_020bc6c4(int self);
extern void func_ov022_020a4490(int self, int a, int b);
extern void func_ov022_020a384c(int self, int mode);
extern void func_ov002_020521a4(void *a, int b, int c, int d);
extern void func_0202accc(int a, int b, int c, short d);

void func_ov090_020babac(int self, int mode) {
    int p = self + 0x2ce4;
    int reached = -1;

    switch (mode - 0x2f) {
    case 0:
        if (*(int *)(self + 0x6bc) != mode) { func_ov090_020bc704(self, p); }
        break;
    case 1:
        if (*(int *)(self + 0x6bc) != mode) { func_ov090_020bc780(self, p); }
        break;
    case 2:
        if (*(int *)(self + 0x6bc) != mode) { func_ov090_020bc818(self, p); }
        break;
    case 3:
        if (*(int *)(self + 0x6bc) != mode) {
            func_ov090_020bc8b0(self, p);
            *(int *)(p + 0x10) = 0;
        }
        break;
    case 4:
        if (*(int *)(self + 0x6bc) != mode) { func_ov022_020a4490(self, 0xc6, 1); }
        mode = 0x31;
        reached = 0x33;
        break;
    }
    if (mode < 0x2e) {
        int loop = 0;
        if (*(signed char *)(self + 0x2bb2) == 2) { loop = 1; }
        func_ov002_020521a4((void *)(self + 0xda8), self + 0x2c2c, mode, loop);
    } else {
        int p2 = self + 0x2ce4;
        if (mode == 0x2e && *(int *)(self + 0x6bc) != mode) { func_ov090_020bc6c4(self); }
        if (*(signed char *)(self + 0x2c2c) != mode) {
            func_0202accc(self + 0xdac, 0, *(int *)(p2 + 0x130), (short)(mode - 0x2e));
            *(signed char *)(self + 0x2c2c) = (char)mode;
            *(int *)(self + 0x2c30) = 1;
        }
    }
    func_ov022_020a384c(self, mode);
    if (reached >= 0) { *(int *)(self + 0x6bc) = reached; }
}
