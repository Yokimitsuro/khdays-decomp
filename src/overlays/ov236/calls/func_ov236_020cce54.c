/* Constructor of the front rider controller (created by 020cce20). Installs its handlers (+8,
 * +0xc, +0x10, +0x1c message, +0x20, +0x28, +0x30 update, +0x34, +0x1d0 hit filter, +0x1d4, +0x1dc
 * move player), sets kind 2, clears +0x54 / +0x58, the +0x64 pose (scale 2.75), bits 3-4 of +0x1ae,
 * bits 3, 7 and 11 of +0x1b0 and bit 5 of the +0x60 high byte. From the owner's +0x394 pool it
 * builds the +0x384 rider (pose 0x18, subscribed to +0x9c) with its +0x388 work list (pose 0x19)
 * and four bone attachments (+0x3a0..+0x3ac), and the +0x38c mount (pose 0x3d) with its +0x390 work
 * list (scaled 1/1/1 with flag 1, raised 1/8, list rate 8), then the five hidden sub-items of
 * data_ov236_020d6314 into the +0x3b8 pair table. Two capsules (length 1.5, radius 0.5, along the
 * x and z axes) are reserved at +0x398 / +0x39c on the +0x144 pool and, with radius scaled by 1.125
 * and flag bit 0 set, at +0x3b0 / +0x3b4 on the +0x22c pool. Both rider counters (+0x3bc / +0x3be)
 * start at 1, +0x3c0 bit 0 is set, the presence hook runs and both rigs re-init. */
typedef unsigned short u16;
typedef void (*Callback)(void);
typedef struct { int x, y, z; } Vec3;
typedef struct { int id[5]; } IdTable5;
typedef struct { Vec3 pos; Vec3 axis; int length; int radius; } Capsule;
struct Pair { int res; int handle; };
typedef struct { unsigned f : 8; } B8;
struct b1 { unsigned int b0 : 1; };

extern void func_ov236_020cd300(void);
extern void func_ov236_020cd368(void);
extern void func_ov236_020cd450(void);
extern void func_ov236_020cd508(void);
extern void func_ov236_020cd5a0(void);
extern void func_ov236_020d1848(void);
extern void func_ov236_020cd780(void);
extern void func_ov236_020cd8cc(void);
extern void func_ov236_020cd834(void);
extern void func_ov236_020d1894(void);
extern void func_ov236_020cd918(void);
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
extern int *func_01fffca8(void *pool, int elementSize, int capacity);
extern int func_ov107_020c3210(const Capsule *capsule);
extern void func_ov236_020cda7c(char *self);
extern void func_0203c7ac(int item, int a);
extern IdTable5 data_ov236_020d6314;
extern char data_ov236_020d64c8[];
extern char data_ov236_020d64d4[];
extern const Vec3 data_02041dc8;
extern const Vec3 data_0204224c;
extern const Vec3 data_02042270;

static inline int FX_Mul(int a, int b) {
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov236_020cce54(char *self)
{
    IdTable5 ids = data_ov236_020d6314;
    Capsule cap;
    Vec3 zero;
    u16 hw;
    int i;
    int *slot;

    *(Callback *)(self + 0x8) = func_ov236_020cd300;
    *(Callback *)(self + 0xc) = func_ov236_020cd368;
    *(Callback *)(self + 0x10) = func_ov236_020cd450;
    *(Callback *)(self + 0x20) = func_ov236_020cd508;
    *(Callback *)(self + 0x1c) = func_ov236_020cd5a0;
    *(Callback *)(self + 0x30) = func_ov236_020d1848;
    *(Callback *)(self + 0x34) = func_ov236_020cd780;
    *(Callback *)(self + 0x28) = func_ov236_020cd8cc;
    *(Callback *)(self + 0x1d4) = func_ov236_020cd834;
    *(Callback *)(self + 0x1d0) = func_ov236_020d1894;
    *(Callback *)(self + 0x1dc) = func_ov236_020cd918;
    *(unsigned char *)(self + 0x1c9) = 2;
    *(int *)(self + 0x54) = 0;
    *(int *)(self + 0x58) = 0;
    /* default scales first: the overwritten stores are dropped after scheduling but still spend
     * the block's scheduling budget, which keeps the ROM's argument order for the rest of it */
    *(int *)(self + 0x70) = 0x1000;
    *(int *)(self + 0x70) = 0x2c00;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0x1000;
    *(int *)(self + 0x68) = 0x2c00;
    *(int *)(self + 0x6c) = 0;
    *(u16 *)(self + 0x100 + 0xae) |= 0x18;
    *(u16 *)(self + 0x100 + 0xb0) |= 0x888;
    hw = *(u16 *)(self + 0x60);
    *(u16 *)(self + 0x60) = (hw & ~0xff00) |
        ((((((unsigned int)hw << 0x10) >> 0x18) | 0x20) << 0x18) >> 0x10);
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(*(int *)(self + 0x394), 0x18));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    *(int *)(self + 0x388) = func_0203d15c(0x24);
    func_0202a388(*(int *)(self + 0x388), *(int *)(*(int *)(self + 0x384) + 0x88), func_ov107_020c9440(*(int *)(self + 0x394), 0x19), 0xc);
    func_0203b9ac(*(int *)(self + 0x384), *(int *)(self + 0x388));
    *(int *)(self + 0x3a0) = func_0203bee8(*(int *)(self + 0x384), 3, data_ov236_020d64c8);
    *(int *)(self + 0x3a4) = func_0203bee8(*(int *)(self + 0x384), 3, data_ov236_020d64d4);
    *(int *)(self + 0x3a8) = func_0203bee8(*(int *)(self + 0x384), 3, data_ov236_020d64c8);
    *(int *)(self + 0x3ac) = func_0203bee8(*(int *)(self + 0x384), 3, data_ov236_020d64d4);
    *(int *)(self + 0x38c) = func_0203b898(func_ov107_020c9440(*(int *)(self + 0x394), 0x3d));
    func_ov107_020c9074(self, *(int *)(self + 0x38c));
    *(int *)(self + 0x390) = func_0203d15c(0x24);
    func_0202a388(*(int *)(self + 0x390), *(int *)(*(int *)(self + 0x38c) + 0x88), func_ov107_020c9440(*(int *)(self + 0x394), 0x19), 0xc);
    func_0203b9ac(*(int *)(self + 0x38c), *(int *)(self + 0x390));
    func_0203ca50(*(int *)(self + 0x38c) + 4, 0x1000, 1, 0x1000);
    func_0203ca14(*(int *)(self + 0x38c) + 4, 0, 0x200, 0);
    func_02016d10(*(int *)(*(int *)(*(int *)(self + 0x38c) + 0x88) + 0x78), 8);
    *(int *)(self + 0x3b8) = func_0203d15c(0x28);
    for (i = 0; i < 5; i++) {
        ((struct Pair *)*(int *)(self + 0x3b8))[i].res = func_0203b898(func_ov107_020c9440(*(int *)(self + 0x394), ids.id[i]));
        func_ov107_020c9074(self, ((struct Pair *)*(int *)(self + 0x3b8))[i].res);
        *(int *)(((struct Pair *)*(int *)(self + 0x3b8))[i].res + 0x5c) |= 2;
    }
    zero = data_02041dc8;
    cap.pos = zero;
    cap.axis = data_0204224c;
    cap.length = 0x1800;
    cap.radius = 0x800;
    slot = func_01fffca8(self + 0x144, 4, 100);
    *(int *)(self + 0x398) = *slot = func_ov107_020c3210(&cap);
    cap.radius = FX_Mul(cap.radius, 0x1200);
    *(int *)(self + 0x3b0) = (int)func_01fffca8(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x3b0) = func_ov107_020c3210(&cap);
    ((B8 *)(*(int *)(self + 0x3b0) + 8))->f |= 1;
    cap.pos = zero;
    cap.axis = data_02042270;
    cap.length = 0x1800;
    cap.radius = 0x800;
    slot = func_01fffca8(self + 0x144, 4, 100);
    *(int *)(self + 0x39c) = *slot = func_ov107_020c3210(&cap);
    cap.radius = FX_Mul(cap.radius, 0x1200);
    *(int *)(self + 0x3b4) = (int)func_01fffca8(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x3b4) = func_ov107_020c3210(&cap);
    ((B8 *)(*(int *)(self + 0x3b4) + 8))->f |= 1;
    *(short *)(self + 0x300 + 0xbc) = *(short *)(self + 0x300 + 0xbe) = 1;
    ((struct b1 *)(self + 0x3c0))->b0 = 1;
    func_ov236_020cda7c(self);
    func_0203c7ac(*(int *)(self + 0x384), 0);
    func_0203c7ac(*(int *)(self + 0x38c), 0);
}
