/*
 * Ov002_ProjectPanelPoint - turn a world position into the panel's screen
 * position.
 *
 * The camera's own view matrix is rebuilt from its eye, up and target vectors,
 * concatenated with the scene's projection matrix, and the point is run through
 * the result. The x and y that come out are then scaled into the units the
 * panel widgets are placed in; z is left alone.
 *
 * ARM.
 */

typedef signed long fx32;

typedef struct {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct {
    fx32 a[12];
} MtxFx43;

typedef struct {
    fx32 a[16];
} MtxFx44;

typedef struct {
    char pad000[0x14];
    VecFx32 vTarget;
    VecFx32 vEye;
    VecFx32 vUp;
} Ov002Camera;

typedef struct {
    char pad000[0x1170];
    MtxFx44 mtxProj;
} Ov002ProjScene;

extern int data_ov002_0207f628;

extern void func_01ff9c04(const VecFx32 *pCamPos, const VecFx32 *pCamUp,
                          const VecFx32 *pTarget, MtxFx43 *pOut);
extern void MTX_Copy43To44_(const MtxFx43 *pSrc, MtxFx44 *pDst);
extern void MTX_Concat44(const MtxFx44 *pA, const MtxFx44 *pB, MtxFx44 *pDst);
extern void MTX_Copy44To43_(const MtxFx44 *pSrc, MtxFx43 *pDst);
extern void MTX_MultVec43(const VecFx32 *pVec, const MtxFx43 *pMtx,
                          VecFx32 *pOut);

void func_ov002_02060b4c(VecFx32 *pOut, const VecFx32 *pIn,
                         const Ov002Camera *pCam)
{
    MtxFx43 mView;
    MtxFx43 mFinal;
    MtxFx44 mView44;
    Ov002ProjScene *s;

    s = *(Ov002ProjScene **)&data_ov002_0207f628;
    func_01ff9c04(&pCam->vEye, &pCam->vUp, &pCam->vTarget, &mView);
    MTX_Copy43To44_(&mView, &mView44);
    MTX_Concat44(&mView44, &s->mtxProj, &mView44);
    MTX_Copy44To43_(&mView44, &mFinal);
    MTX_MultVec43(pIn, &mFinal, pOut);

    pOut->x = (fx32)(((long long)pOut->x * 0xcccd + 0x800) >> 12);
    pOut->y = (fx32)(((long long)pOut->y * 0x999a + 0x800) >> 12);
}
