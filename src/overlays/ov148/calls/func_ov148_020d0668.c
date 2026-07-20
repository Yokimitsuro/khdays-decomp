/* Fire a three-way spread from the owner's heading.
 *
 * Turn the Q12 radian at self+0x34 into a sin/cos table index (see
 * func_ov137_020cc9e0 for the full write-up of that conversion), build the unit XZ
 * direction from it, then rotate it +0x860 and walk it back down in 0x860 steps: the
 * three nodes at owner+0x398 are launched at +0x860, 0 and -0x860 around the heading.
 * The caller's `height` is written into the direction's Y before each launch, so the
 * rotation only ever acts on the flat XZ part.
 *
 * The second rotation quaternion is built ONCE, before the loop, with the negated angle,
 * and re-applied between launches -- so the last iteration deliberately skips it.
 *
 * TWO CODEGEN POINTS, both about things that look like scheduling and are not:
 *  - DECLARATION ORDER sets the stack layout.  The ROM has the direction at sp+0 and the
 *    quaternion at sp+0xc; mwcc gives the LOWER address to the LATER declaration, so the
 *    Xform must be declared before the Vec3.  Declared the other way the whole frame is
 *    mirrored and every access offset is wrong.
 *  - the node index must stay a displacement: `(char *)*self + i * sizeof(int)` with the
 *    +0x398 applied at the access.  Folding the base in as `((int *)(*self + 0x398))[i]`
 *    costs a register for the byte offset (`add r0, r0, r6` instead of the ROM's
 *    `add r0, r0, r4, lsl #2`), which spills into an EIGHTH callee-saved register and an
 *    extra push -- 12 bytes.  Same lever as the Tally families.
 */
typedef struct { int v[4]; } Xform;
typedef struct { int x, y, z; } Vec3;

extern void func_0202f188(Xform *out, const Xform *src, int angle);
extern void func_0202f384(Vec3 *dst, const Xform *x, const Vec3 *src);
extern void func_ov148_020d18dc(int node, int arg, Vec3 *dir);
extern Xform data_02042264;
extern const short data_0203d210[];

void func_ov148_020d0668(int *self, int height, int arg) {
    Xform rot;
    Vec3 dir;
    int i;
    int idx;

    idx = (unsigned short)(((long long)self[0xd] * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4;
    dir.x = data_0203d210[idx * 2];
    dir.y = 0;
    dir.z = data_0203d210[idx * 2 + 1];

    func_0202f188(&rot, &data_02042264, 0x860);
    func_0202f384(&dir, &rot, &dir);
    func_0202f188(&rot, &data_02042264, -0x860);

    for (i = 0; i < 3; i++) {
        dir.y = height;
        func_ov148_020d18dc(*(int *)((char *)*self + i * sizeof(int) + 0x398), arg, &dir);
        if (i + 1 < 3) {
            func_0202f384(&dir, &rot, &dir);
        }
    }
}
