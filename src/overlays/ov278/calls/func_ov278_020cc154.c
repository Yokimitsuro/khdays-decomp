/* Constructor of the ov278 enemy (x2 with ov278). Installs the handlers (+8, +0xc, +0x1c message,
 * +0x28, +0x2c, +0x30 update, +0x1d0 hit filter, +0x1dc move player, +0x1ec, +0x1f4), sets the
 * +0x1c9 kind to 2, the +0x64 pose (scale 2.75), bits 3-4 of +0x1ae and bits 5 and 7 of the +0x60
 * high byte; builds the +0x384 rig from pose 0 (subscribed to +0x9c, owned by the enemy with
 * callback 020cbfc4) with its +0x38c work list and two bone attachments (+0x39c, +0x3a0), and the
 * +0x388 mount rig from pose 0x3c with its +0x390 work list (scaled 1/1/1 with flag 1, raised
 * 1/8, list rate 8); resolves the +0x3ac marker, builds the ten sub-items of data_ov278_020d6244
 * into the +0x3b0 pair table (all hidden; the sixth owned by the enemy with callback 020cc110),
 * creates the two rider controllers (+0x3b4 / +0x3b8, 020cce20 / 020cdc84) sharing the +0x19c
 * team byte, and reserves the +0x144 / +0x22c shape handles: a capsule (0.5 below, length 1.0,
 * radius 0.45) at +0x394 and +0x3a4 (radius scaled by 1.25), and a placement (scale 0.75) at
 * +0x398 and +0x3a8 (scaled by 1.5). Loads sound 0x166. */
typedef unsigned short u16;
typedef void (*Callback)(void);
typedef struct { int x, y, z; } Vec3;
typedef struct { int id[10]; } IdTable;
typedef struct { Vec3 pos; int scale; } Placement;
typedef struct { Vec3 pos; Vec3 axis; int length; int radius; } Capsule;
struct Pair { int res; int handle; };

extern void func_ov278_020cc5c0(void);
extern void func_ov278_020cc630(void);
extern void func_ov278_020cc6f8(void);
extern void func_ov278_020cc838(void);
extern void func_ov278_020cc86c(void);
extern void func_ov278_020ced5c(void);
extern void func_ov278_020cedb8(void);
extern void func_ov278_020cca44(void);
extern void func_ov278_020ccd14(void);
extern void func_ov278_020ccd68(void);
extern void func_ov278_020cbfc4(void);
extern void func_ov278_020cc110(void);
extern void *func_ov107_020c9440(char *self, int index);
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
extern int func_ov278_020cce20(char *self);
extern int func_ov278_020cdc84(char *self);
extern int *func_01fffca8(void *pool, int elementSize, int capacity);
extern int func_ov107_020c3210(const Capsule *capsule);
extern int func_ov107_020c319c(const Placement *placement);
extern void func_0203355c(int resourceId);
extern IdTable data_ov278_020d6244;
extern char data_ov278_020d646c[];
extern char data_ov278_020d6474[];
extern const char data_ov278_020d6480[];
extern const Vec3 data_02041dc8;
extern const Vec3 data_02042264;

static inline int FX_Mul(int a, int b) {
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov278_020cc154(char *self)
{
    IdTable ids = data_ov278_020d6244;
    Capsule cap;
    Placement place;
    u16 hw;
    int i;
    int *slot;

    *(Callback *)(self + 0x8) = func_ov278_020cc5c0;
    *(Callback *)(self + 0xc) = func_ov278_020cc630;
    *(Callback *)(self + 0x28) = func_ov278_020cc6f8;
    *(Callback *)(self + 0x2c) = func_ov278_020cc838;
    *(Callback *)(self + 0x1c) = func_ov278_020cc86c;
    *(Callback *)(self + 0x30) = func_ov278_020ced5c;
    *(Callback *)(self + 0x1d0) = func_ov278_020cedb8;
    *(Callback *)(self + 0x1dc) = func_ov278_020cca44;
    *(Callback *)(self + 0x1f4) = func_ov278_020ccd14;
    *(Callback *)(self + 0x1ec) = func_ov278_020ccd68;
    *(unsigned char *)(self + 0x1c9) = 2;
    *(int *)(self + 0x70) = 0x2c00;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0x2c00;
    *(int *)(self + 0x6c) = 0;
    *(u16 *)(self + 0x100 + 0xae) |= 0x18;
    hw = *(u16 *)(self + 0x60);
    *(u16 *)(self + 0x60) = (hw & ~0xff00) |
        ((((((unsigned int)hw << 0x10) >> 0x18) | 0x20) << 0x18) >> 0x10);
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(self, 0));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    *(int *)(self + 0x38c) = func_0203d15c(0x24);
    func_0202a388(*(int *)(self + 0x38c), *(int *)(*(int *)(self + 0x384) + 0x88), func_ov107_020c9440(self, 1), 0xc);
    func_0203b9ac(*(int *)(self + 0x384), *(int *)(self + 0x38c));
    *(Callback *)(*(int *)(self + 0x384) + 0x74) = func_ov278_020cbfc4;
    *(char **)(*(int *)(self + 0x384) + 0x84) = self;
    *(int *)(self + 0x39c) = func_0203bee8(*(int *)(self + 0x384), 3, data_ov278_020d646c);
    *(int *)(self + 0x3a0) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov278_020d6474);
    hw = *(u16 *)(self + 0x60);
    *(u16 *)(self + 0x60) = (hw & ~0xff00) |
        ((((((unsigned int)hw << 0x10) >> 0x18) | 0x80) << 0x18) >> 0x10);
    *(int *)(self + 0x388) = func_0203b898(func_ov107_020c9440(self, 0x3c));
    func_ov107_020c9074(self, *(int *)(self + 0x388));
    *(int *)(self + 0x390) = func_0203d15c(0x24);
    func_0202a388(*(int *)(self + 0x390), *(int *)(*(int *)(self + 0x388) + 0x88), func_ov107_020c9440(self, 1), 0xc);
    func_0203b9ac(*(int *)(self + 0x388), *(int *)(self + 0x390));
    func_0203ca50(*(int *)(self + 0x388) + 4, 0x1000, 1, 0x1000);
    func_0203ca14(*(int *)(self + 0x388) + 4, 0, 0x200, 0);
    func_02016d10(*(int *)(*(int *)(*(int *)(self + 0x388) + 0x88) + 0x78), 8);
    *(int *)(self + 0x3ac) = func_ov107_020c9e50(func_ov107_020c9440(self, 0x3f), data_ov278_020d6480);
    *(int *)(self + 0x3b0) = func_0203d15c(0x50);
    for (i = 0; i < 10; i++) {
        ((struct Pair *)*(int *)(self + 0x3b0))[i].res = func_0203b898(func_ov107_020c9440(self, ids.id[i]));
        func_ov107_020c9074(self, ((struct Pair *)*(int *)(self + 0x3b0))[i].res);
        *(int *)(((struct Pair *)*(int *)(self + 0x3b0))[i].res + 0x5c) |= 2;
    }
    *(Callback *)(((struct Pair *)*(int *)(self + 0x3b0))[5].res + 0x6c) = func_ov278_020cc110;
    *(char **)(((struct Pair *)*(int *)(self + 0x3b0))[5].res + 0x84) = self;
    *(int *)(self + 0x3b4) = func_ov278_020cce20(self);
    *(unsigned char *)(*(int *)(self + 0x3b4) + 0x19c) = *(unsigned char *)(self + 0x19c);
    *(int *)(self + 0x3b8) = func_ov278_020cdc84(self);
    *(unsigned char *)(*(int *)(self + 0x3b8) + 0x19c) = *(unsigned char *)(self + 0x19c);
    *(int *)(self + 0x3c0) = 0;
    cap.pos.x = 0;
    cap.pos.y = -0x800;
    cap.pos.z = 0;
    cap.axis = data_02042264;
    cap.length = 0x1000;
    cap.radius = 0x732;
    slot = func_01fffca8(self + 0x144, 4, 100);
    *(int *)(self + 0x394) = *slot = func_ov107_020c3210(&cap);
    place.pos = data_02041dc8;
    place.scale = 0xc00;
    slot = func_01fffca8(self + 0x144, 4, 100);
    *(int *)(self + 0x398) = *slot = func_ov107_020c319c(&place);
    place.scale = FX_Mul(place.scale, 0x1800);
    *(int *)(self + 0x3a8) = (int)func_01fffca8(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x3a8) = func_ov107_020c319c(&place);
    cap.radius = FX_Mul(cap.radius, 0x1400);
    *(int *)(self + 0x3a4) = (int)func_01fffca8(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x3a4) = func_ov107_020c3210(&cap);
    func_0203355c(0x166);
}
