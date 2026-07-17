/*
 * Apply a mode change to the actor -- the guarded/link variant (x4: ov044/063/081/098).
 *
 * Unlike the rest of the ApplyModeChange family this one gates everything on whether the actor
 * is currently drivable: 0209fc48 + 0209fc78 both have to say yes, otherwise `ok` goes false and
 * the mode is instead mapped to a secondary UI id. That mapping is the big switch (0..4 -> 0..4,
 * 8..11 -> 5..8, 26 -> a "guard broken" event, 23/24 -> the same via a translated mode from
 * 02090978), and it only runs when the mode actually changed. Modes 0x2e/0x2f/0x30 additionally
 * drive the command block at self+0x2ca8, and 0x30 rewrites the mode to 0x2f while caching 0x30
 * as reached -- plus, if this actor owns the slot (02030788), it retargets an already-cached 0x30.
 * The tail then either hands the mode down (020a384c), or runs the 020a46f8 + 020a3c78 hand-off
 * and caches the mode directly.
 *
 * Four spellings carried it. Three are catalogued family rules (see references/families.md);
 * the other two are new and worth the paragraph:
 *
 * ★ 64-BIT FLAGS at self+0. The tell is `and r0, r1, #0` -- a mask whose high half is zero --
 *   and Ghidra prints the low half of the 64-bit OR as the no-op `*param_1 = *param_1`. Test is
 *   `flags & 0x10000000ULL`, set is `flags |= 0x200000000ULL` (bit 33: lo |= 0, hi |= 2). Same
 *   crack as DriveGuardSequence; reached as a struct member.
 *
 * ★ NEW: `if (x == A || x == B || x == C)` on CONSECUTIVE values gets RANGE-OPTIMISED into
 *   `sub r0, x, #A ; cmp r0, #2 ; bhi` -- three instructions, and no ordering of the `||` chain
 *   prevents it (0x2e/0x2f/0x30, 0x2f/0x30/0x2e and 0x2e/0x30/0x2f were all measured: identical).
 *   The ROM's four-instruction `cmp ; cmpne ; cmpne ; bne` comes from a SWITCH with the three
 *   cases sharing a body -- or, equivalently, from `if (x != A && x != B && x != C) {} else`.
 *
 * ★ NEW: `((int *)self)[0x1af]` and `*(int *)(self + 0x6bc)` are the same address and do NOT
 *   compile the same. For the PREDICATED store here the index form folds into the addressing
 *   mode (`streq r0, [sb, #0x6bc]`), while the cast-and-offset form makes mwcc precompute a base
 *   (`add r0, sb, #0x2bc ; streq r1, [r0, #0x400]`) -- one instruction more, and it was the last
 *   one in the way. Plain loads fold either way, which is why this only shows up under
 *   predication. When a diff is one hoisted `add` in front of a conditional store, try the index
 *   spelling.
 *
 * The other three: declaration order DOES drive allocation here (id, ret, reached, handled, ok
 * -> r4, sl, r5, r6, r7) because each initialiser owns a constant the next one borrows --
 * `mvn r4,#0` then `mov r5,r4`, `mov sl,#0` then `mov r6,sl`; the `id != -1 || handled` arm is
 * written FIRST, leaving 020a384c as the cold tail; and 0209fc48/0209fc78 take TWO args each
 * (Ghidra invents five for the first).
 */
struct Actor { unsigned long long flags; };

extern int func_ov022_0209fc48(int self, int i);
extern int func_ov022_0209fc78(int self, int i);
extern void func_ov022_020b19cc(int p, int a, int b);
extern int func_ov022_02090978(int p, unsigned short h);
extern void func_ov022_020902d4(int p, unsigned short h);
extern void func_ov099_020bc7a4(int p, int mode);
extern unsigned short func_02030788(void);
extern void func_ov022_020a384c(int self, int mode);
extern void func_ov022_020a46f8(int self, int mode);
extern void func_ov022_020a3c78(int a, int b, int c, int d);
extern int func_ov002_020519b0(int a, int b, int c);
extern void func_ov002_02052024(void *a, int b, int c, int d, int e);
extern void func_ov002_020521a4(void *a, int b, int c, int d);

void func_ov099_020babd4(int self, int mode) {
    int id = -1;
    int ret = 0;
    int reached = -1;
    int handled = 0;
    int ok = 1;
    int p = self + 0x2ca8;

    if (func_ov022_0209fc48(self, 1) == 0 || func_ov022_0209fc78(self, 1) == 0) { ok = 0; }
    if (!ok && mode != *(int *)(self + 0x6bc)) {
        switch (mode) {
        case 0: id = 0; break;
        case 1: id = 1; break;
        case 2: id = 2; break;
        case 3: id = 3; break;
        case 4: id = 4; break;
        case 8: id = 5; break;
        case 9: id = 6; break;
        case 10: id = 7; break;
        case 11: id = 8; break;
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
    case 0x2e:
    case 0x2f:
    case 0x30:
        func_ov099_020bc7a4(p, mode);
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
            func_ov002_02052024((void *)(self + 0xf0c), self + 0x2c54, mode, 2, ret);
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
