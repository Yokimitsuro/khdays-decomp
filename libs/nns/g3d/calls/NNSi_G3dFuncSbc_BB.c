/* NNSi_G3dFuncSbc_BB -- SBC billboard command (BB) (NitroSystem G3D). NitroSystem's
 * NNSi_G3dFuncSbc_BB as built here, without the render callbacks: optionally restores the source matrix
 * (MTX_RESTORE through NNSi_G3dGeBufferCommand1), reads the current clip matrix, folds in the (SRT) camera
 * matrix when the global flags ask for it, keeps its translation and row lengths in the command
 * template (data_02042844: trans at [12], scale at [15]) and sends the template to the geometry FIFO
 * (after the inverse camera matrix when a camera is folded in); optionally stores the result
 * (MTX_STORE), then advances the command pointer. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/gx.h"

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

extern u32 data_02042844[];             /* bbcmd1 */
extern u32 data_02042848[];             /* &bbcmd1[1] */
extern u32 data_02042850[];             /* &bbcmd1[3] */
extern VecFx32 data_02042874;           /* bbcmd1[12]: trans */
extern VecFx32 data_02042880;           /* bbcmd1[15]: scale */
extern NNSG3dGlb NNS_G3dGlb;         /* NNS_G3dGlb */

extern void NNSi_G3dGeBufferCommand1(u32 op, u32 param);      /* one-parameter geometry buffer command */
extern void GXi_FlushCommandList(void);                   /* NNS_G3dGeFlushBuffer */
extern int G3X_GetClipMtx(MtxFx44 *m);
extern const MtxFx43 *GetOrInitResource749c(void);         /* NNS_G3dGlbGetSrtCameraMtx */
extern const MtxFx43 *GetOrInitResource74cc(void);         /* NNS_G3dGlbGetInvSrtCameraMtx */
extern const MtxFx43 *G3d_GetInverseCameraMtx(void);         /* NNS_G3dGlbGetInvCameraMtx */
extern void MTX_Copy43To44_(const MtxFx43 *pSrc, MtxFx44 *pDst);
extern void MTX_Concat44(const MtxFx44 *a, const MtxFx44 *b, MtxFx44 *ab);
extern fx32 VEC_Mag(const VecFx32 *v);
extern void MIi_CpuSend32(const void *src, volatile void *dest, u32 size);

void NNSi_G3dFuncSbc_BB(NNSG3dRS *rs, u32 opt)
{
    u32 cmdLen = 2;
    VecFx32 *trans = &data_02042874;
    VecFx32 *scale = &data_02042880;
    MtxFx44 m;

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
            NNSi_G3dGeBufferCommand1(G3OP_MTX_RESTORE, idxMtxSrc);
        }
    }

    if (!(rs->flag & NNS_G3D_RSFLAG_OPT_NOGECMD)) {
        GXi_FlushCommandList();

        reg_G3X_GXFIFO = 0x00151110;    /* MTX_MODE, MTX_PUSH, MTX_IDENTITY */
        reg_G3X_GXFIFO = 0;             /* GX_MTXMODE_PROJECTION */
        reg_G3X_GXFIFO = 0;

        while (G3X_GetClipMtx(&m)) {
        }

        if (NNS_G3dGlb.flag & NNS_G3D_GLB_FLAG_FLUSH_WVP) {
            const MtxFx43 *cam = GetOrInitResource749c();
            MtxFx44 tmp;

            MTX_Copy43To44_(cam, &tmp);
            MTX_Concat44(&m, &tmp, &m);
        } else if (NNS_G3dGlb.flag & NNS_G3D_GLB_FLAG_FLUSH_VP) {
            const MtxFx43 *cam = &NNS_G3dGlb.cameraMtx;
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

        if (NNS_G3dGlb.flag & NNS_G3D_GLB_FLAG_FLUSH_WVP) {
            reg_G3X_GXFIFO = 0x00171012;    /* MTX_POP, MTX_MODE, MTX_LOAD_4x3 */
            MIi_CpuSend32(data_02042848, &reg_G3X_GXFIFO, 2 * sizeof(u32));
            MIi_CpuSend32(GetOrInitResource74cc(), &reg_G3X_GXFIFO, 12 * sizeof(u32));
            reg_G3X_GXFIFO = 0x00001b19;    /* MTX_MULT_4x3, MTX_SCALE */
            MIi_CpuSend32(data_02042850, &reg_G3X_GXFIFO, sizeof(MtxFx43) + sizeof(VecFx32));
        } else if (NNS_G3dGlb.flag & NNS_G3D_GLB_FLAG_FLUSH_VP) {
            reg_G3X_GXFIFO = 0x00171012;
            MIi_CpuSend32(data_02042848, &reg_G3X_GXFIFO, 2 * sizeof(u32));
            MIi_CpuSend32(G3d_GetInverseCameraMtx(), &reg_G3X_GXFIFO, 12 * sizeof(u32));
            reg_G3X_GXFIFO = 0x00001b19;
            MIi_CpuSend32(data_02042850, &reg_G3X_GXFIFO, sizeof(MtxFx43) + sizeof(VecFx32));
        } else {
            MIi_CpuSend32(data_02042844, &reg_G3X_GXFIFO, 18 * sizeof(u32));
        }
    }

    if (opt == NNS_G3D_SBCFLG_001 || opt == NNS_G3D_SBCFLG_011) {
        ++cmdLen;
        if (!(rs->flag & NNS_G3D_RSFLAG_OPT_NOGECMD)) {
            NNSi_G3dGeBufferCommand1(G3OP_MTX_STORE, *(rs->c + 2));
        }
    }

    rs->c += cmdLen;
}
