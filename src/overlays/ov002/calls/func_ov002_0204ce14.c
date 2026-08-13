typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct {
    int radius;
    int angle;
    int verticalTargetOffset;
} Ov002OrbitParams;

typedef struct {
    char pad00[0x14];
    VecFx32 base;                  /* +0x14 */
    VecFx32 position;              /* +0x20 */
    char pad2c[0x28];
    Ov002OrbitParams orbit;         /* +0x54 */
    int verticalOffset;            /* +0x60 */
    VecFx32 computed;              /* +0x64 */
    char pad70[0x10];
    int appliedAngle;              /* +0x80 */
} Ov002MotionState;

typedef struct {
    char pad00[0x20];
    Ov002MotionState *motion;       /* +0x20 */
} Ov002Actor;

extern const short data_0203d210[];

extern void func_ov002_0204ff18(Ov002Actor *actor);
extern void func_ov002_0204cac0(Ov002Actor *actor, int reaim);

static inline int FX_Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

static inline void VEC_Copy(VecFx32 *destination, const VecFx32 *source)
{
    *destination = *source;
}

void func_ov002_0204ce14(Ov002Actor *actor, int angle)
{
    int tableIndex;
    Ov002MotionState *motion;
    int computedX;
    int computedY;
    int computedZ;
    int cosOffset;

    motion = actor->motion;
    motion->orbit.angle = angle;
    tableIndex = (motion->orbit.angle >> 4) * 2;
    cosOffset = FX_Mul(data_0203d210[tableIndex + 1], motion->orbit.radius);
    computedX = motion->base.x +
                FX_Mul(data_0203d210[tableIndex], motion->orbit.radius);
    computedZ = motion->base.z + cosOffset;
    computedY = motion->base.y + motion->orbit.verticalTargetOffset;
    motion->computed.x = computedX;
    motion->computed.y = computedY;
    motion->computed.z = computedZ;
    motion->appliedAngle = motion->orbit.angle;
    VEC_Copy(&motion->position, &motion->computed);

    func_ov002_0204ff18(actor);
    func_ov002_0204cac0(actor, 1);
}
