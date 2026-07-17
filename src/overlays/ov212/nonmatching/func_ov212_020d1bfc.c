/* UNFINISHED -- 116/116 bytes, 29/29 instructions. Correct except ONE register swap in the final
 * struct copy. Worth 3: ov266_020d39f0 / ov267_020d5810 are byte-identical twins. (2026-07-17)
 *
 * THE ENTIRE DIFF -- src and dst swap the two registers available:
 *     ROM:  add ip, r4, #0xa0 ; ldr r4, [r0]   (src -> ip, dst -> r4)
 *     mine: add r4, r4, #0xa0 ; ldr ip, [r0]   (src -> r4, dst -> ip)
 * Both kill `obj`'s register (it is dead by then); mwcc just picks the opposite one. Everything
 * before this point matches, including the 11-int ldm/stm shape.
 *
 * RULED OUT (all byte-IDENTICAL, diff stays at 0x4D):
 *   a `src` local · a `dst` local · both locals · no locals at all
 * The `half` local IS load-bearing though and must stay -- without it the two zero-stores are
 * emitted as a block up front (diff at 0x8) instead of being interleaved into the divide's latency.
 *
 * NEXT IDEA (untried): the copy is 44 bytes = 11 ints, modelled as `struct { int v[11]; }`. Try a
 * shape that matches the real semantic layout (e.g. Quaternion + Quaternion + VecFx32 = 16+16+12)
 * -- the member types may change which operand mwcc materialises first.
 *
 * ---- what it does ----------------------------------------------------------------------------
 *
 * Centre the object on its pivot, tick it, and publish the pose.
 *
 * Shape family of 3: ov212_020d1bfc / ov266_020d39f0 / ov267_020d5810.
 *
 * The offset vector at +0x64 is set to (0, 0, -height/2) -- height being +0x70 -- and rotated by
 * the pose at +0xa0 in place, which puts the object's origin half its height below the pivot.
 * After func_ov107_020c6980 ticks it, the 44-byte pose block at +0xa0 is published into
 * *(int *)*(int *)(obj + 0x388) + 0x10.
 *
 * That copy is 11 ints, which is why the ROM does `ldm ip!/stm r4!` twice plus a 3-register tail
 * rather than a single ldm: 44 bytes is not a whole number of 4-register groups. Modelled as one
 * struct assignment so mwcc open-codes exactly that.
 *
 * `-height / 2` is a SIGNED divide by two -- the ROM's `rsb ; add r0, r0, r0, lsr #31 ; asr #1`
 * is the round-toward-zero correction. Do not simplify it to a shift. */

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct {
    int v[11];
} Pose44;

extern void func_0202f384(VecFx32 *dst, const void *q, const VecFx32 *v);
extern void func_ov107_020c6980(int obj, int a);

void func_ov212_020d1bfc(int obj, int a) {
    Pose44 *dst;
    const Pose44 *src;
    int half = -*(int *)(obj + 0x70) / 2;

    *(int *)(obj + 0x64) = 0;
    *(int *)(obj + 0x68) = 0;
    *(int *)(obj + 0x6c) = half;
    func_0202f384((VecFx32 *)(obj + 0x64), (const void *)(obj + 0xa0), (const VecFx32 *)(obj + 0x64));
    func_ov107_020c6980(obj, a);
    src = (const Pose44 *)(obj + 0xa0);
    dst = (Pose44 *)(*(int *)(*(int *)(obj + 0x388)) + 0x10);
    *dst = *src;
}
