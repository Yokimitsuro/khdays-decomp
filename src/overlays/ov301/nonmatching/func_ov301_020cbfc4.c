/*
 * func_ov301_020cbfc4 -- UNFINISHED. 408/408 bytes, all 16 relocs matching by name.
 * ov301 is 17/18 and this is the LAST function in the overlay.
 *
 * 2026-07-20: REWRITTEN AGAINST A REAL STRUCT, and it is measurably closer.
 * The old version addressed the object as ~20 hand-computed byte offsets
 * (*(int *)(param_1 + 0x1fc), **(int **)(param_1 + 0x388), ...). Per the pointer-cast
 * rule in codegen-cracks.md, a cast is a symptom of wrong C, not a technique: a developer
 * would have written self->field. Measured, same size both ways:
 *      old (byte offsets): 102 differing bytes, 75/92 instructions with the same mnemonic
 *      new (struct):        80 differing bytes, 80/92
 * The rewrite also EXPOSED A REAL BUG the cast form was hiding: the field at 0x388 is
 * `int *`, not `int **`. Typed as `int **` the store needs three instructions where the ROM
 * uses two (ldr r2,[r4,#0x388]; str r0,[r2]), which cost 4 bytes. A wrong indirection level
 * is invisible inside **(int **)(param_1 + 0x388) and obvious in a struct field.
 *
 * WHAT IS LEFT: a register-choice tie on three short-lived constants.
 *      ROM:   uVar4 -> r3,  iVar1 -> r6,  0x17 -> r5
 *      ours:  uVar4 -> r7,  iVar1 -> r5,  0x17 -> lr
 * The push list is IDENTICAL ({r3,r4,r5,r6,r7,lr}), so the same registers are available.
 * r3 is pushed only for 8-byte alignment and the ROM then spends it as a scratch value
 * register (legal: nothing is live across a call until +0xc4). mwcc reaches for callee-saved
 * registers instead. All three constants have exactly 2 uses and near-identical live ranges,
 * which is precisely the symmetric case where the tie-break is invisible from the source.
 *
 * CRACK FOUND HERE, also in codegen-cracks.md -- do not undo it: the block at +0x1fc is a
 * bounding box, three (min, max) pairs where max = min + extent. Deriving max from the LOCAL
 * lets mwcc constant-fold it and materialise the literal cheaply (rsb r2,r6,#0xf00), 3
 * instructions SHORT. Deriving it from the STRUCT MEMBER just stored does not fold and
 * reproduces the ROM's runtime two-add chain exactly.
 *
 * Two arity bugs were fixed here earlier; do not re-introduce them. func_0203b898 takes
 * the RESULT of func_ov107_020c9440(self, 0), nested (the ROM sets up no arguments before
 * that bl). func_0203bfb4 takes TWO args, not three.
 *
 * RULED OUT (17 spellings across three sessions, diff pinned at 0x15 throughout):
 *   4 declaration orders of the two constants -- byte-IDENTICAL output, so decl order is not
 *     the axis; 0x17 as an explicit local in 3 slots; 1/2/3/4 parameters on the function;
 *   both constants inlined at their single use, removing the locals -- byte-identical again,
 *     so the locals were never the thing;
 *   the six field assignments interleaved so each constant dies immediately -- much worse (88);
 *   the bounding-box block moved above the pointer stores -- 404, 4 SHORT;
 *   the box written straight through a pointer instead of built in a local and copied --
 *     388, 20 SHORT, so the local struct plus block copy is load-bearing.
 *
 * NEXT STEP: something that makes the three constants' use counts or live ranges DIFFER.
 * Not found yet. Asked on the decomp.me Discord.
 */
extern int func_ov301_020cc15c, func_ov301_020cc178, func_ov301_020cc240;
extern int WM_EndKeySharing_0x020cc1d8, WM_EndKeySharing_0x020cc1e4;
extern int func_ov301_020cc28c, func_ov301_020cc1f0;
extern int data_02041dc8[], data_02042264[];
extern int func_ov107_020c9440(int p, int a);
extern int func_0203b898(int r0);
extern void func_0203bfb4(int a, int b);
extern int *func_01fffca8(void *p, int sz, int n);
extern int func_ov107_020c3210(void *p);
extern int func_ov107_020c319c(void *p);

struct blk3 { int x, y, z; };
typedef struct { int minX, minY, minZ, maxX, maxY, maxZ; } Box;

typedef struct {
    char      pad_00[0x08];
    void     *fn08;          /* 0x08 */
    void     *fn0c;          /* 0x0c */
    char      pad_10[0x18];
    void     *fn28;          /* 0x28 */
    void     *fn2c;          /* 0x2c */
    void     *fn30;          /* 0x30 */
    char      pad_34[0x30];
    int       cam[4];        /* 0x64 */
    char      pad_74[0x28];
    int       p9c;           /* 0x9c */
    char      pad_a0[0xa4];
    char      pool144[0x6a]; /* 0x144 */
    unsigned short flags1ae; /* 0x1ae */
    char      pad_1b0[0x19];
    char      b1c9;          /* 0x1c9 */
    char      pad_1ca[0x06];
    void     *fn1d0;         /* 0x1d0 */
    char      pad_1d4[0x08];
    void     *fn1dc;         /* 0x1dc */
    char      pad_1e0[0x1c];
    Box       box;           /* 0x1fc */
    char      pad_214[0x18];
    char      pool22c[0x158];/* 0x22c */
    int       p384;          /* 0x384 */
    int      *p388;          /* 0x388 */
    int       p38c;          /* 0x38c */
} Ov301Obj;

void func_ov301_020cbfc4(Ov301Obj *self) {
    int iVar1 = 0xfffff116;
    unsigned int uVar4 = 0xfffff7a8;
    struct { int v[8]; } b;
    Box s;
    int *slot;

    self->fn08  = &func_ov301_020cc15c;
    self->fn0c  = &func_ov301_020cc178;
    self->fn30  = &func_ov301_020cc240;
    self->fn28  = &WM_EndKeySharing_0x020cc1d8;
    self->fn2c  = &WM_EndKeySharing_0x020cc1e4;
    self->fn1d0 = &func_ov301_020cc28c;
    self->fn1dc = &func_ov301_020cc1f0;
    self->b1c9  = 2;
    self->cam[3] = 0x1900;
    self->cam[0] = 0;
    self->cam[1] = 0x400;
    self->cam[2] = 0;

    s.minX = iVar1;
    s.minY = 0x17;
    s.minZ = uVar4;
    s.maxX = s.minX + 0x1dd3;
    s.maxY = s.minY + 0x1c27;
    s.maxZ = s.minZ + 0xd64;
    self->box = s;

    self->p384 = func_0203b898(func_ov107_020c9440((int)self, 0));
    func_0203bfb4(self->p9c, self->p384);

    self->flags1ae |= 0x10;
    *(struct blk3 *)&b.v[0] = *(struct blk3 *)data_02041dc8;
    *(struct blk3 *)&b.v[3] = *(struct blk3 *)data_02042264;
    b.v[6] = 0x4000;
    b.v[7] = 0x1900;

    self->p388 = func_01fffca8(&self->pool22c[0], 0x10, 0x64);
    *self->p388 = func_ov107_020c3210(&b);

    slot = func_01fffca8(&self->pool144[0], 4, 0x64);
    *slot = func_ov107_020c319c(&self->cam[0]);
    self->p38c = *slot;
}
