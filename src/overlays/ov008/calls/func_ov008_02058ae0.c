/*
 * Ov008_Menu_CommitEnterSubScene8 - confirm/commit path that advances the shared
 * menu context into detail sub-scene 8, latching the persistent state.
 *
 * Bails while bit 4 or bit 5 of the shared context status halfword (+0x5c6) is
 * set, while the two subsystem gates (func_ov008_0206f78c / func_ov008_0206f824)
 * report busy, and unless the input branch is satisfied: when func_ov008_0204ed3c
 * is non-zero it requires func_ov008_020570c0, otherwise it requires
 * func_ov008_0204ebf0. On success it plays the confirm sound only the first time
 * (game flag 0x200c not yet set), refreshes menu button 5, runs the pre-commit
 * step func_ov008_02050ab8(0), latches bit 8 (0x100) at +0x5c6, sets the
 * persistent game flag 0x200c, and primes sub-scene 8 from the cursor.
 *
 * Codegen note: the +0x5c6 bit accesses are a 16-bit bitfield, NOT a manual
 * `(x << N) >> 31` shift. Both forms emit the same `ldrh; lsl; lsr` triple, but
 * only the bitfield IR coalesces the CSE'd container into the field's own
 * register (r0) the way the ROM does; the manual-shift form colors it into a
 * scratch register (r1) and diverges at the first bit test.
 */

extern int func_ov008_0206f78c(void);
extern int func_ov008_0206f824(void);
extern int func_ov008_0204ed3c(void);
extern int func_ov008_020570c0(void);
extern int func_ov008_0204ebf0(void);
extern int func_02023588(int flag);
extern void func_02033b78(int a, int b);
extern void func_ov008_0206f7b0(int a);
extern void func_ov008_02050ab8(int a);
extern void func_020235a8(int flag);
extern void func_ov008_0205714c(int arg);
extern int data_ov008_02090f1c;

typedef struct {
    unsigned short b0:1, b1:1, b2:1, b3:1, b4:1, b5:1, b6:1, b7:1,
                   b8:1, b9:1, b10:1, b11:1, b12:1, b13:1, b14:1, b15:1;
} Flags;

void func_ov008_02058ae0(void)
{
    Flags *f = (Flags *)(data_ov008_02090f1c + 0x5c6);

    if (f->b4) return;
    if (f->b5) return;
    if (func_ov008_0206f78c() != 0) return;
    if (func_ov008_0206f824() != 0) return;
    if (func_ov008_0204ed3c() != 0) {
        if (func_ov008_020570c0() == 0) return;
    } else {
        if (func_ov008_0204ebf0() == 0) return;
    }
    if (func_02023588(0x200c) == 0) func_02033b78(0, 1);
    func_ov008_0206f7b0(0);
    func_ov008_02050ab8(0);
    ((Flags *)(data_ov008_02090f1c + 0x5c6))->b8 = 1;
    func_020235a8(0x200c);
    func_ov008_0205714c(8);
}
