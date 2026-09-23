/* Constructor of the rear rider controller (created by 020cdc84). Installs its handlers (+8, +0xc,
 * +0x10, +0x1c message, +0x20, +0x28, +0x30 update, +0x34, +0x1d0 hit filter, +0x1d4, +0x1dc move
 * player), sets kind 2, +0x54 = 0 / +0x58 = 0.5, the +0x64 pose (scale 2.75), bits 3-4 of +0x1ae,
 * bits 3, 7 and 11 of +0x1b0 and bit 5 of the +0x60 high byte. From the owner's +0x384 pool it
 * builds the +0x388 rider (pose 0x2a, subscribed to +0x9c) with its +0x38c work list (pose 0x2b)
 * and six bone attachments (+0x3a8..+0x3bc), and the +0x390 mount (pose 0x3e) with its +0x394 work
 * list (scaled 1/1/1 with flag 1, raised 1/8, list rate 8), resolves the +0x3c8 marker and builds
 * the four hidden sub-items of data_ov236_020d636c into the +0x3cc pair table. Four capsules
 * (length 1.4, radius 0.375, along y, z, y and x) are reserved at +0x398..+0x3a4 on the +0x144 pool
 * and two (radius scaled by 1.125, along z and x) at +0x3c0 / +0x3c4 on the +0x22c pool. Both
 * rider counters (+0x3d0 / +0x3d2) start at 1, +0x3d4 bit 0 is set, the presence hook runs and
 * both rigs re-init. */
typedef unsigned short u16;
typedef void (*Callback)(void);
typedef struct { int x, y, z; } Vec3;
typedef struct { int id[4]; } IdTable4;
typedef struct { Vec3 pos; Vec3 axis; int length; int radius; } Capsule;
struct Pair { int res; int handle; };
struct b1 { unsigned int b0 : 1; };

extern void func_ov236_020ce1c0(void);
extern void func_ov236_020ce230(void);
extern void func_ov236_020ce2d0(void);
extern void func_ov236_020ce430(void);
extern void func_ov236_020ce4c8(void);
extern void func_ov236_020d374c(void);
extern void WM_EndKeySharing_ov236_0x020ce6fc(void);
extern void func_ov236_020ce7d4(void);
extern void func_ov236_020ce708(void);
extern void func_ov236_020d3798(void);
extern void func_ov236_020ce820(void);
extern void *func_ov107_020c9440(int pool, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern int func_0203d15c(int size);
extern void func_0202a388(int a, int b, void *c, int d);
extern void func_0203b9ac(int a, int b);
extern int func_0203bee8(int item, int kind, void *name);
extern void func_ov107_020c9074(char *self, int item);
extern void func_0203ca50(int srt, int sx, int sy, int sz);
extern void func_0203ca14(int srt, int x, int y, int z);
extern void func_02016d10(int nList, int nValue);
extern int func_ov107_020c9e50(void *item, const char *name);
extern int *func_01fffca8(void *pool, int elementSize, int capacity);
extern int func_ov107_020c3210(const Capsule *capsule);
extern void func_ov236_020ce984(char *self);
extern void func_0203c7ac(int item, int a);
extern IdTable4 data_ov236_020d636c;
extern char data_ov236_020d64e0[];
extern char data_ov236_020d64ec[];
extern char data_ov236_020d64f8[];
extern char data_ov236_020d6504[];
extern const char data_ov236_020d6510[];
extern const Vec3 data_02041dc8;
extern const Vec3 data_02042264;
extern const Vec3 data_02042270;
extern const Vec3 data_0204224c;

static inline int FX_Mul(int a, int b) {
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov236_020cdcb8(char *self)
{
    IdTable4 ids = data_ov236_020d636c;
    Capsule cap;
    Vec3 axisY;
    Vec3 axisZ;
    Vec3 axisX;
    u16 hw;
    int i;
    int *slot;

    *(Callback *)(self + 0x8) = func_ov236_020ce1c0;
    *(Callback *)(self + 0xc) = func_ov236_020ce230;
    *(Callback *)(self + 0x10) = func_ov236_020ce2d0;
    *(Callback *)(self + 0x20) = func_ov236_020ce430;
    *(Callback *)(self + 0x1c) = func_ov236_020ce4c8;
    *(Callback *)(self + 0x30) = func_ov236_020d374c;
    *(Callback *)(self + 0x34) = WM_EndKeySharing_ov236_0x020ce6fc;
    *(Callback *)(self + 0x28) = func_ov236_020ce7d4;
    *(Callback *)(self + 0x1d4) = func_ov236_020ce708;
    *(Callback *)(self + 0x1d0) = func_ov236_020d3798;
    *(Callback *)(self + 0x1dc) = func_ov236_020ce820;
    *(unsigned char *)(self + 0x1c9) = 2;
    *(int *)(self + 0x54) = 0;
    *(int *)(self + 0x58) = 0x800;
    *(int *)(self + 0x70) = 0x2c00;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0x2c00;
    *(int *)(self + 0x6c) = 0;
    *(u16 *)(self + 0x100 + 0xae) |= 0x18;
    *(u16 *)(self + 0x100 + 0xb0) |= 0x888;
    hw = *(u16 *)(self + 0x60);
    *(u16 *)(self + 0x60) = (hw & ~0xff00) |
        ((((((unsigned int)hw << 0x10) >> 0x18) | 0x20) << 0x18) >> 0x10);
    *(int *)(self + 0x388) = func_0203b898(func_ov107_020c9440(*(int *)(self + 0x384), 0x2a));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x388));
    *(int *)(self + 0x38c) = func_0203d15c(0x24);
    func_0202a388(*(int *)(self + 0x38c), *(int *)(*(int *)(self + 0x388) + 0x88), func_ov107_020c9440(*(int *)(self + 0x384), 0x2b), 0xc);
    func_0203b9ac(*(int *)(self + 0x388), *(int *)(self + 0x38c));
    *(int *)(self + 0x3a8) = func_0203bee8(*(int *)(self + 0x388), 1, data_ov236_020d64e0);
    *(int *)(self + 0x3ac) = func_0203bee8(*(int *)(self + 0x388), 3, data_ov236_020d64ec);
    *(int *)(self + 0x3b0) = func_0203bee8(*(int *)(self + 0x388), 1, data_ov236_020d64f8);
    *(int *)(self + 0x3b4) = func_0203bee8(*(int *)(self + 0x388), 3, data_ov236_020d6504);
    *(int *)(self + 0x3b8) = func_0203bee8(*(int *)(self + 0x388), 3, data_ov236_020d64e0);
    *(int *)(self + 0x3bc) = func_0203bee8(*(int *)(self + 0x388), 3, data_ov236_020d64f8);
    *(int *)(self + 0x390) = func_0203b898(func_ov107_020c9440(*(int *)(self + 0x384), 0x3e));
    func_ov107_020c9074(self, *(int *)(self + 0x390));
    *(int *)(self + 0x394) = func_0203d15c(0x24);
    func_0202a388(*(int *)(self + 0x394), *(int *)(*(int *)(self + 0x390) + 0x88), func_ov107_020c9440(*(int *)(self + 0x384), 0x2b), 0xc);
    func_0203b9ac(*(int *)(self + 0x390), *(int *)(self + 0x394));
    func_0203ca50(*(int *)(self + 0x390) + 4, 0x1000, 1, 0x1000);
    func_0203ca14(*(int *)(self + 0x390) + 4, 0, 0x200, 0);
    func_02016d10(*(int *)(*(int *)(*(int *)(self + 0x390) + 0x88) + 0x78), 8);
    *(int *)(self + 0x3c8) = func_ov107_020c9e50(func_ov107_020c9440(*(int *)(self + 0x384), 0x3f), data_ov236_020d6510);
    *(int *)(self + 0x3cc) = func_0203d15c(0x20);
    for (i = 0; i < 4; i++) {
        ((struct Pair *)*(int *)(self + 0x3cc))[i].res = func_0203b898(func_ov107_020c9440(*(int *)(self + 0x384), ids.id[i]));
        func_ov107_020c9074(self, ((struct Pair *)*(int *)(self + 0x3cc))[i].res);
        *(int *)(((struct Pair *)*(int *)(self + 0x3cc))[i].res + 0x5c) |= 2;
    }
    cap.pos = data_02041dc8;
    axisY = data_02042264;
    cap.axis = axisY;
    cap.length = 0x1666;
    cap.radius = 0x600;
    slot = func_01fffca8(self + 0x144, 4, 100);
    *(int *)(self + 0x398) = *slot = func_ov107_020c3210(&cap);
    axisZ = data_02042270;
    cap.axis = axisZ;
    slot = func_01fffca8(self + 0x144, 4, 100);
    *(int *)(self + 0x39c) = *slot = func_ov107_020c3210(&cap);
    cap.axis = axisY;
    slot = func_01fffca8(self + 0x144, 4, 100);
    *(int *)(self + 0x3a0) = *slot = func_ov107_020c3210(&cap);
    axisX = data_0204224c;
    cap.axis = axisX;
    slot = func_01fffca8(self + 0x144, 4, 100);
    *(int *)(self + 0x3a4) = *slot = func_ov107_020c3210(&cap);
    cap.radius = FX_Mul(cap.radius, 0x1200);
    cap.axis = axisZ;
    *(int *)(self + 0x3c0) = (int)func_01fffca8(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x3c0) = func_ov107_020c3210(&cap);
    cap.axis = axisX;
    *(int *)(self + 0x3c4) = (int)func_01fffca8(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x3c4) = func_ov107_020c3210(&cap);
    *(short *)(self + 0x300 + 0xd0) = *(short *)(self + 0x300 + 0xd2) = 1;
    ((struct b1 *)(self + 0x3d4))->b0 = 1;
    func_ov236_020ce984(self);
    func_0203c7ac(*(int *)(self + 0x388), 0);
    func_0203c7ac(*(int *)(self + 0x390), 0);
}
