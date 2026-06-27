typedef int s32;
typedef unsigned int u32;
typedef volatile u32 REGType32v;

typedef struct { s32 _[16]; } MtxFx44;
typedef struct { s32 _[12]; } MtxFx43;
typedef struct { s32 _[3]; } VecFx32;

#define reg_G3_MTX_MODE       (*(REGType32v *)0x4000440)
#define reg_G3_MTX_PUSH       (*(REGType32v *)0x4000444)
#define reg_G3_MTX_POP        (*(REGType32v *)0x4000448)
#define reg_G3_MTX_IDENTITY   (*(REGType32v *)0x4000454)

extern void func_01ff80b8(void);
extern void MTX_Copy44To43_(const MtxFx44 *src, MtxFx43 *dst);
extern u32 G3X_GetClipMtx(MtxFx44 *mtx);
extern u32 G3X_GetVectorMtx(VecFx32 *mtx);

void func_02016294(MtxFx43 *pos, VecFx32 *vec) {
    MtxFx44 tmp;

    func_01ff80b8();
    reg_G3_MTX_MODE = 0;
    reg_G3_MTX_PUSH = 0;
    reg_G3_MTX_IDENTITY = 0;

    if (pos != 0) {
        while (G3X_GetClipMtx(&tmp) != 0) {}
        MTX_Copy44To43_(&tmp, pos);
    }
    if (vec != 0) {
        while (G3X_GetVectorMtx(vec) != 0) {}
    }

    reg_G3_MTX_POP = 1;
    reg_G3_MTX_MODE = 2;
}
