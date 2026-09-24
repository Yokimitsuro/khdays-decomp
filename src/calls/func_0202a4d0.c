/* func_0202a4d0 -- set up a model instance, MAIN. Resolves the model file `fileId` through the
 * instance's resource list (+0x74, func_0201f634; with both a texture source and a file the
 * loader's texture flag is lowered around the lookup), sets the textures up from `texSrc` when
 * given (func_020255f0), takes model 0 of the file's model set as the resource model (+0x78) and
 * initialises the render object (+0x20) with it, binds the animation block (+0xe0, func_0202a208),
 * clears the five animation slots (ids +0x2 / +0xca, handles +0xc), and resets the transform:
 * identity rotation (+0x80), zero translation (+0xa4), unit scale (+0xb0), zero offset (+0xbc).
 * Returns TRUE. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int fx32;
typedef int BOOL;

typedef struct {
    u8 revision;
    u8 numEntry;
    u16 sizeDictBlk;
    u16 dummy_;
    u16 ofsEntry;
} NNSG3dResDict;

typedef struct {
    u16 sizeUnit;
    u16 sizeName;
    u8 data[4];
} NNSG3dResDictEntryHeader;

typedef struct {
    u32 header[2];
    NNSG3dResDict dict;
} NNSG3dResMdlSet;

typedef struct { fx32 m[9]; } MtxFx33;
typedef struct { fx32 x, y, z; } VecFx32;

typedef struct ModelResList {
    char pad00[8];
    void *texSet;                       /* +0x08 */
} ModelResList;

typedef struct ModelInst {
    u16 flags;                          /* +0x00 */
    s16 animId[5];                      /* +0x02 */
    void *anim[5];                      /* +0x0c */
    char renderObj[0x54];               /* +0x20: NNSG3dRenderObj */
    ModelResList *resList;              /* +0x74 */
    void *resMdl;                       /* +0x78 */
    u16 frame;                          /* +0x7c */
    u16 frameSpeed;                     /* +0x7e */
    MtxFx33 rot;                        /* +0x80 */
    VecFx32 trans;                      /* +0xa4 */
    VecFx32 scale;                      /* +0xb0 */
    VecFx32 offset;                     /* +0xbc */
    s16 jointId;                        /* +0xc8 */
    s16 animSlot[5];                    /* +0xca */
    int pad0d4;
    int userA;                          /* +0xd8 */
    int userB;                          /* +0xdc */
    char animBlock[0xc];                /* +0xe0 */
    int animCount;                      /* +0xec */
} ModelInst;

extern void func_0201f390(int flag);
extern void *func_0201f634(ModelResList *list, int fileId);
extern void func_020255f0(void *file, void *texSet, int texSrc);
extern void *func_020255d4(void *file, int nMember, int nSub);
extern NNSG3dResMdlSet *func_02017078(void *file);   /* NNS_G3dGetMdlSet */
extern void func_02014b5c(void *renderObj, void *resMdl);   /* NNS_G3dRenderObjInit */
extern void func_0202a208(void *animBlock, ModelInst *inst, void *file, int texSrc);
extern void MTX_Identity33_(MtxFx33 *m);

static inline void *GetResDataByIdx(const NNSG3dResDict *dict, u32 idx)
{
    if (dict != 0 && idx < dict->numEntry) {
        const NNSG3dResDictEntryHeader *hdr = (const NNSG3dResDictEntryHeader *)((u8 *)dict + dict->ofsEntry);

        return (void *)&hdr->data[idx * hdr->sizeUnit];
    }
    return 0;
}

static inline void *GetMdlByIdx(const NNSG3dResMdlSet *mdlSet, u32 idx)
{
    if (mdlSet) {
        const u32 *data = GetResDataByIdx(&mdlSet->dict, idx);

        if (data) {
            return (u8 *)mdlSet + *data;
        }
    }
    return 0;
}

BOOL func_0202a4d0(ModelInst *inst, int texSrcFlag, int fileId, int texSrc)
{
    void *file;
    int i;

    if (texSrcFlag != 0 && fileId != 0) {
        func_0201f390(0);
    }
    file = func_0201f634(inst->resList, fileId);
    if (texSrcFlag != 0) {
        if (fileId != 0) {
            func_0201f390(1);
        }
        func_020255f0(file, inst->resList->texSet, texSrc);
    }
    inst->resMdl = GetMdlByIdx(func_02017078(func_020255d4(file, 7, 0)), 0);
    func_02014b5c(inst->renderObj, inst->resMdl);
    inst->animCount = 0;
    func_0202a208(inst->animBlock, inst, file, texSrc);
    for (i = 0; i < 5; i++) {
        inst->animId[i] = -1;
        inst->animSlot[i] = -1;
        inst->anim[i] = 0;
    }
    inst->frame = 0;
    inst->frameSpeed = 0;
    MTX_Identity33_(&inst->rot);
    inst->trans.x = inst->trans.y = inst->trans.z = 0;
    inst->scale.x = inst->scale.y = inst->scale.z = 0x1000;
    inst->flags = 0;
    inst->offset.x = inst->offset.y = inst->offset.z = 0;
    inst->jointId = -1;
    inst->userA = 0;
    inst->userB = 0;
    return 1;
}
