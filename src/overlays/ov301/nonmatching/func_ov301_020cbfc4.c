/*
 * func_ov301_020cbfc4 -- UNFINISHED. 408/408 bytes, 92/92 instructions,
 * INSTRUCTION-FOR-INSTRUCTION identical to the ROM. All 16 relocs match by name.
 * The only difference is which registers three constants land in.
 *
 * ov301 is 17/18 -- this is the LAST function in the overlay. Worth finishing.
 *
 * This file replaces an older one that had no diagnosis note and three real bugs.
 * Do NOT re-introduce them; each is confirmed against the disassembly:
 *   1. `func_0203b898` takes the RESULT of `func_ov107_020c9440(param_1, 0)`, nested --
 *      the ROM sets up no arguments at all before that bl (+0x0c8), r0 just carries
 *      through. The old file called it as func_0203b898(param_1).
 *   2. `func_0203bfb4` takes TWO args, not three. The ROM sets only r0/r1 at +0x0d8, the
 *      real definition in src/calls/func_0203bfb4.c is `int f(int, int)`, and every other
 *      call site in the tree passes 2. The old file passed uVar4 as a phantom third.
 *   3. The reloc NAMES were wrong: it is func_ov107_020c9440 / func_ov107_020c3210 /
 *      func_ov107_020c319c (not func_020c*), and +0x28/+0x2c store
 *      WM_EndKeySharing_0x020cc1d8 / _020cc1e4 -- junk SDK names the identifier matched by
 *      shape, but they are what the index carries, so they are what must be written.
 *
 * ★ CRACK FOUND HERE, now also in codegen-cracks.md -- do not undo it:
 *   The +0x1fc block is a bounding box: three (min, max) pairs where max = min + extent.
 *   Deriving max from the LOCAL (`s.d = iVar1 + 0x1dd3`) lets mwcc constant-fold it to the
 *   literal 0xee9 and then materialise that cheaply from some other live constant
 *   (`rsb r2, r6, #0xf00`) -- 3 instructions SHORT (396). Deriving it from the STRUCT
 *   MEMBER just stored (`s.d = s.a + 0x1dd3`) does not fold, and reproduces the ROM's
 *   runtime two-add chain (`add r0,r6,#0xd3 ; add r2,r0,#0x1d00`) exactly.
 *   Measured both ways: s.d and s.f each cost 4 bytes when spelled off the local (P4/P5).
 *
 * PRE-PARK CHECKLIST:
 *  1. --thumb: run. ARM is the exact 408/408; THUMB gives 316 != 408. It is ARM.
 *  2. Arity: this is what the whole rescue WAS -- two arity bugs found and fixed. All 16
 *     relocs now match by name and position, which is strong evidence the call structure
 *     is right.
 *  3. A constant IS in the wrong register -- but see below: it is three of them, and the
 *     arity of every call has been checked against both the ROM and the tree.
 *  4. Diff read back: 92/92 instructions, same opcodes, same operands, same order.
 *
 * THE DIFFERENCE (starts at 0x15, everything downstream is the same permutation):
 *      ROM:   uVar4 -> r3,  iVar1 -> r6,  0x17 -> r5
 *      mine:  uVar4 -> r6,  iVar1 -> r7,  0x17 -> lr
 * The push list is IDENTICAL ({r3,r4,r5,r6,r7,lr}), so the same registers are available to
 * both. r3 is pushed for 8-byte alignment and the ROM then spends it as a scratch value
 * register (legal -- nothing is live across a call until +0xc4). mwcc instead reaches for
 * the callee-saved r6/r7. The constant-pool ORDER is already identical (020cc15c,
 * 0xfffff7a8, 020cc178, 0xfffff116, ...), so first-use order is not the lever.
 *
 * RULED OUT (12 spellings, all still 408/408 with the diff pinned at 0x15):
 *   4 declaration orders of iVar1/uVar4 (both first, both last, either side of the
 *     aggregates, slot first) -- byte-IDENTICAL output, so decl order is not the axis
 *   0x17 as an explicit local, declared in 3 different slots
 *   1/2/3/4 parameters on the function itself (r3 live at entry does not change it)
 * And ruled out in the other direction (these make it WORSE, 404): deriving s.d or s.f
 * from the local instead of the struct member.
 *
 * NEXT STEP: the axis is which register a short-lived constant gets when several compete
 * and none is live across a call. state.md's note that caller-saved values are ordered by
 * USE COUNT and live range (not declaration order) fits: all three constants here have
 * exactly 2 uses and near-identical live ranges, which is precisely the symmetric case
 * where the tie-break is invisible from the source. Something that makes their use counts
 * or live ranges DIFFER is the thing to try -- I could not find one.
 */
extern int func_ov301_020cc15c, func_ov301_020cc178, func_ov301_020cc240;
extern int WM_EndKeySharing_0x020cc1d8, WM_EndKeySharing_0x020cc1e4;
extern int func_ov301_020cc28c, func_ov301_020cc1f0;
extern int data_02041dc8[], data_02042264[];
extern int func_ov107_020c9440(int p, int a);
extern int func_0203b898(int r0);
extern void func_0203bfb4(int a, int b);
extern int *func_01fffca8(int p, int sz, int n);
extern int func_ov107_020c3210(void *p);
extern int func_ov107_020c319c(int p);

struct blk6 { int a, b, c, d, e, f; };
struct blk3 { int x, y, z; };

void func_ov301_020cbfc4(int param_1) {
    int iVar1 = 0xfffff116;
    unsigned int uVar4 = 0xfffff7a8;
    struct { int v[8]; } b;
    struct blk6 s;
    int *slot;

    *(int *)(param_1 + 8)     = (int)&func_ov301_020cc15c;
    *(int *)(param_1 + 0xc)   = (int)&func_ov301_020cc178;
    *(int *)(param_1 + 0x30)  = (int)&func_ov301_020cc240;
    *(int *)(param_1 + 0x28)  = (int)&WM_EndKeySharing_0x020cc1d8;
    *(int *)(param_1 + 0x2c)  = (int)&WM_EndKeySharing_0x020cc1e4;
    *(int *)(param_1 + 0x1d0) = (int)&func_ov301_020cc28c;
    *(int *)(param_1 + 0x1dc) = (int)&func_ov301_020cc1f0;
    *(char *)(param_1 + 0x1c9) = 2;
    *(int *)(param_1 + 0x70) = 0x1900;
    *(int *)(param_1 + 0x64) = 0;
    *(int *)(param_1 + 0x68) = 0x400;
    *(int *)(param_1 + 0x6c) = 0;

    s.a = iVar1;
    s.b = 0x17;
    s.c = uVar4;
    s.d = s.a + 0x1dd3;
    s.e = s.b + 0x1c27;
    s.f = s.c + 0xd64;
    *(struct blk6 *)(param_1 + 0x1fc) = s;

    *(int *)(param_1 + 0x384) = func_0203b898(func_ov107_020c9440(param_1, 0));
    func_0203bfb4(*(int *)(param_1 + 0x9c), *(int *)(param_1 + 0x384));

    *(unsigned short *)(param_1 + 0x1ae) |= 0x10;
    *(struct blk3 *)&b.v[0] = *(struct blk3 *)data_02041dc8;
    *(struct blk3 *)&b.v[3] = *(struct blk3 *)data_02042264;
    b.v[6] = 0x4000;
    b.v[7] = 0x1900;

    *(int *)(param_1 + 0x388) = (int)func_01fffca8(param_1 + 0x22c, 0x10, 0x64);
    **(int **)(param_1 + 0x388) = func_ov107_020c3210(&b);

    slot = func_01fffca8(param_1 + 0x144, 4, 0x64);
    *slot = func_ov107_020c319c(param_1 + 0x64);
    *(int *)(param_1 + 0x38c) = *slot;
}
