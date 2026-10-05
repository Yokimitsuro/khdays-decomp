/*
 * Ov002_UpdateSceneFrame - one frame of the scene: draw it, then mask it.
 *
 * Derives the visible rectangle from the scene context - the two extents at
 * +0x28 and +0x2c are the fade timer scaled by two and by three - resets the
 * view, draws the scene's own quad, then sets up the 2D projection and camera
 * targets. Once the flags say the scene is live and its slot is still empty it
 * bumps a settle counter and raises bit 4 on the second frame. Finally it
 * blacks out the four margins around the visible rectangle and commits the
 * camera matrices.
 *
 * ARM. The half-extents are a signed divide by two, so each is rounded toward
 * zero before the shift, and the rectangle bounds come out as >>12 of the
 * centre plus and minus that half. Both halves are computed before either is
 * used, which is what interleaves the two multiply chains the way the ROM has
 * them.
 *
 * The zero target vector needs its initialiser: plain field assignments let
 * mwcc fold the offsets into each store and lose the base register the ROM
 * computes. But a declaration initialiser at function scope is emitted ahead
 * of the first call, so the vector is declared in an inner scope that opens
 * exactly where the ROM zeroes it.
 */

#include "nitro/fx_types.h"

extern int func_ov022_02083f0c(void);
extern void Ov002_ResetViewToDefault(void);          /* reset the view */
extern void Ov002_ResourceEntryCallback(int nName);     /* draw the scene's own quad */
extern void MTX_OrthoW(int a, int b, int c, int d, int e, int f, int g,
                          void *pProjOut);
extern void NNS_G3dGlbSetBaseScale(const VecFx32 *v);    /* secondary camera target */
extern void NNS_G3dGlbSetBaseTrans(const VecFx32 *v);    /* primary camera target */
extern void NNS_G3dGlbFlushP(void);
extern void Ov002_DrawFlatRect(int nX0, int nY0, int nX1, int nY1, int nZ);
extern void *Ov002_GetWord20(int nHandle);
extern void Camera_CommitMatrices(void *pCam);          /* commit the matrices */

extern char data_0204739c[];                    /* projection matrix output */
extern int data_ov002_0207db5c[];               /* the fixed secondary target */
extern int data_ov002_0207f600;                 /* slot holding the scene context */

extern struct {
    char         _p00[0xd4];
    unsigned int flags;                         /* +0xd4 */
} NNS_G3dGlb;

void Ov002_UpdateSceneFrame(void)
{
    int *pCtx;
    int nHandle;
    VecFx32 vScale;
    int nHalfX;
    int nHalfY;
    int nLeft;
    int nRight;
    int nTop;
    int nBottom;
    void *pCam;

    nHandle = func_ov022_02083f0c();
    *(int *)(data_ov002_0207f600 + 0x28) =
        *(int *)(data_ov002_0207f600 + 4) << 1;
    *(int *)(data_ov002_0207f600 + 0x2c) =
        *(int *)(data_ov002_0207f600 + 4) * 3;
    Ov002_ResetViewToDefault();
    Ov002_ResourceEntryCallback(data_ov002_0207f600 + 0x10);

    vScale = *(VecFx32 *)data_ov002_0207db5c;
    {
        VecFx32 vTarget = {0, 0, 0};

        pCtx = (int *)data_ov002_0207f600;
        MTX_OrthoW(0, 0x3000, 0, 0x4000, 0, 0x1000, 0x400000, data_0204739c);
        NNS_G3dGlb.flags &= ~0x50;

        nHalfX = (int)*(short *)((char *)pCtx + 0x14)
                 * *(int *)((char *)pCtx + 0x28) / 2;
        nHalfY = (int)*(short *)((char *)pCtx + 0x16)
                 * *(int *)((char *)pCtx + 0x2c) / 2;
        nLeft = (*(int *)((char *)pCtx + 0x20) - nHalfX) >> 12;
        nRight = (*(int *)((char *)pCtx + 0x20) + nHalfX) >> 12;
        nTop = (*(int *)((char *)pCtx + 0x24) - nHalfY) >> 12;
        nBottom = (*(int *)((char *)pCtx + 0x24) + nHalfY) >> 12;

        NNS_G3dGlbSetBaseScale(&vScale);
        NNS_G3dGlbSetBaseTrans(&vTarget);
        NNS_G3dGlbFlushP();

        pCtx = (int *)data_ov002_0207f600;
        if ((*(unsigned int *)pCtx & 1) != 0
            && *(int *)((char *)pCtx + 0x40) == 0) {
            *(unsigned char *)((char *)pCtx + 0x44) =
                *(unsigned char *)((char *)pCtx + 0x44) + 1;
            pCtx = (int *)data_ov002_0207f600;
            if (*(unsigned char *)((char *)pCtx + 0x44) >= 2) {
                *(unsigned int *)pCtx = *(unsigned int *)pCtx | 0x10;
            }
        }

        if (nTop > 0) {
            Ov002_DrawFlatRect(0, 0, 0x100, nTop, 0);
        }
        if (nBottom < 0xc0) {
            Ov002_DrawFlatRect(0, nBottom, 0x100, 0xc0, 0);
        }
        if (nLeft > 0) {
            Ov002_DrawFlatRect(0, 0, nLeft, 0xc0, 0);
        }
        if (nRight < 0x100) {
            Ov002_DrawFlatRect(nRight, 0, 0x100, 0xc0, 0);
        }

        pCam = Ov002_GetWord20(nHandle);
        Camera_CommitMatrices(pCam);
    }
}
