/* func_020280a4 -- SBC environment-map command (ENVMAP), MAIN. The game's copy of NitroSystem's
 * NNSi_G3dFuncSbc_ENVMAP without the render callbacks: for a visible node it forces the material's
 * texture coordinate generation to "normal" (resending TEXIMAGE_PARAM when it changes), loads the
 * texture matrix with the texture-size scale and centre offset, multiplies in the material's effect
 * matrix when it has one, then multiplies in the camera (and base rotation) and the current
 * normal matrix; the command pointer always advances by 3. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef int fx32;

typedef struct { fx32 x, y, z; } VecFx32;
typedef struct { fx32 _00, _01, _02, _10, _11, _12, _20, _21, _22; } MtxFx33;
typedef struct { fx32 _00, _01, _02, _10, _11, _12, _20, _21, _22, _30, _31, _32; } MtxFx43;
typedef struct {
    fx32 _00, _01, _02, _03, _10, _11, _12, _13, _20, _21, _22, _23, _30, _31, _32, _33;
} MtxFx44;

typedef struct NNSG3dResDict {
    u8 revision;                        /* +0x00 */
    u8 numEntry;                        /* +0x01 */
    u16 sizeDictBlk;                    /* +0x02 */
    u16 dummy_;                         /* +0x04 */
    u16 ofsEntry;                       /* +0x06 */
} NNSG3dResDict;

typedef struct NNSG3dResDictEntryHeader {
    u16 sizeUnit;                       /* +0x00 */
    u16 sizeName;                       /* +0x02 */
    u8 data[4];                         /* +0x04 */
} NNSG3dResDictEntryHeader;

typedef struct NNSG3dResDictMatData {
    u32 offset;                         /* +0x00 */
} NNSG3dResDictMatData;

typedef struct NNSG3dResMat {
    u16 ofsDictTexToMatList;            /* +0x00 */
    u16 ofsDictPlttToMatList;           /* +0x02 */
    NNSG3dResDict dict;                 /* +0x04 */
} NNSG3dResMat;

typedef struct NNSG3dResMatData {
    char pad00[0x1e];
    u16 flag;                           /* +0x1e */
    char pad20[0x2c - 0x20];
} NNSG3dResMatData;

typedef struct NNSG3dMatAnmResult {
    char pad00[0x10];
    u32 prmTexImage;                    /* +0x10 */
    char pad14[0x2c - 0x14];
    u16 origWidth;                      /* +0x2c */
    u16 origHeight;                     /* +0x2e */
} NNSG3dMatAnmResult;

typedef struct NNSG3dRS {
    const u8 *c;                        /* +0x00 */
    u32 pad04;
    u32 flag;                           /* +0x08 */
    char pad0c[0xb0 - 0x0c];
    NNSG3dMatAnmResult *pMatAnmResult;  /* +0xb0 */
    char padb4[0xd8 - 0xb4];
    const NNSG3dResMat *pResMat;        /* +0xd8 */
} NNSG3dRS;

typedef struct NNSG3dGlb {
    char pad00[0x4c];
    MtxFx43 cameraMtx;                  /* +0x4c */
    char pad7c[0x94 - 0x7c];
    MtxFx33 prmBaseRot;                 /* +0x94 */
    char padb8[0xd4 - 0xb8];
    u32 flag;                           /* +0xd4 */
} NNSG3dGlb;

#define NNS_G3D_RSFLAG_NODE_VISIBLE     0x001
#define NNS_G3D_RSFLAG_OPT_SKIP_SBCDRAW 0x200
#define NNS_G3D_GLB_FLAG_FLUSH_WVP 1
#define NNS_G3D_GLB_FLAG_FLUSH_VP  2
#define NNS_G3D_MATFLAG_TEXMTX_SCALEONE  0x0002
#define NNS_G3D_MATFLAG_TEXMTX_ROTZERO   0x0004
#define NNS_G3D_MATFLAG_TEXMTX_TRANSZERO 0x0008
#define NNS_G3D_MATFLAG_EFFECTMTX        0x2000
#define REG_G3_TEXIMAGE_PARAM_TGEN_MASK  0xc0000000
#define REG_G3_TEXIMAGE_PARAM_TGEN_SHIFT 30
#define GX_TEXGEN_NORMAL 2
#define GX_MTXMODE_POSITION_VECTOR 2
#define GX_MTXMODE_TEXTURE         3
#define G3OP_MTX_MODE     0x10
#define G3OP_MTX_MULT_4x4 0x18
#define G3OP_MTX_MULT_3x3 0x1a
#define G3OP_MTX_SCALE    0x1b
#define G3OP_TEXCOORD     0x22
#define GX_FX16ST(x) ((short)((x) >> 8))
#define GX_ST(s, t) ((u32)((u16)GX_FX16ST(s) | ((u16)GX_FX16ST(t) << 16)))
#define GX_PACK_TEXCOORD_PARAM(s, t) (GX_ST((s), (t)))

extern u32 data_020427f4[];             /* [2..3]: TEXIMAGE_PARAM command template */
extern u32 data_02042800[];             /* its parameter word */
extern NNSG3dGlb data_02047394;         /* NNS_G3dGlb */

extern void func_01ff9f00(u32 op, const u32 *args, u32 num);    /* NNS_G3dGeBufferOP_N */
extern void func_02016294(MtxFx43 *m, MtxFx33 *n);              /* NNS_G3dGetCurrentMtx */

static inline void NNS_G3dGeMtxMode(u32 mode)
{
    func_01ff9f00(G3OP_MTX_MODE, (u32 *)&mode, 1);
}

static inline void NNS_G3dGeScale(fx32 x, fx32 y, fx32 z)
{
    VecFx32 vec;

    vec.x = x;
    vec.y = y;
    vec.z = z;
    func_01ff9f00(G3OP_MTX_SCALE, (u32 *)&vec, 3);
}

static inline void NNS_G3dGeTexCoord(fx32 s, fx32 t)
{
    u32 tmp;

    tmp = GX_PACK_TEXCOORD_PARAM(s, t);
    func_01ff9f00(G3OP_TEXCOORD, (u32 *)&tmp, 1);
}

static inline void NNS_G3dGeMultMtx44(const MtxFx44 *m)
{
    func_01ff9f00(G3OP_MTX_MULT_4x4, (u32 *)m, 16);
}

static inline void NNS_G3dGeMultMtx33(const MtxFx33 *m)
{
    func_01ff9f00(G3OP_MTX_MULT_3x3, (u32 *)m, 9);
}

static inline void *NNS_G3dGetResDataByIdx(const NNSG3dResDict *dict, u32 idx)
{
    NNSG3dResDictEntryHeader *hdr;

    if (dict != 0 && idx < dict->numEntry) {
        hdr = (NNSG3dResDictEntryHeader *)((u8 *)dict + dict->ofsEntry);
        return (void *)(&hdr->data[0] + hdr->sizeUnit * idx);
    } else {
        return 0;
    }
}

static inline NNSG3dResMatData *NNS_G3dGetMatDataByIdx(const NNSG3dResMat *mat, u32 idx)
{
    NNSG3dResDictMatData *data;

    if (mat) {
        data = (NNSG3dResDictMatData *)NNS_G3dGetResDataByIdx(&mat->dict, idx);
        if (data) {
            return (NNSG3dResMatData *)((u8 *)mat + data->offset);
        }
    }
    return 0;
}

void func_020280a4(NNSG3dRS *rs)
{
    if (!(rs->flag & NNS_G3D_RSFLAG_OPT_SKIP_SBCDRAW) && (rs->flag & NNS_G3D_RSFLAG_NODE_VISIBLE)) {
        if ((rs->pMatAnmResult->prmTexImage & REG_G3_TEXIMAGE_PARAM_TGEN_MASK) !=
            (GX_TEXGEN_NORMAL << REG_G3_TEXIMAGE_PARAM_TGEN_SHIFT)) {
            rs->pMatAnmResult->prmTexImage &= ~REG_G3_TEXIMAGE_PARAM_TGEN_MASK;
            rs->pMatAnmResult->prmTexImage |= GX_TEXGEN_NORMAL << REG_G3_TEXIMAGE_PARAM_TGEN_SHIFT;

            data_020427f4[3] = rs->pMatAnmResult->prmTexImage;
            func_01ff9f00(data_020427f4[2], data_02042800, 1);
        }

        NNS_G3dGeMtxMode(GX_MTXMODE_TEXTURE);

        {
            s32 width, height;

            width = (s32)rs->pMatAnmResult->origWidth;
            height = (s32)rs->pMatAnmResult->origHeight;

            NNS_G3dGeScale(width << (12 + 3), -height << (12 + 3), 0x1000 << 4);
            NNS_G3dGeTexCoord(width << (12 - 1), height << (12 - 1));
        }

        {
            u32 idxMat = *(rs->c + 1);
            const NNSG3dResMatData *mat = NNS_G3dGetMatDataByIdx(rs->pResMat, idxMat);

            if (mat->flag & NNS_G3D_MATFLAG_EFFECTMTX) {
                const MtxFx44 *effect_mtx;
                const u8 *p = (const u8 *)mat + sizeof(NNSG3dResMatData);

                if (!(mat->flag & NNS_G3D_MATFLAG_TEXMTX_SCALEONE)) {
                    p += sizeof(fx32) + sizeof(fx32);
                }
                if (!(mat->flag & NNS_G3D_MATFLAG_TEXMTX_ROTZERO)) {
                    p += sizeof(short) + sizeof(short);
                }
                if (!(mat->flag & NNS_G3D_MATFLAG_TEXMTX_TRANSZERO)) {
                    p += sizeof(fx32) + sizeof(fx32);
                }
                effect_mtx = (const MtxFx44 *)p;
                NNS_G3dGeMultMtx44(effect_mtx);
            }
        }

        {
            MtxFx33 n;

            NNS_G3dGeMtxMode(GX_MTXMODE_POSITION_VECTOR);
            func_02016294(0, &n);
            NNS_G3dGeMtxMode(GX_MTXMODE_TEXTURE);

            if (data_02047394.flag & NNS_G3D_GLB_FLAG_FLUSH_WVP) {
                NNS_G3dGeMultMtx33((const MtxFx33 *)&data_02047394.cameraMtx);
                NNS_G3dGeMultMtx33(&data_02047394.prmBaseRot);
                NNS_G3dGeMultMtx33(&n);
            } else if (data_02047394.flag & NNS_G3D_GLB_FLAG_FLUSH_VP) {
                NNS_G3dGeMultMtx33((const MtxFx33 *)&data_02047394.cameraMtx);
                NNS_G3dGeMultMtx33(&n);
            } else {
                NNS_G3dGeMultMtx33(&n);
            }
        }

        NNS_G3dGeMtxMode(GX_MTXMODE_POSITION_VECTOR);
    }
    rs->c += 3;
}
