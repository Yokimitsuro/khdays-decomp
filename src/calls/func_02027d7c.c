/* func_02027d7c -- SBC Y-axis billboard command (BBY), MAIN. The game's copy of NitroSystem's
 * NNSi_G3dFuncSbc_BBY without the render callbacks: like the plain billboard (func_02027b18) it
 * reads the clip matrix (with the camera folded in when asked), keeps its translation and row
 * lengths in its own command template (data_0204288c), but also rebuilds the template rotation
 * from the normalised Y row (or the Z row when Y has no Y/Z part) so the billboard only turns
 * about the Y axis. */
typedef unsigned char u8;
typedef unsigned int u32;
typedef int fx32;
typedef volatile u32 vu32;

typedef struct { fx32 x, y, z; } VecFx32;
typedef struct { fx32 _00, _01, _02, _10, _11, _12, _20, _21, _22, _30, _31, _32; } MtxFx43;
typedef struct {
    fx32 _00, _01, _02, _03, _10, _11, _12, _13, _20, _21, _22, _23, _30, _31, _32, _33;
} MtxFx44;

typedef struct NNSG3dRS {
    const u8 *c;                        /* +0x00 */
    u32 pad04;
    u32 flag;                           /* +0x08 */
} NNSG3dRS;

typedef struct NNSG3dGlb {
    char pad00[0x4c];
    MtxFx43 cameraMtx;                  /* +0x4c */
    char pad7c[0xd4 - 0x7c];
    u32 flag;                           /* +0xd4 */
} NNSG3dGlb;

#define reg_G3X_GXFIFO (*(vu32 *)0x04000400)

#define NNS_G3D_SBCFLG_001 0x20
#define NNS_G3D_SBCFLG_010 0x40
#define NNS_G3D_SBCFLG_011 0x60
#define NNS_G3D_RSFLAG_OPT_NOGECMD      0x100
#define NNS_G3D_RSFLAG_OPT_SKIP_SBCDRAW 0x200
#define NNS_G3D_GLB_FLAG_FLUSH_WVP 1
#define NNS_G3D_GLB_FLAG_FLUSH_VP  2
#define G3OP_MTX_STORE   0x13
#define G3OP_MTX_RESTORE 0x14

extern u32 data_0204288c[];             /* bbcmd1 */
extern u32 data_02042890[];             /* &bbcmd1[1] */
extern MtxFx43 data_02042898;           /* bbcmd1[3]: rotation / translation */
extern VecFx32 data_020428bc;           /* bbcmd1[12]: trans */
extern VecFx32 data_020428c8;           /* bbcmd1[15]: scale */
extern NNSG3dGlb data_02047394;         /* NNS_G3dGlb */

extern void func_01ffa764(u32 op, u32 param);      /* one-parameter geometry buffer command */
extern void func_01ff80b8(void);                   /* NNS_G3dGeFlushBuffer */
extern int G3X_GetClipMtx(MtxFx44 *m);
extern const MtxFx43 *func_02015bc8(void);         /* NNS_G3dGlbGetSrtCameraMtx */
extern const MtxFx43 *func_02015c00(void);         /* NNS_G3dGlbGetInvSrtCameraMtx */
extern const MtxFx43 *func_020158e0(void);         /* NNS_G3dGlbGetInvCameraMtx */
extern void MTX_Copy43To44_(const MtxFx43 *pSrc, MtxFx44 *pDst);
extern void MTX_Concat44(const MtxFx44 *a, const MtxFx44 *b, MtxFx44 *ab);
extern fx32 VEC_Mag(const VecFx32 *v);
extern void func_01ff8d18(const VecFx32 *pSrc, VecFx32 *pDst);   /* VEC_Normalize */
extern void MIi_CpuSend32(const void *src, volatile void *dest, u32 size);

void func_02027d7c(NNSG3dRS *rs, u32 opt)
{
    u32 cmdLen = 2;
    MtxFx44 m;
    VecFx32 *trans = &data_020428bc;
    VecFx32 *scale = &data_020428c8;
    MtxFx43 *mtx = &data_02042898;

    if (rs->flag & NNS_G3D_RSFLAG_OPT_SKIP_SBCDRAW) {
        if (opt == NNS_G3D_SBCFLG_010 || opt == NNS_G3D_SBCFLG_011) {
            ++cmdLen;
        }
        if (opt == NNS_G3D_SBCFLG_001 || opt == NNS_G3D_SBCFLG_011) {
            ++cmdLen;
        }
        rs->c += cmdLen;
        return;
    }

    if (opt == NNS_G3D_SBCFLG_010 || opt == NNS_G3D_SBCFLG_011) {
        ++cmdLen;
        if (!(rs->flag & NNS_G3D_RSFLAG_OPT_NOGECMD)) {
            u32 idxMtxSrc;

            if (opt == NNS_G3D_SBCFLG_010) {
                idxMtxSrc = *(rs->c + 2);
            } else {
                idxMtxSrc = *(rs->c + 3);
            }
            func_01ffa764(G3OP_MTX_RESTORE, idxMtxSrc);
        }
    }

    if (!(rs->flag & NNS_G3D_RSFLAG_OPT_NOGECMD)) {
        func_01ff80b8();

        reg_G3X_GXFIFO = 0x00151110;    /* MTX_MODE, MTX_PUSH, MTX_IDENTITY */
        reg_G3X_GXFIFO = 0;             /* GX_MTXMODE_PROJECTION */
        reg_G3X_GXFIFO = 0;

        while (G3X_GetClipMtx(&m)) {
        }

        if (data_02047394.flag & NNS_G3D_GLB_FLAG_FLUSH_WVP) {
            const MtxFx43 *cam = func_02015bc8();
            MtxFx44 tmp;

            MTX_Copy43To44_(cam, &tmp);
            MTX_Concat44(&m, &tmp, &m);
        } else if (data_02047394.flag & NNS_G3D_GLB_FLAG_FLUSH_VP) {
            const MtxFx43 *cam = &data_02047394.cameraMtx;
            MtxFx44 tmp;

            MTX_Copy43To44_(cam, &tmp);
            MTX_Concat44(&m, &tmp, &m);
        }

        trans->x = m._30;
        trans->y = m._31;
        trans->z = m._32;

        scale->x = VEC_Mag((VecFx32 *)&m._00);
        scale->y = VEC_Mag((VecFx32 *)&m._10);
        scale->z = VEC_Mag((VecFx32 *)&m._20);

        if (m._11 != 0 || m._12 != 0) {
            func_01ff8d18((VecFx32 *)&m._10, (VecFx32 *)&mtx->_10);

            mtx->_21 = -mtx->_12;
            mtx->_22 = mtx->_11;
        } else {
            func_01ff8d18((VecFx32 *)&m._20, (VecFx32 *)&mtx->_20);

            mtx->_12 = -mtx->_21;
            mtx->_11 = mtx->_22;
        }

        if (data_02047394.flag & NNS_G3D_GLB_FLAG_FLUSH_WVP) {
            reg_G3X_GXFIFO = 0x00171012;    /* MTX_POP, MTX_MODE, MTX_LOAD_4x3 */
            MIi_CpuSend32(data_02042890, &reg_G3X_GXFIFO, 2 * sizeof(u32));
            MIi_CpuSend32(func_02015c00(), &reg_G3X_GXFIFO, 12 * sizeof(u32));
            reg_G3X_GXFIFO = 0x00001b19;    /* MTX_MULT_4x3, MTX_SCALE */
            MIi_CpuSend32(&data_02042898, &reg_G3X_GXFIFO, sizeof(MtxFx43) + sizeof(VecFx32));
        } else if (data_02047394.flag & NNS_G3D_GLB_FLAG_FLUSH_VP) {
            reg_G3X_GXFIFO = 0x00171012;
            MIi_CpuSend32(data_02042890, &reg_G3X_GXFIFO, 2 * sizeof(u32));
            MIi_CpuSend32(func_020158e0(), &reg_G3X_GXFIFO, 12 * sizeof(u32));
            reg_G3X_GXFIFO = 0x00001b19;
            MIi_CpuSend32(&data_02042898, &reg_G3X_GXFIFO, sizeof(MtxFx43) + sizeof(VecFx32));
        } else {
            MIi_CpuSend32(data_0204288c, &reg_G3X_GXFIFO, 18 * sizeof(u32));
        }
    }

    if (opt == NNS_G3D_SBCFLG_001 || opt == NNS_G3D_SBCFLG_011) {
        ++cmdLen;
        if (!(rs->flag & NNS_G3D_RSFLAG_OPT_NOGECMD)) {
            func_01ffa764(G3OP_MTX_STORE, *(rs->c + 2));
        }
    }

    rs->c += cmdLen;
}
