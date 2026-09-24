/* Loads a model file (heap 0xf) into data_0204c20c[1], sets its textures up with the loader's
 * texture flag off (func_02025138), takes model 0 of its model set (NNS_G3dGetMdlSet /
 * NNS_G3dGetMdlByIdx, inlined) into data_0204c20c[0] and binds it (func_020169f8). Returns 1. */
#pragma thumb on
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

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

extern void *func_0201ef9c(const char *path, int heap);
extern void func_0201f390(int flag);
extern void func_02025138(void *file);
extern NNSG3dResMdlSet *func_02017078(void *file);   /* NNS_G3dGetMdlSet */
extern void func_020169f8(void *mdl, int a, int b);
extern void *data_0204c20c[];

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

int func_0202de74(const char *path)
{
    NNSG3dResMdlSet *mdlSet;

    data_0204c20c[1] = func_0201ef9c(path, 0xf);
    func_0201f390(0);
    func_02025138(data_0204c20c[1]);
    func_0201f390(1);
    mdlSet = func_02017078(data_0204c20c[1]);
    data_0204c20c[0] = GetMdlByIdx(mdlSet, 0);
    func_020169f8(data_0204c20c[0], 0, 0);
    return 1;
}
