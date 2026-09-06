typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

typedef struct VecFx32 {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct MtxFx33 {
    int value[9];
} MtxFx33;

typedef struct Ov022AnimationSlot {
    s8 active00;
    u8 padding001[3];
    u16 resource04;
    u8 padding006[0x76];
    void *config7c;
    u16 angle80;
    u8 padding082[0x26];
    VecFx32 translationA8;
    VecFx32 scaleB4;
    u8 padding0c0[0x4c];
    void *commandBlock10c;
    s8 kind110;
    s8 subkind111;
    u8 padding112[2];
} Ov022AnimationSlot;

typedef struct NNSG3dGlobalState {
    u8 padding000[0xd4];
    u32 flagsD4;
} NNSG3dGlobalState;

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void func_02016b60(void *object, unsigned int index,
                          unsigned int value, int slot);
extern void func_0202aa9c(void *renderNode);
extern void MTX_RotY33_(MtxFx33 *matrix, int sine, int cosine);
extern void func_0201571c(void);
extern void func_01ff9f00(unsigned int command, const void *source,
                          unsigned int wordCount);
extern void func_020279e0(void *object);

extern VecFx32 data_02047458;
extern s16 data_0203d210[];
extern MtxFx33 data_02047428;
extern VecFx32 data_0204744c;
extern NNSG3dGlobalState data_02047394;

void func_ov022_02089078(Ov022AnimationSlot *entry,
                          Ov022AnimationSlot *base)
{
    int angle;

    NNSi_FndGetCurrentRootHeap();
    if (entry->kind110 != -1 && entry->subkind111 != -1) {
        func_02016b60(entry->config7c, entry->kind110,
                      entry->subkind111, -1);
    }

    if (entry->commandBlock10c == 0) {
        func_0202aa9c((char *)entry + 4);
        return;
    }

    data_02047458 = entry->scaleB4;
    angle = entry->angle80 >> 4;
    MTX_RotY33_(&data_02047428, data_0203d210[angle * 2],
                data_0203d210[angle * 2 + 1]);
    data_0204744c = entry->translationA8;
    data_02047394.flagsD4 &= ~0xa4;
    func_0201571c();
    func_01ff9f00(0x17, entry->commandBlock10c, 0xc);
    func_020279e0((char *)entry + 0x24);
}
