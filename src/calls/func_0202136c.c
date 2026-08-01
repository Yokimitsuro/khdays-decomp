/*
 * Anim_GetBlendFactor - map an interpolation parameter to an eased blend factor, selected by mode.
 * Called from Obj_StepMotionTransform. param_2 is the current position, param_3 the start; iVar1 =
 * param_2 - param_3 is the delta. Modes (param_1):
 *   0/1 (default): pass the mode value through unchanged (no easing here).
 *   2: FX_Inv(delta * 0x1000, param_2 << 12) - a fixed-point ratio.
 *   3: turn (delta << 15) / param_2 into an angle, normalize to [0,0x10000), look up sin in the
 *      shared {sin,cos} angle table (data_0203d210, stride 4) and return (sin + 0x1000) / 2.
 *   4: same angle from (delta << 15) / (param_2 << 1), return sin + 0x1000 (no halving).
 *   5: angle from (param_3 << 15) / (param_2 << 1) biased by +0x4000, return the raw sin.
 *
 * THUMB. Matching note: the angle normalization is `iVar1 = q -/+ 0x4000; if (iVar1 < 0) iVar1 +=
 * 0x10000;` - the wrap adds 0x10000 to the ALREADY-biased iVar1 (mwcc reuses the 0x4000 register as
 * 0x4000 << 2), NOT `q + 0xc000` recomputed from the quotient (which Ghidra's decompile shows and
 * which costs an extra movs/lsls). func_02020400 is the 64-bit divide; only its low word (quotient)
 * is used here, so it is prototyped to return int.
 */

typedef struct {
    short sin;
    short cos;
} SinCos;

extern int   FX_Inv(int a, int b);
extern int   func_02020400(int a, int b);
extern SinCos data_0203d210[];

int func_0202136c(int param_1, unsigned int param_2, int param_3)
{
    int iVar1;

    iVar1 = param_2 - param_3;
    switch (param_1) {
    case 2:
        return FX_Inv(iVar1 * 0x1000, param_2 << 0xc);
    case 3:
        iVar1 = func_02020400(iVar1 * 0x8000, param_2) - 0x4000;
        if (iVar1 < 0) {
            iVar1 = iVar1 + 0x10000;
        }
        return (data_0203d210[iVar1 >> 4].sin + 0x1000) / 2;
    case 4:
        iVar1 = func_02020400(iVar1 * 0x8000, param_2 << 1) - 0x4000;
        if (iVar1 < 0) {
            iVar1 = iVar1 + 0x10000;
        }
        return data_0203d210[iVar1 >> 4].sin + 0x1000;
    case 5:
        iVar1 = func_02020400(param_3 << 0xf, param_2 << 1) + 0x4000;
        if (iVar1 < 0) {
            iVar1 = iVar1 + 0x10000;
        }
        param_1 = data_0203d210[iVar1 >> 4].sin;
    }
    return param_1;
}
