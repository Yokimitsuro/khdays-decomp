/* MATCHED -- rescued 2026-07-17. Was parked as a 1-register src/dst swap in the final 11-int
 * struct copy (ROM src->ip/dst->r4; mwcc reversed), ruled unbreakable across every pointer-local
 * spelling. THE FIX is the field-to-field struct copy crack (codegen-cracks.md): make BOTH ends
 * fields of their own structs -- SrcObj.pose @0xa0 and DstObj.pose @0x10 -- so the copy is
 * `((DstObj*)deref)->pose = ((SrcObj*)obj)->pose`, which picks the ROM's base order. Same crack
 * that landed ov022_0209d3a0 and ov208_020cfc04. Worth 3: ov266_020d39f0 / ov267_020d5810 twins.
 * `half` stays load-bearing (without it the two zero-stores block up front instead of interleaving
 * into the divide latency).
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

typedef struct {
    char pad[0xa0];
    Pose44 pose;
} SrcObj;

typedef struct {
    char pad[0x10];
    Pose44 pose;
} DstObj;

extern void func_0202f384(VecFx32 *dst, const void *q, const VecFx32 *v);
extern void func_ov107_020c6980(int obj, int a);

void func_ov212_020d1bfc(int obj, int a) {
    int half = -*(int *)(obj + 0x70) / 2;

    *(int *)(obj + 0x64) = 0;
    *(int *)(obj + 0x68) = 0;
    *(int *)(obj + 0x6c) = half;
    func_0202f384((VecFx32 *)(obj + 0x64), (const void *)(obj + 0xa0), (const VecFx32 *)(obj + 0x64));
    func_ov107_020c6980(obj, a);
    ((DstObj *)(*(int *)(*(int *)(obj + 0x388))))->pose = ((SrcObj *)obj)->pose;
}
