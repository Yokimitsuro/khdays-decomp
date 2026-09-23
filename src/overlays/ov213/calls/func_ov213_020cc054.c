/* Constructor of the ov213 enemy (x2 with ov273). Installs the handlers (+8, +0xc, +0x1c message,
 * +0x20, +0x28, +0x2c, +0x30, +0x34 update, +0x1d0 hit filter, +0x1dc, +0x1e0), sets bit 6 of the
 * +0x60 high byte, the +0x64 pose (scale 2.0) and bits 3-4 of +0x1ae; builds the +0x384 body rig
 * (pose 0, subscribed to +0x9c, lowered 2.0, owned by the enemy with callback 020cbfc8) with its
 * embedded +0x38c work list (pose 1) and four bone attachments (+0x3e8..+0x3f4, the first's +0x14
 * becoming the +0x2cc anchor), and the +0x388 tail rig (pose 0x1d, lowered 2.0) with its embedded
 * +0x3b0 list (pose 0x1e); builds the eight hidden sub-items of data_ov213_020d2d74 into the +0x430
 * pair table and registers action 2/3 (rate 0.5). Shapes: a placement (scale 2.0) at +0x3d4 on
 * the +0x22c pool and an oriented box (half-extents 0.85 / 1.7 / 0.68) at +0x3d8 on the +0x144
 * pool. Creates the 020d0574 companion (+0x3dc) and eight 020d1628 / 020d238c children (+0x3e0 /
 * +0x3e4), then loads sound 0x122. */
typedef unsigned short u16;
typedef void (*Callback)(void);
typedef struct { int x, y, z; } Vec3;
typedef struct { int id[8]; } IdTable8;
typedef struct { Vec3 pos; int scale; } Placement;
typedef struct { Vec3 pos; Vec3 axis[3]; int ext[3]; } Box;
struct Pair { int res; int handle; };

extern void func_ov213_020cc464(void);
extern void func_ov213_020cc4cc(void);
extern void func_ov213_020cc584(void);
extern void func_ov213_020cc600(void);
extern void func_ov213_020ccb98(void);
extern void func_ov213_020ccfc4(void);
extern void func_ov213_020ccc58(void);
extern void func_ov213_020cccc0(void);
extern void func_ov213_020cd010(void);
extern void func_ov213_020ccd28(void);
extern void func_ov213_020cd258(void);
extern void func_ov213_020cbfc8(void);
extern void *func_ov107_020c9440(char *self, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern void func_0203ca14(int srt, int x, int y, int z);
extern void func_0202a388(void *list, int b, void *c, int d);
extern void func_0203b9ac(int a, void *list);
extern int func_0203bee8(int item, int kind, void *name);
extern int func_0203d15c(int size);
extern void func_ov107_020c9074(char *self, int item);
extern void func_ov107_020c92b0(char *self, int slot, int a, const Vec3 *v, int c);
extern int *func_01fffca8(void *pool, int elementSize, int capacity);
extern int func_ov107_020c319c(const Placement *placement);
extern int func_ov107_020c32b8(const Box *box);
extern int func_ov213_020d0574(char *self);
extern int func_ov213_020d1628(char *self);
extern int func_ov213_020d238c(char *self);
extern void func_0203355c(int resourceId);
extern IdTable8 data_ov213_020d2d74;
extern char data_ov213_020d2fac[];
extern char data_ov213_020d2fb4[];
extern char data_ov213_020d2fbc[];
extern char data_ov213_020d2fcc[];
extern const Vec3 data_02041dc8;
extern const Vec3 data_02042270;
extern const Vec3 data_02042264;
extern const Vec3 data_02042258;

void func_ov213_020cc054(char *self)
{
    IdTable8 ids = data_ov213_020d2d74;
    Box box;
    Placement place;
    Vec3 zero;
    u16 hw;
    int i;
    int *slot;

    *(Callback *)(self + 0x8) = func_ov213_020cc464;
    *(Callback *)(self + 0xc) = func_ov213_020cc4cc;
    *(Callback *)(self + 0x20) = func_ov213_020cc584;
    *(Callback *)(self + 0x1c) = func_ov213_020cc600;
    *(Callback *)(self + 0x34) = func_ov213_020ccb98;
    *(Callback *)(self + 0x30) = func_ov213_020ccfc4;
    *(Callback *)(self + 0x28) = func_ov213_020ccc58;
    *(Callback *)(self + 0x2c) = func_ov213_020cccc0;
    *(Callback *)(self + 0x1d0) = func_ov213_020cd010;
    *(Callback *)(self + 0x1dc) = func_ov213_020ccd28;
    *(Callback *)(self + 0x1e0) = func_ov213_020cd258;
    hw = *(u16 *)(self + 0x60);
    *(u16 *)(self + 0x60) = (hw & ~0xff00) |
        ((((((unsigned int)hw << 0x10) >> 0x18) | 0x40) << 0x18) >> 0x10);
    /* default scale / pose first: the overwritten stores are dropped after scheduling but spend
     * the block's scheduling budget (keeps the ROM's argument order of the attachment calls) */
    *(int *)(self + 0x70) = 0x1000;
    *(int *)(self + 0x70) = 0x2000;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0x1000;
    *(int *)(self + 0x68) = 0;
    *(int *)(self + 0x6c) = 0;
    *(u16 *)(self + 0x100 + 0xae) |= 0x18;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(self, 0));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    func_0203ca14(*(int *)(self + 0x384) + 4, 0, -0x2000, 0);
    func_0202a388(self + 0x38c, *(int *)(*(int *)(self + 0x384) + 0x88), func_ov107_020c9440(self, 1), 0xc);
    func_0203b9ac(*(int *)(self + 0x384), self + 0x38c);
    *(Callback *)(*(int *)(self + 0x384) + 0x74) = func_ov213_020cbfc8;
    *(char **)(*(int *)(self + 0x384) + 0x84) = self;
    *(int *)(self + 0x3e8) = func_0203bee8(*(int *)(self + 0x384), 3, data_ov213_020d2fac);
    *(int *)(self + 0x3ec) = func_0203bee8(*(int *)(self + 0x384), 3, data_ov213_020d2fb4);
    *(int *)(self + 0x3f0) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov213_020d2fbc);
    *(int *)(self + 0x3f4) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov213_020d2fcc);
    *(int *)(self + 0x2cc) = *(int *)(self + 0x3e8) + 0x14;
    *(int *)(self + 0x388) = func_0203b898(func_ov107_020c9440(self, 0x1d));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x388));
    func_0203ca14(*(int *)(self + 0x388) + 4, 0, -0x2000, 0);
    func_0202a388(self + 0x3b0, *(int *)(*(int *)(self + 0x388) + 0x88), func_ov107_020c9440(self, 0x1e), 0xc);
    func_0203b9ac(*(int *)(self + 0x388), self + 0x3b0);
    *(int *)(self + 0x430) = func_0203d15c(0x40);
    for (i = 0; i < 8; i++) {
        ((struct Pair *)*(int *)(self + 0x430))[i].res = func_0203b898(func_ov107_020c9440(self, ids.id[i]));
        func_ov107_020c9074(self, ((struct Pair *)*(int *)(self + 0x430))[i].res);
        *(int *)(((struct Pair *)*(int *)(self + 0x430))[i].res + 0x5c) |= 2;
    }
    func_ov107_020c92b0(self, 2, 3, 0, 0x800);
    zero = data_02041dc8;
    place.pos = zero;
    place.scale = 0x2000;
    *(int *)(self + 0x3d4) = (int)func_01fffca8(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x3d4) = func_ov107_020c319c(&place);
    box.pos = zero;
    box.axis[0] = data_02042270;
    box.axis[1] = data_02042264;
    box.axis[2] = data_02042258;
    box.ext[0] = 0xd99;
    box.ext[1] = 0x1b33;
    box.ext[2] = 0xae0;
    slot = func_01fffca8(self + 0x144, 4, 100);
    *(int *)(self + 0x3d8) = *slot = func_ov107_020c32b8(&box);
    *(int *)(self + 0x3dc) = func_ov213_020d0574(self);
    *(int *)(self + 0x3e0) = func_0203d15c(0x20);
    for (i = 0; i < 8; i++) {
        (*(int **)(self + 0x3e0))[i] = func_ov213_020d1628(self);
    }
    *(int *)(self + 0x3e4) = func_0203d15c(0x20);
    for (i = 0; i < 8; i++) {
        (*(int **)(self + 0x3e4))[i] = func_ov213_020d238c(self);
    }
    func_0203355c(0x122);
}
