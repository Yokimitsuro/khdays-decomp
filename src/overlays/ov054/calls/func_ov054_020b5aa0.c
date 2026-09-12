typedef unsigned char u8;

struct InitConfig {
    int type;
    int slot;
    u8 bit;
    u8 pad[3];
    int low;
    int mid;
    int high;
};

struct OpenParams { int enabled, limit, scale, unused0c, unused10; };
struct RigHeader { int unused, rig; };

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void func_0202b850(int, unsigned short, int, void *, int);
extern void func_0202b914(int, void *, int, int);
extern int func_02020a9c(void);
extern int func_0202bfcc(int);
extern void func_0202d968(void *, int);
extern int func_02016f10(void *, void *);
extern void func_ov022_0209f6e0(void *);

extern void func_ov054_020b5d5c(void);
extern void func_ov054_020b5ee0(void);
extern void func_ov054_020b5fec(void);
extern void func_ov054_020b5cd0(void);
extern void func_ov054_020b5d3c(void);
extern void func_ov054_020b6024(void);
struct Runtime;
typedef u8 (*SetupHandler)(struct Runtime *);
typedef int (*StateHandler)(int *);
extern u8 func_ov054_020b61a8(struct Runtime *);
extern int func_ov054_020b6c6c(int *);
extern void *data_ov054_020b74a0;
extern char data_ov054_020b741c[];
extern char data_ov054_020b73bc[];
extern char data_ov054_020b73cc[];
extern char data_ov054_020b73ac[];
extern char data_ov054_020b738c[];
extern char data_ov054_020b739c[];

static inline int bone(char *obj) {
    int rig = ((struct RigHeader *)(*(int *)(obj + 0x20) + 0x24))->rig;
    return rig != 0 ? rig + 0x40 : 0;
}

void func_ov054_020b5aa0(struct InitConfig *cfg) {
    struct OpenParams p;
    char *obj = (char *)NNSi_FndGetCurrentRootHeap();
    int i, b, mode;

    data_ov054_020b74a0 = obj;
    obj[9] = (char)cfg->type;
    obj[0x4bc] = (char)cfg->slot;
    obj[8] = cfg->bit;
    *(int *)(obj + 0xc) = 5;
    *(long long *)obj = 0;

    p.enabled = 1;
    p.scale = 0x900;
    p.limit = 0xf00;
    func_0202b850(*(signed char *)(obj + 0x4bc),
                  (unsigned short)(1 << *(u8 *)(obj + 8)), 0, &p, 0);
    func_0202b914(*(signed char *)(obj + 0x4bc), data_ov054_020b741c,
                  1, cfg->type + 7);

    *(void **)(obj + 0x664) = (void *)&func_ov054_020b5d5c;
    *(void **)(obj + 0x668) = (void *)&func_ov054_020b5ee0;
    *(void **)(obj + 0x66c) = (void *)&func_ov054_020b5fec;
    *(void **)(obj + 0x670) = 0;
    *(void **)(obj + 0x674) = 0;
    *(void **)(obj + 0x678) = (void *)&func_ov054_020b5cd0;
    *(void **)(obj + 0x67c) = (void *)&func_ov054_020b5d3c;
    *(void **)(obj + 0x684) = (void *)&func_ov054_020b6024;

    mode = func_02020a9c();
    if (mode != 0x2a) {
        *(SetupHandler *)(obj + 0x68c) = func_ov054_020b61a8;
    } else {
        *(SetupHandler *)(obj + 0x68c) = 0;
    }
    *(StateHandler *)(obj + 0x688) = func_ov054_020b6c6c;

    func_0202d968(obj + 0x20, func_0202bfcc(*(signed char *)(obj + 0x4bc)));
    i = 0;
    goto test;
body:
    *(int *)(obj + i * sizeof(int) + 0x514) = -1;
    i++;
test:
    if (i < 5) goto body;

    b = bone(obj);
    *(int *)(obj + 0x520) = b ? func_02016f10((void *)b, data_ov054_020b73bc) : -1;
    b = bone(obj);
    *(int *)(obj + 0x518) = b ? func_02016f10((void *)b, data_ov054_020b73cc) : -1;
    b = bone(obj);
    *(int *)(obj + 0x514) = b ? func_02016f10((void *)b, data_ov054_020b73ac) : -1;
    b = bone(obj);
    *(int *)(obj + 0x51c) = b ? func_02016f10((void *)b, data_ov054_020b738c) : -1;
    b = bone(obj);
    *(int *)(obj + 0x524) = b ? func_02016f10((void *)b, data_ov054_020b739c) : -1;

    if (cfg->low) *(long long *)obj |= 0x20;
    if (cfg->mid) *(long long *)obj |= 0x10000;
    if (cfg->high) *(long long *)obj |= 0x1000000000LL;
    func_ov022_0209f6e0(obj);
}
