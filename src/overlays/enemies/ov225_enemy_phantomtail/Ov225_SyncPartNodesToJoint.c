/* Joint callback: moves the two nodes of the selected body part (+0x3ac.. / +0x3c0..) to the
 * current joint matrix. NNS_G3dGetCurrentMtx fills one 4x3 matrix, whose last row is the
 * joint's translation. */

#include "nitro/fx.h"

extern void NNS_G3dGetCurrentMtx(MtxFx43 *m, MtxFx33 *n);
extern void Srt_SetTranslation(void *transform, const VecFx32 *translation);

struct Obj {
    char pad0[4];
    void *field4;
    int field8;
    char pad_c[0xae - 0xc];
    unsigned char byteAE;
};

struct Sub {
    char pad[0x3ac];
    void **f3ac;       /* +0x3ac */
    void **f3b0;       /* +0x3b0 */
    void **f3b4;       /* +0x3b4 */
    void **f3b8;       /* +0x3b8 */
    void **f3bc;       /* +0x3bc */
    char *f3c0;        /* +0x3c0 */
    char *f3c4;        /* +0x3c4 */
    char *f3c8;        /* +0x3c8 */
    char *f3cc;        /* +0x3cc */
    char *f3d0;        /* +0x3d0 */
    int f3d4;          /* +0x3d4 */
    int f3d8;          /* +0x3d8 */
    int f3dc;          /* +0x3dc */
    int f3e0;          /* +0x3e0 */
    int f3e4;          /* +0x3e4 */
};

void Ov225_SyncPartNodesToJoint(struct Obj *a)
{
    struct Sub *s;
    int sel;
    MtxFx43 mtx;

    s = *(struct Sub **)(((char *)a->field4) + 0x2c);

    if (a->field8 & 0x10) {
        sel = a->byteAE;
    } else {
        sel = -1;
    }

    if (sel == s->f3d8) {
        NNS_G3dGetCurrentMtx(&mtx, 0);
        Srt_SetTranslation((char *)(*s->f3ac) + 0x10, (const VecFx32 *)&mtx._30);
        Srt_SetTranslation(s->f3c0 + 0x10, (const VecFx32 *)&mtx._30);
        return;
    }
    if (sel == s->f3dc) {
        NNS_G3dGetCurrentMtx(&mtx, 0);
        Srt_SetTranslation((char *)(*s->f3b4) + 0x10, (const VecFx32 *)&mtx._30);
        Srt_SetTranslation(s->f3c8 + 0x10, (const VecFx32 *)&mtx._30);
        return;
    }
    if (sel == s->f3d4) {
        NNS_G3dGetCurrentMtx(&mtx, 0);
        Srt_SetTranslation((char *)(*s->f3b0) + 0x10, (const VecFx32 *)&mtx._30);
        Srt_SetTranslation(s->f3c4 + 0x10, (const VecFx32 *)&mtx._30);
        return;
    }
    if (sel == s->f3e0) {
        NNS_G3dGetCurrentMtx(&mtx, 0);
        Srt_SetTranslation((char *)(*s->f3b8) + 0x10, (const VecFx32 *)&mtx._30);
        Srt_SetTranslation(s->f3cc + 0x10, (const VecFx32 *)&mtx._30);
        return;
    }
    if (sel == s->f3e4) {
        NNS_G3dGetCurrentMtx(&mtx, 0);
        Srt_SetTranslation((char *)(*s->f3bc) + 0x10, (const VecFx32 *)&mtx._30);
        Srt_SetTranslation(s->f3d0 + 0x10, (const VecFx32 *)&mtx._30);
        return;
    }
}
