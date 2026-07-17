/*
 * Apply a mode change to the actor -- the guarded/link variant with a slot check
 * (x4: ov030/054b/074b/091b -- see the dedup fan-out for the exact twins).
 *
 * The ov044 shape plus two things. First, the switch that maps a mode to a secondary UI id runs
 * only when the actor is NOT drivable (0209fc48 + 0209fc78) AND the word at self+0x2ca8 is
 * exactly 0x80000000 AND the mode actually changed -- the ROM spells that guard as one
 * predicated chain (`cmp r6,#0 ; addeq ; ldreq ; cmpeq r0,#0x80000000 ; bne`), so the load only
 * happens when `ok` is false. Second, mode 0x1b has its own arm (id 2, and it CLEARS ret), which
 * is why the tail switch here has four cases where ov044's had three.
 *
 * The id mapping differs from ov044's: 0..4 -> 0,1,3,4,5 (note the gap at 2, which 0x1b fills)
 * and 8..11 -> 6..9.
 *
 * Matched off the ov044 template with all its cracks (64-bit flags at self+0 via a struct member,
 * the `((int *)self)[0x1af]` index spelling for the predicated store, the switch-not-`||` for the
 * 0x2e/0x2f/0x30 group, both arities). Two notes specific to this one:
 *  - The `case 0x1b:` and the 0x2e/0x2f/0x30 group are ONE switch. mwcc compiles it to a binary
 *    search (`cmp #0x1b ; bgt` / `cmp #0x30 ; bgt` / `cmp #0x2e ; blt`) and only then the
 *    `cmpne ; cmpne` chain for the shared arm. Ghidra renders that tree as nested `if`s with a
 *    redundant-looking `mode < 0x31 && mode > 0x2d && (mode == 0x2e || ...)`; do not transcribe
 *    that literally.
 *  - DECLARATION ORDER is (id, ret, handled, ok, reached) -> r4, sl, r5, r6, r7. It matters here
 *    for the same reason as in ov044: each initialiser owns a constant the next borrows
 *    (`mvn r4,#0` then `mov r7,r4`; `mov sl,#0` then `mov r5,sl`). Note the order is NOT ov044's
 *    -- there `reached` borrowed before `handled`, here it is the other way round, and the
 *    borrow order in the ROM is what tells you which. All 40 constraint-satisfying permutations
 *    were swept; exactly one matches.
 */
struct Actor { unsigned long long flags; };

extern int func_ov022_0209fc48(int self, int i);
extern int func_ov022_0209fc78(int self, int i);
extern void func_ov022_020b19cc(int p, int a, int b);
extern int func_ov022_02090978(int p, unsigned short h);
extern void func_ov022_020902d4(int p, unsigned short h);
extern void func_ov030_020b55d0(int p, int mode);
extern unsigned short func_02030788(void);
extern void func_ov022_020a384c(int self, int mode);
extern void func_ov022_020a46f8(int self, int mode);
extern void func_ov022_020a3c78(int a, int b, int c, int d);
extern int func_ov002_020519b0(int a, int b, int c);
extern void func_ov002_02052024(void *a, int b, int c, int d, int e);
extern void func_ov002_020521a4(void *a, int b, int c, int d);

void func_ov030_020b3990(int self, int mode) {
    int id = -1;
    int ret = 0;
    int handled = 0;
    int ok = 1;
    int reached = -1;
    int p = self + 0x2cb0;

    if (func_ov022_0209fc48(self, 1) == 0 || func_ov022_0209fc78(self, 1) == 0) { ok = 0; }
    if (!ok && *(unsigned int *)(self + 0x2ca8) == 0x80000000
        && mode != *(int *)(self + 0x6bc)) {
        switch (mode) {
        case 0: id = 0; break;
        case 1: id = 1; break;
        case 2: id = 3; break;
        case 3: id = 4; break;
        case 4: id = 5; break;
        case 8: id = 6; break;
        case 9: id = 7; break;
        case 10: id = 8; break;
        case 11: id = 9; break;
        case 26:
            if ((((struct Actor *)self)->flags & 0x10000000ULL) == 0) {
                ((struct Actor *)self)->flags |= 0x200000000ULL;
                func_ov022_020b19cc(self + 0xd90, mode + 0x1b, 0x11);
                handled = 1;
            }
            break;
        case 23:
        case 24:
            if ((((struct Actor *)self)->flags & 0x10000000ULL) == 0
                && func_ov022_0209fc78(self, 1) == 0) {
                mode = func_ov022_02090978(self + 0x2288, *(unsigned short *)(self + 0x4d8));
                ((struct Actor *)self)->flags |= 0x200000000ULL;
                func_ov022_020b19cc(self + 0xd90, mode + 0x1b, 0x12);
                func_ov022_020902d4(self + 0x2288, *(unsigned short *)(self + 0x4d8));
                handled = 1;
            }
            break;
        }
        if (id != -1 && handled != 1) {
            ret = func_ov002_020519b0(mode, *(int *)(self + 0x6bc), *(int *)(self + 0xc));
        }
    }
    switch (mode) {
    case 0x1b:
        id = 2;
        ret = 0;
        break;
    case 0x2e:
    case 0x2f:
    case 0x30:
        func_ov030_020b55d0(p, mode);
        if (mode == 0x30) {
            mode = 0x2f;
            reached = 0x30;
            if (func_02030788() != 0 && ((int *)self)[0x1af] == 0x30) {
                ((int *)self)[0x1af] = mode;
            }
        }
        break;
    }
    if (handled == 0 && ok == 1) {
        int flag = 0;
        if (*(signed char *)(self + 0x2bb2) == 2) { flag = 1; }
        if (mode >= 0x2e) {
            func_ov002_02052024((void *)(self + 0xf0c), self + 0x2c54, mode + 1, 2, ret);
        } else {
            func_ov002_020521a4((void *)(self + 0xf0c), self + 0x2c54, mode, flag);
        }
    }
    if (id != -1 || handled == 1) {
        if (handled == 0) {
            func_ov022_020a46f8(self, mode);
            func_ov022_020a3c78(self, self + 0x2c2c, id, ret);
        }
        *(int *)(self + 0x6bc) = mode;
        return;
    }
    func_ov022_020a384c(self, mode);
    if (reached >= 0) { *(int *)(self + 0x6bc) = reached; }
}
