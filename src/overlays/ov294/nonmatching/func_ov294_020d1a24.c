/* 2026-07-20: the STRUCT REWRITE AXIS WAS TRIED HERE AND MAKES IT WORSE. Do not repeat.
 * The pointer-cast rule from codegen-cracks.md ("if you are casting pointers the C is
 * wrong") cracked ov029_020b2ee0 and improved ov301_020cbfc4 from 102 to 80 differing
 * bytes, so it looked like the obvious next lever -- especially since this object is
 * clearly the SAME TYPE as ov301_020cbfc4's (fn pointers at 8/0xc/0x30/0x1d0, byte 2 at
 * 0x1c9, the int block at 0x64..0x70, and 0x9c/0x144/0x22c/0x384/0x388).
 * Measured, both 348/348 with correct relocs:
 *      this file, hand-computed offsets:  19 differing bytes, first at 0x51
 *      full struct rewrite:               62 differing bytes, first at 0x20
 * So the rule is a prior, not a law: it is about writing what the original author wrote,
 * and where a modelled layout guesses wrong (field grouping, pointer element type) it
 * moves the codegen further away. Keep the offsets here until the layout is known from
 * the Ghidra type rather than inferred.
 */
/* NONMATCHING - 348/348 B, THREE instructions from exact. Was parked as a
 * "scheduler tie ... register-pressure driven, not source-steerable; confirmed
 * unreproducible across all 26 mwcc generations and statement reorders".
 *
 * That was wrong, and the biggest of the three claims is now fixed: the ROM's
 * hoisted `add r2, r4, #0x100` is not the scheduler being clever, it is a
 * SUB-OBJECT POINTER that is live as a variable. Declaring
 *     struct Body *b = (struct Body *)(param_1 + 0x100);
 * at the top and writing `b->flags |= 0x10` puts the add exactly where the ROM has
 * it, in the same register (r2), filling the same ldr->str delay. 0x100 is
 * encodable as an ARM immediate and 0xae fits an ldrh displacement, which is why
 * the split looks like a scheduling artifact -- it is really a struct base.
 *
 * REMAINING (3, all "which scratch register"):
 *   - the ldrh/orr/strh temp: ROM r3, mwcc r1;
 *   - `str r3, [sp, #0x10]` (g.scale): ROM keeps it in source order, mwcc sinks it
 *     into the func_01fffca8 argument setup;
 *   - `str r0, [r5]` vs `str r1, [r5]`: both hold the same copied value.
 * Do NOT record these as ties without trying declaration order first -- that is
 * what cracked TickTagTrackerNodes, and this file has already been wrong once.
 * The asm stub keeps the blob byte-exact.
 *
 * 2026-07-17 pass. Declaration order HAS now been tried, along with four other axes.
 * All five are byte-identical to each other and to the file as it stands -- the diff
 * stays pinned at 0x51, the ldrh temp. Recording them so the next pass starts past them:
 *   - b/g/r declaration order (b first, b last)                     identical
 *   - `g.scale = 0x1200` before `g.t = data_02041dc8`               identical
 *   - a shared `int fall = 0x1200` local feeding BOTH the +0x70
 *     store and g.scale (they are the same constant, which looked
 *     like a CSE the ROM might be exposing)                         identical
 *   - the return type of func_ov107_020c319c: `long long` (what
 *     this file declares), `int`, and `void *` all produce the
 *     SAME 87 instructions. The type is invisible at this call
 *     site; the `long long` here is not load-bearing and not
 *     evidence of anything. Do not spend a pass on it.
 *
 * ** AND THE ONE THAT MATTERS, so nobody brings the wrong crack here: the VEC_Set crack
 * that just cracked its sibling func_ov294_020d1f94 does NOT apply to this function, and
 * the reason is worth stating. There, the ROM grouped three LOADS and refused to group
 * the stores -- suboptimal, and the tell that no copy existed in the source. HERE the ROM
 * emits `ldm r0,{r0,r1,r2} ; stm r5,{r0,r1,r2}` -- it groups BOTH, which is exactly what
 * mwcc produces for `g.t = data_02041dc8`, and is the correct code because no field is
 * modified on the way. This copy is already byte-exact. The two functions look like the
 * same problem and are not.
 *
 * The callee-side question is also already answered: func_ov107_020c319c reads FOUR words
 * off the block, copies them to +0x58 and +0x68 of a fresh 0x78-byte instance, then copies
 * the first three to +4. So `{ struct v3 t; int scale; }` is the right shape and the right
 * size. Nothing to find there.
 *
 * WHAT IS LEFT is three register/schedule choices with the instruction COUNT already exact
 * (87/87): the ldrh temp (ROM r3 / mwcc r1), the sunk `str r3,[sp,#0x10]` (mwcc fills the
 * arg-setup delay with it, the ROM does not), and `str r0,[r5]` vs `str r1,[r5]` where both
 * registers hold the same value. That is the register-CHOICE residue class in
 * deferred-ties.md -- read that entry before spending another pass here. */
struct v3 { int a, b, c; };
struct Body { char pad[0xae]; unsigned short flags; };

extern struct v3 data_02041dc8;

extern void func_ov294_020d1b80(void);
extern void func_ov294_020d1b9c(void);
extern void func_ov294_020d1c00(void);
extern void func_ov294_020d1c4c(void);

extern void *func_ov107_020c9440();
extern void *func_0203b898();
extern void func_0203bfb4();
extern void func_0203ca14();
extern void func_0203b9fc();
extern void func_ov107_020c92b0();
extern void *func_01fffca8();
extern long long func_ov107_020c319c();
extern void func_0203355c();

/* ov294 actor init: install the handler vtable (update/transform/registry/damage),
 * set the fall speed (0x1200) and flags, spawn the actor's render instance (0203b898)
 * and register it, seed two sorted spline lists (020c319c fills from the shared Vec3
 * const data_02041dc8), and kick off the intro tween (0203355c). */
void func_ov294_020d1a24(int param_1) {
    struct { struct v3 t; int scale; } g;
    long long r;
    struct Body *b = (struct Body *)(param_1 + 0x100);

    *(void **)(param_1 + 8) = func_ov294_020d1b80;
    *(void **)(param_1 + 0xc) = func_ov294_020d1b9c;
    *(void **)(param_1 + 0x30) = func_ov294_020d1c00;
    *(void **)(param_1 + 0x1d0) = func_ov294_020d1c4c;
    *(char *)(param_1 + 0x1c9) = 2;
    *(int *)(param_1 + 0x70) = 0x1200;
    *(int *)(param_1 + 0x64) = 0;
    *(int *)(param_1 + 0x68) = 0;
    *(int *)(param_1 + 0x6c) = 0;
    b->flags |= 0x10;
    *(void **)(param_1 + 0x384) = func_0203b898(func_ov107_020c9440(param_1));
    func_0203bfb4(*(int *)(param_1 + 0x9c), *(void **)(param_1 + 0x384));
    func_0203ca14(*(int *)(param_1 + 0x384) + 4, 0, -0x1200, 0);
    func_0203b9fc(*(int *)(param_1 + 0x384), 0, 0, 1);
    func_0203b9fc(*(int *)(param_1 + 0x384), 4, 0, 1);
    func_ov107_020c92b0(param_1, 2, 2, 0, 0x2000);
    g.t = data_02041dc8;
    g.scale = 0x1200;
    *(void **)(param_1 + 0x388) = func_01fffca8(param_1 + 0x22c, 0x10, 100);
    **(int **)(param_1 + 0x388) = (int)func_ov107_020c319c(&g);
    {
        int *p = func_01fffca8(param_1 + 0x144, 4, 100);
        r = func_ov107_020c319c(&g);
        *p = (int)r;
        *(int *)(param_1 + 0x390) = (int)r;
    }
    func_0203355c(0x171, (int)r);
}
