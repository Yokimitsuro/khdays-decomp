/* Constructor for the ov030 actor. Same routine as the ov031 panel-class
 * constructor and built on the same helpers, but with its own tuning: an open
 * limit of 0xf00, a THREE-WAY name choice -- the config's nameGroup picks the
 * family and, inside group 0, alternateName picks between two members -- a
 * ten-entry handler table, and a fourth flag raised when story flag 0x208a is
 * set. The five bone lookups are the family's usual inline: a rig of zero
 * yields -1 rather than being passed on.
 */
typedef unsigned char u8;
typedef unsigned short u16;

struct PanelInitConfig {
    int objectType;                         /* 0x00 */
    int slotId;                             /* 0x04 */
    u8 bitIndex;                            /* 0x08 */
    u8 pad09[3];
    int enableLowFlag;                      /* 0x0c */
    int enableMidFlag;                      /* 0x10 */
    int enableHighFlag;                     /* 0x14 */
    int alternateName;                      /* 0x18 */
    int nameGroup;                          /* 0x1c */
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
extern void OS_SPrintf(void *, const char *, const char *);
extern void func_0202b914(int, void *, int, int);
extern int func_0202bfcc(int);
extern void func_0202d968(void *, int);
extern int func_02016f10(void *, void *);
extern int func_02023588(int);
extern void func_ov022_0209f6e0(void *);

extern void func_ov030_020b3990(void);
extern void func_ov030_020b3cd4(void);
extern void func_ov030_020b3d18(void);
extern void func_ov030_020b35dc(void);
extern void func_ov030_020b3694(void);
extern void func_ov030_020b375c(void);
extern void func_ov030_020b36cc(void);
extern void func_ov030_020b3e24(void);

extern void *data_ov030_020b5a00;
extern const char data_ov030_020b591c[];
extern const char data_ov030_020b5920[];
extern const char data_ov030_020b5934[];
extern const char data_ov030_020b5948[];
extern int data_ov030_020b5880;
extern int data_ov030_020b58a0;
extern int data_ov030_020b5860;
extern int data_ov030_020b5870;
extern int data_ov030_020b5890;

void func_ov030_020b3374(struct PanelInitConfig *config)
{
    struct Ov044OpenParams params;
    char name[0x80];
    char *object = (char *)NNSi_FndGetCurrentRootHeap();
    int bone;

    data_ov030_020b5a00 = object;
    object[9] = (char)config->objectType;
    object[0x4bc] = (char)config->slotId;
    object[8] = config->bitIndex;
    *(int *)(object + 0xc) = 0;
    *(long long *)object = 0;

    params.enabled = 1;
    params.scale = 9 << 8;
    params.limit = 0xf << 8;
    func_0202b850(*(signed char *)(object + 0x4bc),
                  (u16)(1 << *(u8 *)(object + 8)), 0, &params, 0);

    switch (config->nameGroup) {
    case 0:
        if (config->alternateName == 0) {
            OS_SPrintf(name, data_ov030_020b591c, data_ov030_020b5920);
        } else {
            OS_SPrintf(name, data_ov030_020b591c, data_ov030_020b5934);
        }
        break;
    case 1:
        OS_SPrintf(name, data_ov030_020b591c, data_ov030_020b5948);
        break;
    }

    func_0202b914(*(signed char *)(object + 0x4bc), name, 1,
                  config->objectType + 7);

    *(void **)(object + 0x664 + 0x00) = (void *)&func_ov030_020b3990;
    *(void **)(object + 0x664 + 0x04) = (void *)&func_ov030_020b3cd4;
    *(void **)(object + 0x664 + 0x08) = (void *)&func_ov030_020b3d18;
    *(void **)(object + 0x664 + 0x0c) = 0;
    *(void **)(object + 0x664 + 0x10) = 0;
    *(void **)(object + 0x664 + 0x14) = (void *)&func_ov030_020b35dc;
    *(void **)(object + 0x664 + 0x18) = (void *)&func_ov030_020b3694;
    *(void **)(object + 0x664 + 0x20) = (void *)&func_ov030_020b375c;
    *(void **)(object + 0x664 + 0x28) = (void *)&func_ov030_020b36cc;
    *(void **)(object + 0x664 + 0x24) = (void *)&func_ov030_020b3e24;

    func_0202d968(object + 0x20,
                  func_0202bfcc(*(signed char *)(object + 0x4bc)));

    bone = Ov044_GetBoneBase(object);
    *(int *)(object + 0x520) = bone != 0
        ? func_02016f10((void *)bone, &data_ov030_020b5880) : -1;
    bone = Ov044_GetBoneBase(object);
    *(int *)(object + 0x518) = bone != 0
        ? func_02016f10((void *)bone, &data_ov030_020b58a0) : -1;
    bone = Ov044_GetBoneBase(object);
    *(int *)(object + 0x514) = bone != 0
        ? func_02016f10((void *)bone, &data_ov030_020b5860) : -1;
    bone = Ov044_GetBoneBase(object);
    *(int *)(object + 0x51c) = bone != 0
        ? func_02016f10((void *)bone, &data_ov030_020b5870) : -1;
    bone = Ov044_GetBoneBase(object);
    *(int *)(object + 0x524) = bone != 0
        ? func_02016f10((void *)bone, &data_ov030_020b5890) : -1;

    if (config->enableLowFlag != 0) {
        *(long long *)object |= 0x20;
    }
    if (config->enableMidFlag != 0) {
        *(long long *)object |= 0x10000;
    }
    if (config->enableHighFlag != 0) {
        *(long long *)object |= 0x1000000000LL;
    }
    if (func_02023588(0x208a) != 0) {
        *(long long *)object |= 0x8000000000LL;
    }
    func_ov022_0209f6e0(object);
}
