/*
 * Obj_PrepAltTransform - set up an object's alternate transform, run from Game_UpdateObjectMotion's
 * state 1 just before committing the alternate transform block at obj+0x4c.
 *
 * Builds a base position: when the anchor index obj[0xfc] is the sentinel 0x40 the object uses its
 * own base position (obj+0x94); otherwise it takes the anchor entry's position (func_0202bfcc, entry
 * +0xa8) and adds the object's own base (VEC_Add). The result is stored into the alternate transform
 * state via func_0202e5d8(obj+0x3c, &pos) and then dispatched through func_0202e4f4 with the object's
 * command word obj[0x3b] (at obj+0xec). Finally, when any of the two spin angles (obj+0xa0 / +0xa4)
 * or the spin rate (obj+0xdc) is non-zero, it rotates the secondary point obj+0x6c about the pivot
 * obj+0x60: subtract the pivot, advance the accumulated angle obj+0x74 by the rate, build the X/Y
 * rotation matrix (func_0202119c) from the negated angles, transform, and add the pivot back. The two
 * trailing stores seed obj+0x5c/0x58 with the fixed pair (0x6a4000, 0x19a).
 *
 * THUMB. Matching notes: the position vector is a VecFx32 struct copy (ldm/stm); the anchor test is
 * written `if (obj[0xfc] != 0x40) { anchor } else { own }` so the own-position copy is the beq
 * target; func_0202e4f4 takes two arguments here (its param_3/param_4 are leftover registers, not
 * real arguments); and the first spin angle is negated eagerly into a local before VEC_Subtract so it
 * is held while the second angle is negated inline at the func_0202119c call.
 */

typedef struct { int x, y, z; } VecFx32;

extern int  func_0202bfcc(int anchorIndex);
extern void func_0202e5d8(int dst, void *src);
extern void func_0202e4f4(int dst, int cmd);
extern void VEC_Add(const void *a, const void *b, void *out);
extern void VEC_Subtract(const void *a, const void *b, void *out);
extern void func_0202119c(int *dstMtx, unsigned angleX, unsigned angleY);
extern void MTX_MultVec43(const void *v, const int *m, void *out);

void func_02021294(int param_1)
{
    VecFx32 tmp;
    int aiStack_50[12];
    int iVar1, iVar2;

    if (*(int *)(param_1 + 0xfc) != 0x40) {
        iVar1 = func_0202bfcc(*(int *)(param_1 + 0xfc) & 0xffff);
        tmp = *(VecFx32 *)(iVar1 + 0xa8);
        VEC_Add(&tmp, (int *)(param_1 + 0x94), &tmp);
    } else {
        tmp = *(VecFx32 *)(param_1 + 0x94);
    }
    func_0202e5d8(param_1 + 0x3c, &tmp);
    func_0202e4f4(param_1 + 0x3c, *(int *)(param_1 + 0xec));
    iVar1 = *(int *)(param_1 + 0xa0);
    if (iVar1 != 0 || *(int *)(param_1 + 0xa4) != 0 || *(int *)(param_1 + 0xdc) != 0) {
        iVar2 = -*(int *)(param_1 + 0xa4);
        VEC_Subtract((int *)(param_1 + 0x6c), (int *)(param_1 + 0x60), (int *)(param_1 + 0x6c));
        *(int *)(param_1 + 0x74) = *(int *)(param_1 + 0x74) + *(int *)(param_1 + 0xdc);
        func_0202119c(aiStack_50, iVar2 & 0xffff, -iVar1 & 0xffff);
        MTX_MultVec43((int *)(param_1 + 0x6c), aiStack_50, (int *)(param_1 + 0x6c));
        VEC_Add((int *)(param_1 + 0x6c), (int *)(param_1 + 0x60), (int *)(param_1 + 0x6c));
    }
    *(int *)(param_1 + 0x5c) = 0x006a4000;
    *(int *)(param_1 + 0x58) = 0x0000019a;
}
