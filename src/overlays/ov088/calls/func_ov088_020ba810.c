/* Constructor for the ov088 actor. Same routine as the panel-class constructor and
 * built on the same helpers, but with its own tuning: state 1 rather than 0x11, an
 * open limit of 0x1700, a TWO-WAY name choice on the config's alternateName field --
 * which the whole ov047 family leaves unused -- five bone lookups rather than four,
 * and an eight-entry handler table. */
typedef unsigned char u8;
typedef unsigned short u16;

struct PanelInitConfig {
    int objectType;
    int slotId;
    u8 bitIndex;
    u8 pad09[3];
    int enableLowFlag;
    int enableMidFlag;
    int enableHighFlag;
    int alternateName;
    int nameGroup;
};

struct Ov044OpenParams {
    int enabled;
    int limit;
    int scale;
    int unused0c;
    int unused10;
};

struct Ov044RigHeader {
    int pad0;
    int rig;
};

static inline int Ov044_GetBoneBase(char *object)
{
    int rig = ((struct Ov044RigHeader *)(
        *(int *)(object + 0x20) + 0x24))->rig;
    return rig != 0 ? rig + 0x40 : 0;
}

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void func_0202b850(int, u16, int, void *, int);
extern void func_0202b914(int, void *, int, int);
extern int func_0202bfcc(int);
extern void func_0202d968(void *, int);
extern int func_02016f10(void *, void *);
extern void func_ov022_0209f6e0(void *);

extern void func_ov088_020baad4(void);
extern void func_ov088_020babb0(void);
extern void func_ov088_020bacc8(void);
extern void func_ov088_020baa50(void);
extern void func_ov088_020baaac(void);
extern void func_ov088_020bacf8(void);
extern void func_ov088_020badd0(void);
extern void func_ov088_020bb6c0(void);

extern void *data_ov088_020bc360;
extern const char data_ov088_020bc29c[];
extern const char data_ov088_020bc2b0[];
extern int data_ov088_020bc230;
extern int data_ov088_020bc240;
extern int data_ov088_020bc210;
extern int data_ov088_020bc200;
extern int data_ov088_020bc220;

void func_ov088_020ba810(struct PanelInitConfig *config)
{
    struct Ov044OpenParams params;
    char *object = (char *)NNSi_FndGetCurrentRootHeap();
    int i;
    int bone;

    data_ov088_020bc360 = object;
    object[9] = (char)config->objectType;
    object[0x4bc] = (char)config->slotId;
    object[8] = config->bitIndex;
    *(int *)(object + 0xc) = 1;
    *(long long *)object = 0;

    params.enabled = 1;
    params.scale = 9 << 8;
    params.limit = 0x17 << 8;
    func_0202b850(*(signed char *)(object + 0x4bc),
                  (u16)(1 << *(u8 *)(object + 8)), 0, &params, 0);

    if (config->alternateName == 0) {
        func_0202b914(*(signed char *)(object + 0x4bc), (void *)data_ov088_020bc29c, 1,
                      config->objectType + 7);
    } else {
        func_0202b914(*(signed char *)(object + 0x4bc), (void *)data_ov088_020bc2b0, 1,
                      config->objectType + 7);
    }

    *(void **)(object + 0x664 + 0x00) = (void *)&func_ov088_020baad4;
    *(void **)(object + 0x664 + 0x04) = (void *)&func_ov088_020babb0;
    *(void **)(object + 0x664 + 0x08) = (void *)&func_ov088_020bacc8;
    *(void **)(object + 0x664 + 0x0c) = 0;
    *(void **)(object + 0x664 + 0x10) = 0;
    *(void **)(object + 0x664 + 0x14) = (void *)&func_ov088_020baa50;
    *(void **)(object + 0x664 + 0x18) = (void *)&func_ov088_020baaac;
    *(void **)(object + 0x664 + 0x20) = (void *)&func_ov088_020bacf8;
    *(void **)(object + 0x664 + 0x28) = 0;
    *(void **)(object + 0x664 + 0x28) = (void *)&func_ov088_020badd0;
    *(void **)(object + 0x664 + 0x24) = (void *)&func_ov088_020bb6c0;

    func_0202d968(object + 0x20,
                  func_0202bfcc(*(signed char *)(object + 0x4bc)));

    i = 0;
    goto test;
body:
    *(int *)(object + i * sizeof(int) + 0x514) = -1;
    i++;
test:
    if (i < 5) {
        goto body;
    }

    bone = Ov044_GetBoneBase(object);
    *(int *)(object + 0x520) = bone != 0
        ? func_02016f10((void *)bone, &data_ov088_020bc230) : -1;
    bone = Ov044_GetBoneBase(object);
    *(int *)(object + 0x518) = bone != 0
        ? func_02016f10((void *)bone, &data_ov088_020bc240) : -1;
    bone = Ov044_GetBoneBase(object);
    *(int *)(object + 0x514) = bone != 0
        ? func_02016f10((void *)bone, &data_ov088_020bc210) : -1;
    bone = Ov044_GetBoneBase(object);
    *(int *)(object + 0x51c) = bone != 0
        ? func_02016f10((void *)bone, &data_ov088_020bc200) : -1;
    bone = Ov044_GetBoneBase(object);
    *(int *)(object + 0x524) = bone != 0
        ? func_02016f10((void *)bone, &data_ov088_020bc220) : -1;

    if (config->enableLowFlag != 0) {
        *(long long *)object |= 0x20;
    }
    if (config->enableMidFlag != 0) {
        *(long long *)object |= 0x10000;
    }
    if (config->enableHighFlag != 0) {
        *(long long *)object |= 0x1000000000LL;
    }
    func_ov022_0209f6e0(object);
}
