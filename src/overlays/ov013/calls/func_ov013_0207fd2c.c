typedef unsigned short u16;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct {
    int m[9];
} MtxFx33;

typedef struct {
    u16 flags;
    char padding02[0x7e];
    MtxFx33 orientation;
    char paddinga4[0x0c];
    int scaleX;
    int scaleY;
    int scaleZ;
} Ov013SpawnedSlot;

typedef struct {
    char padding00[0x250];
    VecFx32 spawnOrigin;
    char padding25c[0x56c];
    int subsystem;
    int spawnedIndex;
} Ov013Context;

extern int func_ov022_020894f8(int subsystem, int index);
extern void func_ov022_020ad44c(VecFx32 *out, Ov013Context *ctx);
extern void VEC_MultAdd(int scale, const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int func_ov022_020893f4(int subsystem, const VecFx32 *position, int zero);
extern Ov013SpawnedSlot *func_ov022_0208963c(int subsystem, int index);
extern void MTX_Identity33_(MtxFx33 *m);
extern void MTX_RotY33_(MtxFx33 *m, int sinValue, int cosValue);
extern void MTX_Concat33(const MtxFx33 *a, const MtxFx33 *b, MtxFx33 *out);
extern void MTX_RotX33_(MtxFx33 *m, int sinValue, int cosValue);

void func_ov013_0207fd2c(Ov013Context *ctx, const VecFx32 *direction) {
    VecFx32 position;
    VecFx32 adjusted;
    MtxFx33 rotY;
    MtxFx33 rotX;
    MtxFx33 identity;
    int index;
    Ov013SpawnedSlot *slot;

    if (func_ov022_020894f8(ctx->subsystem, ctx->spawnedIndex) != 0) {
        ctx->spawnedIndex = -1;
    }
    if (ctx->spawnedIndex != -1) {
        return;
    }

    position = ctx->spawnOrigin;
    func_ov022_020ad44c(&adjusted, ctx);
    position.y = adjusted.y;
    VEC_MultAdd(-0x800, direction, &position, &position);

    index = func_ov022_020893f4(ctx->subsystem, &position, 0);
    if (index < 0) {
        return;
    }
    ctx->spawnedIndex = index;
    slot = func_ov022_0208963c(ctx->subsystem, ctx->spawnedIndex);
    slot->scaleX = slot->scaleY = slot->scaleZ = 0x2000;

    MTX_Identity33_(&identity);
    MTX_RotY33_(&rotY, direction->x, direction->z);
    MTX_Concat33(&rotY, &identity, &identity);
    MTX_RotX33_(&rotX, 0x1000, 0);
    MTX_Concat33(&rotX, &identity, &slot->orientation);
    slot->flags &= ~0x20;
}

