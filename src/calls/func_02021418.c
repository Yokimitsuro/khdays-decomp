/*
 * Obj_StepMotionTransform - evaluate one frame of an object's animated SRT (scale / rotation /
 * translation) and either write it back into the object or return the components through out-params.
 * Called from Game_UpdateObjectMotion's default state with (obj, 0, 0, 0, 0).
 *
 * param_1 = the object. The animation is driven by a countdown timer at param_1[0x3c]:
 *   - timer counts down each self-update frame (param_3 == 0);
 *   - while running, func_0202136c yields the blend factor t from the timer/curve ids
 *     (param_1[0x3e], param_1[0x3d]);
 *   - timer == 0: snap to the target pose (scale param_1[0x25..0x27], angles param_1[0x28..0x2a],
 *     scalars param_1[0x37]/[0x38]);
 *   - *param_1 == 0: scale-around-pivot blend of each component (func_02021404);
 *   - else: eased interpolation using per-component curve tables from the class *param_1
 *     (func_02021208).
 * param_1[0x3f] is a parent/anchor index: when != 0x40 the anchor entry (func_0202bfcc) contributes
 * its position (entry+0xa8) to the object's translation.
 *
 * Self-update (param_3 == 0): stores the translation into param_1[6..8], builds the rotation matrix
 * (func_0202119c) into scratch, transforms/adds the translation into param_1[9..0xc], and stores
 * sin/cos of the final Z angle (iVar2) from the global angle table data_0203d210 into param_1[1..2].
 * Query mode (param_3 != 0): returns rotation in param_3, scale in param_2, and the two scalars in
 * param_4 / param_5.
 *
 * THUMB. Matching notes: the SRT vectors are copied as VecFx32 struct assignments so the moves emit
 * ldm/stm (scalar assignment gives ldr/str and the wrong size); func_0202136c takes the timer
 * param_1[0x3c] as a third argument (mwcc loads it into r2 for the `timer > 0` test and reuses it as
 * the call arg); every anchor test is `if (param_1[0x3f] != 0x40) { anchor } else { vPos = vScale }`
 * so the vPos=vScale copy is the beq target; the eased-interp branch is written first
 * (`else if (*param_1 != 0)`) so it is the fall-through and scale-around-pivot is the far block; the
 * self-update tail is `if (param_3 == 0) { ...; return; }` so the matrix path is inline and the
 * out-param path is the bne-far block. In the sin/cos tail the angle-table index i2 = (angle>>4)*2 is
 * a local ASSIGNED AFTER the param_1[0xc] store: that keeps i2 a shared CSE (used for both the sin
 * offset i2*2 and the cos offset (i2+1)*2, matching the ROM's single (angle>>4)*2 value) while
 * scheduling its computation after the store like the ROM. Hoisting i2 to the block head, or folding
 * it into (angle>>4)*4, moves the shift before the literal pool and permutes the r0/r1 pair.
 */

typedef struct { int x, y, z; } VecFx32;

extern short data_0203d210[];   /* global {s16 sin, s16 cos} angle table, 4 bytes per entry */
extern int  func_0202136c(int curveId, int timerId, int timer);
extern int  func_0202bfcc(int anchorIndex);
extern int  func_02021208(int t, int target, int curve, int base);
extern int  func_02021404(int t, int base, int target);
extern void func_0202119c(int *dstMtx, unsigned angleX, unsigned angleY);
extern void VEC_Add(const void *a, const void *b, void *out);
extern void VEC_Subtract(const void *a, const void *b, void *out);
extern void VEC_MultAdd(int t, const void *a, const void *b, void *out);
extern void MTX_MultVec43(const void *v, const int *m, void *out);

void func_02021418(int *param_1, int *param_2, int *param_3, int *param_4, int *param_5)
{
    int iVar2, iVar3;
    unsigned uVar4;
    unsigned local_70;
    int local_74, local_78;
    VecFx32 vPos;
    int aiStack_30[3];
    int aiStack_60[12];
    VecFx32 vScale;

    iVar2 = 0;
    if (param_3 == 0 && 0 < param_1[0x3c]) {
        param_1[0x3c] = param_1[0x3c] - 1;
    }
    if (0 < param_1[0x3c]) {
        iVar2 = func_0202136c(param_1[0x3e], param_1[0x3d], param_1[0x3c]);
    }
    if (param_1[0x3c] == 0) {
        vScale = *(VecFx32 *)(param_1 + 0x25);
        if (param_1[0x3f] != 0x40) {
            iVar2 = func_0202bfcc(param_1[0x3f] & 0xffff);
            vPos = *(VecFx32 *)(iVar2 + 0xa8);
            VEC_Add(&vPos, &vScale, &vPos);
        } else {
            vPos = vScale;
        }
        local_70 = -param_1[0x29];
        uVar4 = -param_1[0x28];
        local_78 = param_1[0x2a];
        local_74 = param_1[0x37];
        iVar2 = param_1[0x38];
    } else if (*param_1 != 0) {
        iVar2 = iVar2 * 2;
        vScale.x = func_02021208(iVar2, param_1[0x2b], *(int *)(*param_1 + 0x94), param_1[0x25]);
        vScale.y = func_02021208(iVar2, param_1[0x2c], *(int *)(*param_1 + 0x98), param_1[0x26]);
        vScale.z = func_02021208(iVar2, param_1[0x2d], *(int *)(*param_1 + 0x9c), param_1[0x27]);
        if (param_1[0x3f] != 0x40) {
            iVar3 = func_0202bfcc(param_1[0x3f] & 0xffff);
            vPos = *(VecFx32 *)(iVar3 + 0xa8);
            VEC_Add(&vPos, &vScale, &vPos);
        } else {
            vPos = vScale;
        }
        iVar3 = func_02021208(iVar2, param_1[0x31], *(int *)(*param_1 + 0x18), vPos.x);
        param_1[6] = iVar3;
        iVar3 = func_02021208(iVar2, param_1[0x32], *(int *)(*param_1 + 0x1c), vPos.y);
        param_1[7] = iVar3;
        iVar3 = func_02021208(iVar2, param_1[0x33], *(int *)(*param_1 + 0x20), vPos.z);
        param_1[8] = iVar3;
        iVar3 = func_02021208(iVar2, param_1[0x2f], *(int *)(*param_1 + 0xa4), param_1[0x29]);
        local_70 = -iVar3;
        iVar3 = func_02021208(iVar2, param_1[0x2e], *(int *)(*param_1 + 0xa0), param_1[0x28]);
        uVar4 = -iVar3;
        local_78 = func_02021208(iVar2, param_1[0x30], *(int *)(*param_1 + 0xa8), param_1[0x2a]);
        local_74 = func_02021208(iVar2, param_1[0x39], *(int *)(*param_1 + 0xdc), param_1[0x37]);
        if (local_74 < 0x19a) {
            local_74 = 0x19a;
        }
        iVar2 = func_02021208(iVar2, param_1[0x3a], *(int *)(*param_1 + 0xe0), param_1[0x38]);
    } else {
        vScale.x = func_02021404(iVar2, param_1[0x25], param_1[0x2b]);
        vScale.y = func_02021404(iVar2, param_1[0x26], param_1[0x2c]);
        vScale.z = func_02021404(iVar2, param_1[0x27], param_1[0x2d]);
        if (param_1[0x3f] != 0x40) {
            iVar3 = func_0202bfcc(param_1[0x3f] & 0xffff);
            vPos = *(VecFx32 *)(iVar3 + 0xa8);
            VEC_Add(&vPos, &vScale, &vPos);
        } else {
            vPos = vScale;
        }
        VEC_Subtract(&vPos, param_1 + 0x31, aiStack_30);
        VEC_MultAdd(iVar2, aiStack_30, param_1 + 0x31, param_1 + 6);
        iVar3 = func_02021404(iVar2, param_1[0x29], param_1[0x2f]);
        local_70 = -iVar3;
        iVar3 = func_02021404(iVar2, param_1[0x28], param_1[0x2e]);
        uVar4 = -iVar3;
        local_78 = func_02021404(iVar2, param_1[0x2a], param_1[0x30]);
        local_74 = func_02021404(iVar2, param_1[0x37], param_1[0x39]);
        iVar2 = func_02021404(iVar2, param_1[0x38], param_1[0x3a]);
    }
    *(VecFx32 *)(param_1 + 6) = vPos;
    if (param_3 == 0) {
        func_0202119c(aiStack_60, local_70 & 0xffff, uVar4 & 0xffff);
        param_1[9] = 0;
        param_1[10] = 0;
        param_1[0xb] = local_74;
        MTX_MultVec43(param_1 + 9, aiStack_60, param_1 + 9);
        VEC_Add(param_1 + 9, param_1 + 6, param_1 + 9);
        {
            int i2;
            param_1[0xc] = local_78;
            i2 = (iVar2 >> 4) * 2;
            param_1[1] = *(short *)((char *)data_0203d210 + i2 * 2);
            param_1[2] = *(short *)((char *)data_0203d210 + (i2 + 1) * 2);
        }
        return;
    }
    *param_3 = -uVar4;
    param_3[1] = -local_70;
    param_3[2] = local_78;
    if (param_2 != 0) {
        *(VecFx32 *)param_2 = vScale;
    }
    if (param_4 != 0) {
        *param_4 = local_74;
    }
    if (param_5 != 0) {
        *param_5 = iVar2;
    }
}
