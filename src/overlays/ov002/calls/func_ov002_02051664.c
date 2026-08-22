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

typedef struct { int x, y, z; } VecFx32;

extern int func_ov022_02083f0c(void);
extern void func_ov002_02050e64(void);          /* reset the view */
extern void func_ov002_0205126c(int nName);     /* draw the scene's own quad */
extern void func_02004eac(int a, int b, int c, int d, int e, int f, int g,
                          void *pProjOut);
extern void func_020158b0(const VecFx32 *v);    /* secondary camera target */
extern void func_02015880(const VecFx32 *v);    /* primary camera target */
extern void func_020157c4(void);
extern void func_ov002_02051528(int nX0, int nY0, int nX1, int nY1, int nZ);
extern void *func_ov002_0204cb68(int nHandle);
extern void func_02023cc0(void *pCam);          /* commit the matrices */

extern char data_0204739c[];                    /* projection matrix output */
extern int data_ov002_0207db5c[];               /* the fixed secondary target */
extern int data_ov002_0207f600;                 /* slot holding the scene context */

extern struct {
    char         _p00[0xd4];
    unsigned int flags;                         /* +0xd4 */
} data_02047394;

void func_ov002_02051664(void)
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
    func_ov002_02050e64();
    func_ov002_0205126c(data_ov002_0207f600 + 0x10);

    vScale = *(VecFx32 *)data_ov002_0207db5c;
    {
        VecFx32 vTarget = {0, 0, 0};

        pCtx = (int *)data_ov002_0207f600;
        func_02004eac(0, 0x3000, 0, 0x4000, 0, 0x1000, 0x400000, data_0204739c);
        data_02047394.flags &= ~0x50;

        nHalfX = (int)*(short *)((char *)pCtx + 0x14)
                 * *(int *)((char *)pCtx + 0x28) / 2;
        nHalfY = (int)*(short *)((char *)pCtx + 0x16)
                 * *(int *)((char *)pCtx + 0x2c) / 2;
        nLeft = (*(int *)((char *)pCtx + 0x20) - nHalfX) >> 12;
        nRight = (*(int *)((char *)pCtx + 0x20) + nHalfX) >> 12;
        nTop = (*(int *)((char *)pCtx + 0x24) - nHalfY) >> 12;
        nBottom = (*(int *)((char *)pCtx + 0x24) + nHalfY) >> 12;

        func_020158b0(&vScale);
        func_02015880(&vTarget);
        func_020157c4();

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
            func_ov002_02051528(0, 0, 0x100, nTop, 0);
        }
        if (nBottom < 0xc0) {
            func_ov002_02051528(0, nBottom, 0x100, 0xc0, 0);
        }
        if (nLeft > 0) {
            func_ov002_02051528(0, 0, nLeft, 0xc0, 0);
        }
        if (nRight < 0x100) {
            func_ov002_02051528(nRight, 0, 0x100, 0xc0, 0);
        }

        pCam = func_ov002_0204cb68(nHandle);
        func_02023cc0(pCam);
    }
}
