/* NitroSystem immediate draw of one material and one shape. */
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


typedef struct NNSG3dResMdl {
    u32 size, ofsSbc, ofsMat, ofsShp, ofsEvpMtx;
    u8 pad14[2];
    u8 texMtxMode;
    u8 pad17;
    u8 numMat, numShp;
    u8 pad1a[2];
    fx32 posScale, invPosScale;
} NNSG3dResMdl;
typedef struct NNSG3dResShp { NNSG3dResDict dict; } NNSG3dResShp;
typedef struct NNSG3dResDictShpData { u32 offset; } NNSG3dResDictShpData;
typedef struct NNSG3dResShpData {
    u16 itemTag, size;
    u8 pad04[4];
    u32 ofsDL, sizeDL;
} NNSG3dResShpData;
typedef struct VecFx32 { fx32 x, y, z; } VecFx32;
typedef void (*NNSG3dFuncMatSend)(NNSG3dMatAnmResult *result);
extern NNSG3dFuncMatSend data_0204251c[];
extern void func_01ff9f00(u32 command, const void *words, u32 count);
extern void func_01ff9d90(const void *displayList, u32 byteSize);

#pragma inline_max_size(1300)
static inline void *GetEntry(const NNSG3dResDict *dict, u32 index)
{
    NNSG3dResDictEntryHeader *header;
    if (dict && index < dict->numEntry) {
        header = (NNSG3dResDictEntryHeader *)((u8 *)dict + dict->ofsEntry);
        return header->data + header->sizeUnit * index;
    }
    return 0;
}
static inline NNSG3dResMat *GetMaterials(const NNSG3dResMdl *model)
{
    return model && model->ofsMat ? (NNSG3dResMat *)((u8 *)model + model->ofsMat) : 0;
}
static inline NNSG3dResShp *GetShapes(const NNSG3dResMdl *model)
{
    return model && model->ofsShp ? (NNSG3dResShp *)((u8 *)model + model->ofsShp) : 0;
}
static inline NNSG3dResMatData *GetMaterial(const NNSG3dResMat *materials, u32 index)
{
    NNSG3dResDictMatData *entry;
    if (materials) {
        entry = (NNSG3dResDictMatData *)GetEntry(&materials->dict, index);
        if (entry) return (NNSG3dResMatData *)((u8 *)materials + entry->offset);
    }
    return 0;
}
static inline NNSG3dResShpData *GetShape(const NNSG3dResShp *shapes, u32 index)
{
    NNSG3dResDictShpData *entry;
    if (shapes) {
        entry = (NNSG3dResDictShpData *)GetEntry(&shapes->dict, index);
        if (entry) return (NNSG3dResShpData *)((u8 *)shapes + entry->offset);
    }
    return 0;
}
static inline void SendScale(fx32 value)
{
    VecFx32 scale;
    scale.x = value; scale.y = value; scale.z = value;
    func_01ff9f00(0x1b, &scale, 3);
}
static inline void SendPacket(const u32 *packet, u32 count)
{
    func_01ff9f00(packet[0], packet + 1, count - 1);
}

void func_01ffcc1c(const NNSG3dResMdl *model, u32 materialId, u32 shapeId, s32 sendMaterial)
{
    if (model->posScale != 0x1000) SendScale(model->posScale);
    if (sendMaterial && materialId < model->numMat) {
        const NNSG3dResMatData *material = GetMaterial(GetMaterials(model), materialId);
        u32 packet[7];
        NNSG3dMatAnmResult result;
        const u8 *payload;
        NNSG3dFuncMatSend callback;
        if (!(material->polyAttr & 0x1f0000)) return;
        packet[0] = 0x293130;
        packet[1] = material->diffAmb;
        packet[2] = material->specEmi;
        packet[3] = material->polyAttr;
        if (material->flag & 0x20) packet[3] &= ~0x1f0000;
        packet[4] = 0x2b2a;
        packet[5] = material->texImageParam;
        packet[6] = material->texPlttBase;
        SendPacket(packet, 7);
        if (material->flag & 1) {
            result.flag = 8;
            result.origWidth = material->origWidth;
            result.origHeight = material->origHeight;
            result.magW = material->magW;
            result.magH = material->magH;
            payload = (const u8 *)(material + 1);
            if (material->flag & 2) {
                result.flag |= 1;
            } else {
                result.scaleS = ((const fx32 *)payload)[0];
                result.scaleT = ((const fx32 *)payload)[1];
                payload += 8;
            }
            if (!(material->flag & 4)) {
                result.sinR = ((const s16 *)payload)[0];
                result.cosR = ((const s16 *)payload)[1];
                payload += 4;
            } else {
                result.flag |= 2;
            }
            if (!(material->flag & 8)) {
                result.transS = ((const fx32 *)payload)[0];
                result.transT = ((const fx32 *)payload)[1];
            } else {
                result.flag |= 4;
            }
            callback = data_0204251c[model->texMtxMode];
            if (callback) callback(&result);
        }
    }
    if (shapeId < model->numShp) {
        const NNSG3dResShpData *shape = GetShape(GetShapes(model), shapeId);
        func_01ff9d90((const u8 *)shape + shape->ofsDL, shape->sizeDL);
    }
    if (model->invPosScale != 0x1000) SendScale(model->invPosScale);
}
