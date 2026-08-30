/* NitroSystem G3D material SBC handler, including the game RGB scale extension. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef signed short s16;
typedef signed long s32;
typedef signed long fx32;

typedef struct NNSG3dResDictTreeNode {
    u8 refBit;
    u8 idxLeft;
    u8 idxRight;
    u8 idxEntry;
} NNSG3dResDictTreeNode;

typedef struct NNSG3dResDict {
    u8 revision;
    u8 numEntry;
    u16 sizeDictBlk;
    u16 dummy;
    u16 ofsEntry;
    NNSG3dResDictTreeNode node[1];
} NNSG3dResDict;

typedef struct NNSG3dResDictEntryHeader {
    u16 sizeUnit;
    u16 ofsName;
    u8 data[4];
} NNSG3dResDictEntryHeader;

typedef struct NNSG3dResDictMatData {
    u32 offset;
} NNSG3dResDictMatData;

typedef struct NNSG3dResMatData {
    u16 itemTag;
    u16 size;
    u32 diffAmb;
    u32 specEmi;
    u32 polyAttr;
    u32 polyAttrMask;
    u32 texImageParam;
    u32 texImageParamMask;
    u16 texPlttBase;
    u16 flag;
    u16 origWidth;
    u16 origHeight;
    fx32 magW;
    fx32 magH;
} NNSG3dResMatData;

typedef struct NNSG3dResMat {
    u16 ofsDictTexToMatList;
    u16 ofsDictPlttToMatList;
    NNSG3dResDict dict;
} NNSG3dResMat;

typedef struct NNSG3dMatAnmResult {
    u32 flag;
    u32 prmMatColor0;
    u32 prmMatColor1;
    u32 prmPolygonAttr;
    u32 prmTexImage;
    u32 prmTexPltt;
    fx32 scaleS;
    fx32 scaleT;
    s16 sinR;
    s16 cosR;
    fx32 transS;
    fx32 transT;
    u16 origWidth;
    u16 origHeight;
    fx32 magW;
    fx32 magH;
} NNSG3dMatAnmResult;

struct NNSG3dAnmObj;
typedef void (*NNSG3dFuncAnmMat)(NNSG3dMatAnmResult *,
                                  const struct NNSG3dAnmObj *, u32);

typedef struct NNSG3dAnmObj {
    fx32 frame;
    fx32 ratio;
    void *resAnm;
    NNSG3dFuncAnmMat funcAnm;
    struct NNSG3dAnmObj *next;
    const void *resTex;
    u8 priority;
    u8 numMapData;
    u16 mapData[1];
} NNSG3dAnmObj;

typedef struct NNSG3dRenderObj {
    u32 flags;
    void *pResMdl;
    NNSG3dAnmObj *anmMat;
    u8 pad0c_38[0x2c];
    NNSG3dMatAnmResult *matResults;
    u32 matEnabled[4];
} NNSG3dRenderObj;

typedef void (*NNSG3dFuncMatSend)(NNSG3dMatAnmResult *);

typedef struct NNSG3dRenderState {
    u8 *pSbc;
    NNSG3dRenderObj *pRenderObj;
    u32 flags;
    u8 pad00c_0ac[0xa0];
    u8 commandAc;
    u8 materialAd;
    u8 pad0ae_0b0[2];
    NNSG3dMatAnmResult *currentMat;
    u8 pad0b4_0bc[8];
    u32 matDone[4];
    u8 pad0cc_0d8[0x0c];
    NNSG3dResMat *pResMat;
    u8 pad0dc_0f0[0x14];
    NNSG3dFuncMatSend sendMat;
    NNSG3dMatAnmResult matBuffer;
} NNSG3dRenderState;

typedef struct NNSG3dGlbMaterial {
    u8 pad00_80[0x80];
    u32 prmMatColor0;
    u32 prmMatColor1;
    u32 prmPolygonAttr;
} NNSG3dGlbMaterial;

typedef struct MaterialColorScale {
    u16 red;
    u16 green;
    u16 blue;
} MaterialColorScale;

typedef struct NNSG3dRSOnGlobal {
    NNSG3dMatAnmResult matCache[1];
} NNSG3dRSOnGlobal;

#define GX_COLOR_R(rgb) ((rgb) & 0x1f)
#define GX_COLOR_G(rgb) (((rgb) >> 5) & 0x1f)
#define GX_COLOR_B(rgb) (((rgb) >> 10) & 0x1f)
#define GX_RGB(r, g, b) \
    (((r) & 0x1f) | (((g) & 0x1f) << 5) | (((b) & 0x1f) << 10))

static inline void *NNS_G3dGetResDataByIdx(const NNSG3dResDict *dict,
                                            u32 idx)
{
    NNSG3dResDictEntryHeader *hdr;

    if (dict != 0 && idx < dict->numEntry) {
        hdr = (NNSG3dResDictEntryHeader *)((u8 *)dict + dict->ofsEntry);
        return (void *)(&hdr->data[0] + hdr->sizeUnit * idx);
    } else {
        return 0;
    }
}

static inline NNSG3dResMatData *NNS_G3dGetMatDataByIdx(
    const NNSG3dResMat *mat, u32 idx)
{
    NNSG3dResDictMatData *data;

    if (mat) {
        data = (NNSG3dResDictMatData *)NNS_G3dGetResDataByIdx(&mat->dict,
                                                               idx);
        if (data) {
            return (NNSG3dResMatData *)((u8 *)mat + data->offset);
        }
    }
    return 0;
}

static inline NNSG3dResMatData *NNS_G3dGetWireMatDataByIdx(
    const NNSG3dResMat *mat, u32 idx)
{
    NNSG3dResDictMatData *data;

    if (mat) {
        data = (NNSG3dResDictMatData *)NNS_G3dGetResDataByIdx(&mat->dict,
                                                               idx);
        if (data) {
            return (NNSG3dResMatData *)((u8 *)mat + data->offset);
        }
    }
    return 0;
}

extern NNSG3dRSOnGlobal data_020475d4;
extern NNSG3dGlbMaterial data_02047394;
extern const u32 data_0204208c[];
extern u16 data_027e0654;
extern MaterialColorScale data_027e0658;
extern void func_01ff9f00(u32 command, const void *words, u32 count);

#pragma inline_max_size(1300)
#pragma opt_propagation off

static inline void NNS_G3dGeBufferData_N(const u32 *args, u32 num)
{
    func_01ff9f00(*args, args + 1, num - 1);
}

static inline void BitVecSet(u32 *vec, u32 idx)
{
    vec[idx >> 5] |= 1 << (idx & 0x1f);
}

static inline s32 BitVecCheck(const u32 *vec, u32 idx)
{
    return (s32)(vec[idx >> 5] & (1 << (idx & 0x1f)));
}

static inline NNSG3dMatAnmResult *GetMatCache(u32 idx)
{
    return &data_020475d4.matCache[idx];
}

static inline NNSG3dMatAnmResult *GetNewMatCache(u32 idx)
{
    return &data_020475d4.matCache[idx];
}

static inline NNSG3dMatAnmResult *GetRecordedMat(
    NNSG3dRenderObj *renderObj, u32 idx)
{
    return &renderObj->matResults[idx];
}

static inline u32 GetMatColor0(const NNSG3dMatAnmResult *result)
{
    return result->prmMatColor0;
}

static inline NNSG3dMatAnmResult *SetAndGetMatCache(
    NNSG3dRenderState *state, u32 idx)
{
    BitVecSet(state->matDone, idx);
    return &data_020475d4.matCache[idx];
}

static inline void BlendMat(NNSG3dMatAnmResult *result,
                            NNSG3dRenderObj *renderObj,
                            u32 materialID)
{
    NNSG3dAnmObj *obj = renderObj->anmMat;

    if (obj != 0 &&
        (renderObj->matEnabled[materialID >> 5] &
         (1 << (materialID & 0x1f)))) {
        do {
            if (materialID < obj->numMapData) {
                u32 dataIdx = obj->mapData[materialID];

                if ((dataIdx & 0x300) == 0x100 && obj->funcAnm != 0) {
                    obj->funcAnm(result, obj, dataIdx & 0xff);
                }
            }
            obj = obj->next;
        } while (obj != 0);
    }
}

static inline u32 ScaleMaterialColor(u32 color, const MaterialColorScale *scale)
{
    /* These temporaries scalarize and do not describe a resource layout. */
    struct {
        s32 factor;
        u16 input;
        s32 product;
        u16 normalized;
    } channels[3];
    u32 output;
    channels[0].input = (color >> 0) & 31;
    channels[1].input = (color >> 5) & 31;
    channels[2].input = (color >> 10) & 31;
    channels[0].factor = scale->red;
    channels[0].product = channels[0].input * channels[0].factor;
    channels[1].factor = scale->green;
    channels[1].product = channels[1].input * channels[1].factor;
    channels[2].factor = scale->blue;
    channels[2].product = channels[2].input * channels[2].factor;

    channels[0].normalized = (channels[0].product >> 5);
    channels[1].normalized = (channels[1].product >> 5);
    channels[2].normalized = (channels[2].product >> 5);
    output = color & 0xffff8000U;
    return output | (u32)channels[0].normalized |
           ((u32)channels[1].normalized << 5) |
           ((u32)channels[2].normalized << 10);
}

static inline void MatBody(NNSG3dRenderState *state, u32 option,
                           u32 materialID,
                           const NNSG3dResMatData *matSeed)
{
    NNSG3dRenderObj *renderObj;
    const NNSG3dResMatData *matData;
    NNSG3dMatAnmResult *result;

    matData = matSeed;

    state->materialAd = (u8)materialID;
    state->flags |= 8;
    renderObj = state->pRenderObj;

    {
    if (renderObj->matResults != 0 && !(state->flags & 0x80)) {
        result = GetRecordedMat(renderObj, materialID);
    } else if ((option == 0x20 || option == 0x40) &&
               BitVecCheck(state->matDone, materialID)) {
        if (renderObj->matResults != 0) {
            result = GetRecordedMat(renderObj, materialID);
        } else {
            result = GetMatCache(materialID);
        }
    } else {
        if (renderObj->matResults != 0) {
            BitVecSet(state->matDone, materialID);
            result = GetRecordedMat(renderObj, materialID);
        } else if (option == 0x40) {
            BitVecSet(state->matDone, materialID);
            result = GetNewMatCache(materialID);
        } else {
            result = &state->matBuffer;
        }

        result->flag = 0;
        if (NNS_G3dGetWireMatDataByIdx(state->pResMat, materialID)->flag &
            0x20) {
            result->flag |= 0x20;
        }
        {
            u32 mask = data_0204208c[(matData->flag >> 6) & 7];
            result->prmMatColor0 =
                (data_02047394.prmMatColor0 & ~mask) |
                (matData->diffAmb & mask);
        }
        {
            u32 mask = data_0204208c[(matData->flag >> 9) & 7];
            result->prmMatColor1 =
                (data_02047394.prmMatColor1 & ~mask) |
                (matData->specEmi & mask);
        }
        result->prmPolygonAttr =
            (data_02047394.prmPolygonAttr & ~matData->polyAttrMask) |
            (matData->polyAttr & matData->polyAttrMask);
        result->prmTexImage = matData->texImageParam;
        result->prmTexPltt = matData->texPlttBase;

        if (matData->flag & 1) {
            const u8 *p = (const u8 *)matData + sizeof(NNSG3dResMatData);

            if (!(matData->flag & 2)) {
                const fx32 *pFx32 = (const fx32 *)p;

                result->scaleS = pFx32[0];
                result->scaleT = pFx32[1];
                p += 2 * sizeof(fx32);
            } else {
                result->flag |= 1;
            }
            if (!(matData->flag & 4)) {
                const s16 *pFx16 = (const s16 *)p;

                result->sinR = pFx16[0];
                result->cosR = pFx16[1];
                p += 2 * sizeof(s16);
            } else {
                result->flag |= 2;
            }
            if (!(matData->flag & 8)) {
                const fx32 *pFx32 = (const fx32 *)p;

                result->transS = pFx32[0];
                result->transT = pFx32[1];
            } else {
                result->flag |= 4;
            }
            result->flag |= 8;
        }

        BlendMat(result, renderObj, materialID);

        if (result->flag & 0x18) {
            result->origWidth = matData->origWidth;
            result->origHeight = matData->origHeight;
            result->magW = matData->magW;
            result->magH = matData->magH;
        }
    }

    state->currentMat = result;
    if (result->prmPolygonAttr & 0x1f0000) {
        u32 packet[7];

        if (result->flag & 0x20) {
            result->prmPolygonAttr &= ~0x1f0000;
        }
        state->flags &= ~2U;
        if (!(state->flags & 0x100)) {
            u32 color;
            s32 enabled;
            enabled = data_027e0654;
            packet[0] = 0x00293130;
            if (enabled != 0) {
                color = ScaleMaterialColor(GetMatColor0(result),
                                           &data_027e0658);
            } else {
                color = GetMatColor0(result);
            }
            packet[1] = color;
            packet[2] = result->prmMatColor1;
            packet[3] = result->prmPolygonAttr;
            packet[4] = 0x00002b2a;
            packet[5] = result->prmTexImage;
            packet[6] = result->prmTexPltt;
            NNS_G3dGeBufferData_N(packet, 7);
            if (result->flag & 0x18) {
                state->sendMat(result);
            }
        }
    } else {
        state->flags |= 2;
    }
    }
}

static inline void MatInternalDefault(NNSG3dRenderState *state, u32 option,
                                      const NNSG3dResMatData *matSeed,
                                      u32 materialID)
{
    MatBody(state, option, materialID, matSeed);
}

void func_01ffbbf0(NNSG3dRenderState *state, u32 option)
{
    if (!(state->flags & 0x200)) {
        u32 materialID = state->pSbc[1];

        if ((state->flags & 1) ||
            !((state->flags & 8) && materialID == state->materialAd)) {
            const NNSG3dResMatData *matSeed;

            matSeed = NNS_G3dGetMatDataByIdx(
                state->pResMat, materialID);

            MatInternalDefault(state, option, matSeed, materialID);
        }
    }
    state->pSbc += 2;
}
