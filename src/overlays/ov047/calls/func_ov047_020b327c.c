/* Constructor for the ov047 panel object: takes the root heap block as the object,
 * publishes it in the overlay's global slot, stamps the identity fields from the
 * caller's config, opens the object with its display parameters under a fixed name,
 * installs the handler table at +0x664, binds the rig, invalidates the five cached
 * slots at +0x514, resolves four bone indices off the rig, and finally raises the
 * three optional feature flags the config asked for. */
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

extern void func_ov047_020b34cc(void);
extern void func_ov047_020b3630(void);
extern void func_ov047_020b37a4(void);
extern void func_ov047_020b3474(void);
extern void func_ov047_020b34ac(void);
extern void func_ov047_020b36c8(void);
extern void func_ov047_020b37dc(void);
extern void func_ov047_020b3e34(void);

extern void *data_ov047_020b4380;
extern const char data_ov047_020b4308[];
extern int data_ov047_020b423c;
extern int data_ov047_020b422c;
extern int data_ov047_020b421c;
extern int data_ov047_020b420c;

void func_ov047_020b327c(struct PanelInitConfig *config)
{
    struct Ov044OpenParams params;
    char *object = (char *)NNSi_FndGetCurrentRootHeap();
    int i;
    int bone;

    data_ov047_020b4380 = object;
    object[9] = (char)config->objectType;
    object[0x4bc] = (char)config->slotId;
    object[8] = config->bitIndex;
    *(int *)(object + 0xc) = 0x11;
    *(long long *)object = 0;

    params.enabled = 1;
    params.scale = 9 << 8;
    params.limit = 7 << 8;
    func_0202b850(*(signed char *)(object + 0x4bc),
                  (u16)(1 << *(u8 *)(object + 8)), 0, &params, 0);

    func_0202b914(*(signed char *)(object + 0x4bc), (void *)data_ov047_020b4308, 1,
                  config->objectType + 7);

    *(void **)(object + 0x664 + 0x00) = (void *)&func_ov047_020b34cc;
    *(void **)(object + 0x664 + 0x04) = (void *)&func_ov047_020b3630;
    *(void **)(object + 0x664 + 0x08) = (void *)&func_ov047_020b37a4;
    *(void **)(object + 0x664 + 0x0c) = 0;
    *(void **)(object + 0x664 + 0x10) = 0;
    *(void **)(object + 0x664 + 0x14) = (void *)&func_ov047_020b3474;
    *(void **)(object + 0x664 + 0x18) = (void *)&func_ov047_020b34ac;
    *(void **)(object + 0x664 + 0x20) = (void *)&func_ov047_020b36c8;
    *(void **)(object + 0x664 + 0x28) = (void *)&func_ov047_020b37dc;
    *(void **)(object + 0x664 + 0x24) = (void *)&func_ov047_020b3e34;

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
        ? func_02016f10((void *)bone, &data_ov047_020b423c) : -1;
    bone = Ov044_GetBoneBase(object);
    *(int *)(object + 0x518) = bone != 0
        ? func_02016f10((void *)bone, &data_ov047_020b422c) : -1;
    bone = Ov044_GetBoneBase(object);
    *(int *)(object + 0x51c) = bone != 0
        ? func_02016f10((void *)bone, &data_ov047_020b421c) : -1;
    bone = Ov044_GetBoneBase(object);
    *(int *)(object + 0x524) = bone != 0
        ? func_02016f10((void *)bone, &data_ov047_020b420c) : -1;

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
