typedef struct FxVec3_020b0c24 {
    int x;
    int y;
    int z;
} FxVec3_020b0c24;

typedef struct ScaleControl_020b0c24 {
    unsigned char padding_00[0x13];
    unsigned char flags_13;
} ScaleControl_020b0c24;

typedef struct FxScalar_020b0c24 {
    int value;
} FxScalar_020b0c24;

typedef union FxAngle_020b0c24 {
    int input;
    int output;
} FxAngle_020b0c24;

static inline int FX32_CAST_020b0c24(long long result)
{
    return (int)result;
}

static inline int FX_MulInline_020b0c24(int v1, int v2)
{
    return FX32_CAST_020b0c24(((long long)v1 * v2 + 0x800LL) >> 12);
}

#pragma opt_propagation on
#pragma opt_dead_assignments on
static inline int ClampOffset_020b0c24(int value)
{
    if (value < -0x1000) {
        value = -0x1000;
    }
    if (0x1000 < value) {
        value = 0x1000;
    }
    return value;
}

static inline void ScalePrefix_020b0c24(
    ScaleControl_020b0c24 *control,
    FxVec3_020b0c24 *vector,
    FxScalar_020b0c24 *scalar,
    int scale)
{
    const FxVec3_020b0c24 *input = vector;
    FxVec3_020b0c24 *output = vector;
    const FxScalar_020b0c24 *scalarInput = scalar;
    FxScalar_020b0c24 *scalarOutput = scalar;

    if ((control->flags_13 & 1) != 0) {
        output->x = (int)(((long long)input->x * scale + 0x800LL) >> 12);
    }
    if ((control->flags_13 & 2) != 0) {
        output->y = (int)(((long long)input->y * scale + 0x800LL) >> 12);
    }
    if ((control->flags_13 & 4) != 0) {
        output->z = (int)(((long long)input->z * scale + 0x800LL) >> 12);
    }
    if ((control->flags_13 & 8) != 0) {
        scalarOutput->value = (int)(
            ((long long)scalarInput->value * scale + 0x800LL) >> 12);
    }
}

#pragma opt_propagation off
#pragma opt_dead_assignments on
void func_ov022_020b0c24(
    ScaleControl_020b0c24 *arg0,
    FxVec3_020b0c24 *arg1,
    FxScalar_020b0c24 *arg2,
    FxAngle_020b0c24 *arg3,
    int arg4)
{
    int scale = (short)arg4;

    if (scale <= 0x400) {
        scale = 0x1000;
    }
    ScalePrefix_020b0c24(arg0, arg1, arg2, scale);
    if ((arg0->flags_13 & 0x10) == 0) {
        return;
    }
    arg3->output = ClampOffset_020b0c24(
        FX_MulInline_020b0c24(arg3->input + 0x1000, scale) - 0x1000);
}
#pragma opt_propagation on
