/*
 * Camera_CommitMatrices - build the projection and view matrices for a camera actor and
 * cache its source vectors, called from Game_UpdateObjectMotion (state 0 commits the
 * object's base transform block at obj+4).
 *
 * Steps:
 *  - Camera_BuildProjectionMtx builds the perspective/projection matrix into data_0204739c from the
 *    actor's projection inputs (the four words at +0x00, the near/far bound at +0x10, and
 *    the fixed FX32_ONE scale 0x1000);
 *  - clears GX dirty bits 0x50 in the camera flags word;
 *  - caches the eye/up/target vectors (actor +0x20 / +0x2c / +0x14) into the global camera
 *    state (data_020475ac / b8 / c4);
 *  - MTX_LookAt = MTX_LookAt(&pos, &up, &target, data_020473e0) builds the view matrix;
 *  - clears GX dirty bits 0xe8.
 *
 * ARM. Codegen note: Camera_BuildProjectionMtx takes the four projection words as SEPARATE scalar
 * arguments, not as one 16-byte struct passed by value. That distinction drives the whole
 * basic block's list scheduler: with the scalar form the two look-at address computes
 * (add for +0x2c and +0x14) cluster together before the second vector copy and the view
 * matrix's pool word is loaded last, exactly as the ROM does. A struct-by-value first
 * argument (which loads the four words with a single ldm into r0-r3) perturbs the schedule
 * and reorders the three-vector copy block by ~7 instructions. The three cached vectors are
 * modelled as fields of one camera-state struct so mwcc keeps them a single aliasing region
 * (separate globals batch the two destination pool loads and mis-order the block).
 */

/* Camera actor: projection setup words at the top, then the look-at points. */

#include "nitro/fx_types.h"

typedef struct {
    int     projParams[4];  /* +0x00: perspective build inputs */
    int     f10;            /* +0x10: near/far bound */
    VecFx32 target;         /* +0x14: look-at target */
    VecFx32 pos;            /* +0x20: eye position */
    VecFx32 up;             /* +0x2c: up / orientation */
} CamActor;

/* Global camera-commit state (GX dirty flags + cached vectors, at NNS_G3dGlb). */
extern struct {
    char    _p00[0xd4];
    int     flags;          /* +0xd4 */
    char    _pd8[0x218-0xd8];
    VecFx32 cachePos;       /* +0x218 (data_020475ac) */
    VecFx32 cacheUp;        /* +0x224 (data_020475b8) */
    VecFx32 cacheTarget;    /* +0x230 (data_020475c4) */
} NNS_G3dGlb;

extern char data_0204739c[];   /* projection matrix output */
extern char data_020473e0[];   /* view (look-at) matrix output */

extern void Camera_BuildProjectionMtx(int a, int b, int c, int d, int e, int scale, void *projOut);
extern void MTX_LookAt(const VecFx32 *pos, const VecFx32 *up, const VecFx32 *target,
                          void *viewOut);

void Camera_CommitMatrices(CamActor *cam)
{
    Camera_BuildProjectionMtx(cam->projParams[0], cam->projParams[1], cam->projParams[2],
                  cam->projParams[3], cam->f10, 0x1000, data_0204739c);
    NNS_G3dGlb.flags &= ~0x50;
    NNS_G3dGlb.cachePos = cam->pos;
    NNS_G3dGlb.cacheUp = cam->up;
    NNS_G3dGlb.cacheTarget = cam->target;
    MTX_LookAt(&cam->pos, &cam->up, &cam->target, data_020473e0);
    NNS_G3dGlb.flags &= ~0xe8;
}
