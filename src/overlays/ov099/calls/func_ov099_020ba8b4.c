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
extern int OS_SPrintf(char *, const char *, const char *);
extern void func_0202b914(int, void *, int, int);
extern int func_0202bfcc(int);
extern void func_0202d968(void *, int);
extern int func_02016f10(void *, void *);
extern void func_ov022_0209f6e0(void *);

extern void func_ov099_020babd4(void);
extern void func_ov099_020baeec(void);
extern void func_ov099_020baf30(void);
extern void func_ov099_020baafc(void);
extern void func_ov099_020bab9c(void);
extern void func_ov099_020bafcc(void);
extern void func_ov099_020baf4c(void);
extern void func_ov099_020bb01c(void);

extern void *data_ov099_020bcbc0;
extern const char data_ov099_020bcac8[];
extern const char data_ov099_020bcacc[];
extern const char data_ov099_020bcae0[];
extern const char data_ov099_020bcaf4[];
extern const char data_ov099_020bcb08[];
extern int data_ov099_020bca44;
extern int data_ov099_020bca64;
extern int data_ov099_020bca54;
extern int data_ov099_020bca34;

void func_ov099_020ba8b4(struct PanelInitConfig *config)
{
    char name[128];
    struct Ov044OpenParams params;
    char *object = (char *)NNSi_FndGetCurrentRootHeap();
    int i;
    int bone;
    int nameGroup;
    int alternateName;

    data_ov099_020bcbc0 = object;
    object[9] = (char)config->objectType;
    object[0x4bc] = (char)config->slotId;
    object[8] = config->bitIndex;
    *(int *)(object + 0xc) = 0xe;
    *(long long *)object = 0;

    params.enabled = 1;
    params.scale = 9 << 8;
    params.limit = 0xf << 8;
    func_0202b850(*(signed char *)(object + 0x4bc),
                  (u16)(1 << *(u8 *)(object + 8)), 0, &params, 0);

    nameGroup = config->nameGroup;
    alternateName = config->alternateName;
    switch (nameGroup) {
    case 0:
        if (alternateName != 0) {
            OS_SPrintf(name, data_ov099_020bcac8, data_ov099_020bcacc);
        } else {
            OS_SPrintf(name, data_ov099_020bcac8, data_ov099_020bcae0);
        }
        break;
    case 1:
        if (alternateName != 0) {
            OS_SPrintf(name, data_ov099_020bcac8, data_ov099_020bcaf4);
        } else {
            OS_SPrintf(name, data_ov099_020bcac8, data_ov099_020bcb08);
        }
        break;
    }

    func_0202b914(*(signed char *)(object + 0x4bc), name, 1,
                  config->objectType + 7);

    *(void **)(object + 0x664 + 0x00) = (void *)&func_ov099_020babd4;
    *(void **)(object + 0x664 + 0x04) = (void *)&func_ov099_020baeec;
    *(void **)(object + 0x664 + 0x08) = (void *)&func_ov099_020baf30;
    *(void **)(object + 0x664 + 0x0c) = 0;
    *(void **)(object + 0x664 + 0x10) = 0;
    *(void **)(object + 0x664 + 0x14) = (void *)&func_ov099_020baafc;
    *(void **)(object + 0x664 + 0x18) = (void *)&func_ov099_020bab9c;
    *(void **)(object + 0x664 + 0x20) = (void *)&func_ov099_020bafcc;
    *(void **)(object + 0x664 + 0x28) = (void *)&func_ov099_020baf4c;
    *(void **)(object + 0x664 + 0x24) = (void *)&func_ov099_020bb01c;

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
        ? func_02016f10((void *)bone, &data_ov099_020bca44) : -1;
    bone = Ov044_GetBoneBase(object);
    *(int *)(object + 0x518) = bone != 0
        ? func_02016f10((void *)bone, &data_ov099_020bca64) : -1;
    bone = Ov044_GetBoneBase(object);
    *(int *)(object + 0x51c) = bone != 0
        ? func_02016f10((void *)bone, &data_ov099_020bca54) : -1;
    bone = Ov044_GetBoneBase(object);
    *(int *)(object + 0x524) = bone != 0
        ? func_02016f10((void *)bone, &data_ov099_020bca34) : -1;

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
