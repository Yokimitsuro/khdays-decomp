/* func_ov222_020d6648 -- enter the charge state: reset the flags and the timers, snapshot the
 * anchor position, then branch on ctx[0x16] to one of two charge profiles.
 *
 * One of a 4-member shape family; the twins live in ov221/ov224/ov225 and are byte-identical
 * modulo relocs (matched here, fanned out with dedupprop).
 *
 * Two flag words are OR'd with 1 up front: the hi byte of the owner's hw60 halfword, and the low
 * byte of the u32 at *(ctx[0]+0x388) + 8. Both use the explicit extract/reassemble spelling rather
 * than a bitfield struct -- neither carries the `lsl#0x10 ; lsr#0x10` trunc pair that would call
 * for the bitfield form (codegen-cracks.md). `v & ~0xff00` is deliberate: `v & 0xff` would emit
 * `and #0xff` where the ROM has `bic #0xff00`.
 *
 * ctx[3..5] takes a copy of the vec3 at *(ctx[0]+0x390) + 0x74 -- a struct assignment, which is
 * what produces the ROM's ldm/stm pair; three int stores would not.
 *
 * The two profiles differ in the wind-up they arm:
 *   ctx[0x16] == 0 -> anim 0x432, reach 0x400, 0x32000, and a RANDOM hold of
 *                     rand(0x1000) + 0x2000 at ctx[0x15]; continues at func_ov222_020d69c0
 *   ctx[0x16] == 1 -> anim 0x600, reach 0x700, 0x32000, no random hold;
 *                     continues at func_ov222_020d6af4
 * Any other value falls straight out without dispatching.
 *
 * ctx[0] is re-read before each use rather than cached in a local: the stores through it may alias
 * *ctx, so the ROM reloads and so must the C (codegen-cracks.md). */

typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

/* The u32 at *(ctx[0]+0x388) + 8 -- only its low byte is a flag set. This one DOES want the
 * bitfield form: the ROM keeps both the lsl#0x18/lsr#0x18 extract and the redundant `and #0xff`
 * field-width truncation, which is exactly what `lo |= K` on an unsigned bitfield emits. Writing
 * the extract by hand instead lets mwcc fold it to `and #0xff` and drop the mask (-8 bytes). */
typedef struct {
    u32 lo : 8;
    u32 rest : 24;
} FlagsW;

extern void func_ov107_020c4ecc(int obj);
extern int func_02023eb4();
extern void func_0203c634(int self, int slot, void *cb);
extern void func_ov222_020d69c0(void);
extern void func_ov222_020d6af4(void);

void func_ov222_020d6648(int self) {
    int *ctx;
    u16 v;
    int p;

    ctx = *(int **)(self + 4);

    v = *(u16 *)(ctx[0] + 0x60);
    *(u16 *)(ctx[0] + 0x60) =
        (u16)((v & ~0xff00) | (((((u32)v << 0x10) >> 0x18 | 1) << 0x18) >> 0x10));

    p = *(int *)(ctx[0] + 0x388);
    ((FlagsW *)(p + 8))->lo |= 1;

    ctx[0x11] = 0;
    *(VecFx32 *)&ctx[3] = *(VecFx32 *)(*(int *)(ctx[0] + 0x390) + 0x74);
    *(signed char *)((int)ctx + 0x64) = 0;

    switch (ctx[0x16]) {
    case 0:
        *(int *)(ctx[0] + 0x70) = 0x432;
        func_ov107_020c4ecc(ctx[0]);
        ctx[0x12] = 0x400;
        ctx[0x13] = 0x32000;
        ctx[0x15] = func_02023eb4(0x1000) + 0x2000;
        ctx[0x14] = 0x400;
        func_0203c634(self, *(signed char *)(self + 0x20), func_ov222_020d69c0);
        break;
    case 1:
        *(int *)(ctx[0] + 0x70) = 0x600;
        func_ov107_020c4ecc(ctx[0]);
        ctx[0x12] = 0x700;
        ctx[0x13] = 0x32000;
        func_0203c634(self, *(signed char *)(self + 0x20), func_ov222_020d6af4);
        break;
    }
}
