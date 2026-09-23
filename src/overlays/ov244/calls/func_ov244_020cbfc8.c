/* Constructor of the ov244 enemy (x2 with ov277). Installs the handlers (+8, +0xc, +0x1c message,
 * +0x28, +0x2c, +0x30, +0x34 update, +0x38, +0x1d0 hit filter, +0x1d4, +0x1d8, +0x1dc, +0x1ec),
 * sets kind 2, bits 2, 5 and 7 of the +0x60 high byte, the +0x64 pose (scale 4.0) and bits 3-4 of
 * +0x1ae; builds the +0x384 body rig (pose 0, subscribed to +0x9c) with its +0x390 work list
 * (pose 2) and fourteen bone attachments (+0x3a8..+0x3dc), and the +0x388 / +0x38c arm rigs (poses
 * 0xd / 0x1a, flagged, lists 0xf / 0x1c at +0x394 / +0x398); the eight hidden sub-items of
 * data_ov244_020d3638 go into the +0x40c pair table, the +0x424 list gets two 020d15ac entries
 * (+0x400), six parts (020cd438, +0x404) and four part controllers (020d0ca4, +0x408) are created.
 * Shapes: six capsules (length 1.0, radius 1.5, along z) at +0x3e0..+0x3f4 and two along y
 * (radius 3.0 / 2.0) at +0x3f8 / +0x3fc on the +0x144 pool; on the +0x22c pool a placement
 * (scale 2.0) at +0x39c and two capsules (radius 1.625, along x) at +0x3a0 / +0x3a4. Loads sound
 * 0x113. */
typedef unsigned short u16;
typedef void (*Callback)(void);
typedef struct { int x, y, z; } Vec3;
typedef struct { int id[8]; } IdTable8;
typedef struct { Vec3 pos; int scale; } Placement;
typedef struct { Vec3 pos; Vec3 axis; int length; int radius; } Capsule;
struct Pair { int res; int handle; };
struct b1 { unsigned int b0 : 1; };

extern void func_ov244_020cc6fc(void);
extern void func_ov244_020cc794(void);
extern void func_ov244_020cc8a4(void);
extern void func_ov244_020ccbc4(void);
extern void func_ov244_020ccc70(void);
extern void func_ov244_020cf700(void);
extern void func_ov244_020cccec(void);
extern void func_ov244_020cd130(void);
extern void func_ov244_020cf74c(void);
extern void func_ov244_020cd178(void);
extern void func_ov244_020cc7b0(void);
extern void WM_EndKeySharing_0x020cd20c(void);
extern void func_ov244_020cd218(void);
extern void *func_ov107_020c9440(char *self, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern int func_0203d15c(int size);
extern void func_0202a388(int a, int b, void *c, int d);
extern void func_0203b9ac(int a, int b);
extern int func_0203bee8(int item, int kind, void *name);
extern void func_ov107_020c9074(char *self, int item);
extern void func_ov107_020c2f94(int a, void *list);
extern int func_ov244_020d15ac(void *list);
extern int func_ov244_020cd438(char *self);
extern int func_ov244_020d0ca4(char *self);
extern int *func_01fffca8(void *pool, int elementSize, int capacity);
extern int func_ov107_020c3210(const Capsule *capsule);
extern int func_ov107_020c319c(const Placement *placement);
extern void func_0203355c(int resourceId);
extern IdTable8 data_ov244_020d3638;
extern char data_ov244_020d37cc[];
extern char data_ov244_020d37dc[];
extern char data_ov244_020d37e8[];
extern char data_ov244_020d37f4[];
extern char data_ov244_020d3804[];
extern char data_ov244_020d380c[];
extern char data_ov244_020d3818[];
extern char data_ov244_020d382c[];
extern char data_ov244_020d383c[];
extern char data_ov244_020d384c[];
extern char data_ov244_020d385c[];
extern char data_ov244_020d3870[];
extern char data_ov244_020d3880[];
extern char data_ov244_020d3890[];
extern const Vec3 data_02041dc8;
extern const Vec3 data_02042270;
extern const Vec3 data_02042264;
extern const Vec3 data_0204227c;

void func_ov244_020cbfc8(char *self)
{
    IdTable8 ids = data_ov244_020d3638;
    Capsule cap;
    Placement place;
    Vec3 zero;
    Vec3 axisX;
    u16 hw;
    int i;
    int *slot;

    *(Callback *)(self + 0x8) = func_ov244_020cc6fc;
    *(Callback *)(self + 0xc) = func_ov244_020cc794;
    *(Callback *)(self + 0x1c) = func_ov244_020cc8a4;
    *(Callback *)(self + 0x28) = func_ov244_020ccbc4;
    *(Callback *)(self + 0x2c) = func_ov244_020ccc70;
    *(Callback *)(self + 0x30) = func_ov244_020cf700;
    *(Callback *)(self + 0x34) = func_ov244_020cccec;
    *(Callback *)(self + 0x38) = func_ov244_020cd130;
    *(Callback *)(self + 0x1d0) = func_ov244_020cf74c;
    *(Callback *)(self + 0x1d8) = func_ov244_020cd178;
    *(Callback *)(self + 0x1dc) = func_ov244_020cc7b0;
    *(Callback *)(self + 0x1d4) = WM_EndKeySharing_0x020cd20c;
    *(Callback *)(self + 0x1ec) = func_ov244_020cd218;
    *(unsigned char *)(self + 0x1c9) = 2;
    hw = *(u16 *)(self + 0x60);
    *(u16 *)(self + 0x60) = (hw & ~0xff00) |
        ((((((unsigned int)hw << 0x10) >> 0x18) | 0xa4) << 0x18) >> 0x10);
    /* default scale first: the overwritten store is dropped after scheduling but spends the
     * block's scheduling budget (keeps the ROM's argument order of the attachment calls) */
    *(int *)(self + 0x70) = 0x1000;
    *(int *)(self + 0x70) = 0x4000;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0x4000;
    *(int *)(self + 0x6c) = 0;
    *(u16 *)(self + 0x100 + 0xae) |= 0x18;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(self, 0));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    *(int *)(self + 0x390) = func_0203d15c(0x24);
    func_0202a388(*(int *)(self + 0x390), *(int *)(*(int *)(self + 0x384) + 0x88), func_ov107_020c9440(self, 2), 0xc);
    func_0203b9ac(*(int *)(self + 0x384), *(int *)(self + 0x390));
    *(int *)(self + 0x3a8) = func_0203bee8(*(int *)(self + 0x384), 3, data_ov244_020d37cc);
    *(int *)(self + 0x3ac) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov244_020d37dc);
    *(int *)(self + 0x3b0) = func_0203bee8(*(int *)(self + 0x384), 3, data_ov244_020d37e8);
    *(int *)(self + 0x3b4) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov244_020d37f4);
    *(int *)(self + 0x3b8) = func_0203bee8(*(int *)(self + 0x384), 3, data_ov244_020d3804);
    *(int *)(self + 0x3bc) = func_0203bee8(*(int *)(self + 0x384), 3, data_ov244_020d380c);
    *(int *)(self + 0x3c0) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov244_020d3818);
    *(int *)(self + 0x3c4) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov244_020d382c);
    *(int *)(self + 0x3c8) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov244_020d383c);
    *(int *)(self + 0x3cc) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov244_020d384c);
    *(int *)(self + 0x3d0) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov244_020d385c);
    *(int *)(self + 0x3d4) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov244_020d3870);
    *(int *)(self + 0x3d8) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov244_020d3880);
    *(int *)(self + 0x3dc) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov244_020d3890);
    *(int *)(self + 0x388) = func_0203b898(func_ov107_020c9440(self, 0xd));
    ((struct b1 *)(*(int *)(self + 0x388) + 0x5c))->b0 = 1;
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x388));
    *(int *)(self + 0x394) = func_0203d15c(0x24);
    func_0202a388(*(int *)(self + 0x394), *(int *)(*(int *)(self + 0x388) + 0x88), func_ov107_020c9440(self, 0xf), 0xc);
    func_0203b9ac(*(int *)(self + 0x388), *(int *)(self + 0x394));
    *(int *)(self + 0x38c) = func_0203b898(func_ov107_020c9440(self, 0x1a));
    ((struct b1 *)(*(int *)(self + 0x38c) + 0x5c))->b0 = 1;
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x38c));
    *(int *)(self + 0x398) = func_0203d15c(0x24);
    func_0202a388(*(int *)(self + 0x398), *(int *)(*(int *)(self + 0x38c) + 0x88), func_ov107_020c9440(self, 0x1c), 0xc);
    func_0203b9ac(*(int *)(self + 0x38c), *(int *)(self + 0x398));
    *(int *)(self + 0x40c) = func_0203d15c(0x40);
    for (i = 0; i < 8; i++) {
        ((struct Pair *)*(int *)(self + 0x40c))[i].res = func_0203b898(func_ov107_020c9440(self, ids.id[i]));
        func_ov107_020c9074(self, ((struct Pair *)*(int *)(self + 0x40c))[i].res);
        *(int *)(((struct Pair *)*(int *)(self + 0x40c))[i].res + 0x5c) |= 2;
    }
    func_ov107_020c2f94(0, self + 0x424);
    *(int *)(self + 0x400) = func_0203d15c(8);
    for (i = 0; i < 2; i++) {
        (*(int **)(self + 0x400))[i] = func_ov244_020d15ac(self + 0x424);
    }
    *(int *)(self + 0x404) = func_0203d15c(0x18);
    for (i = 0; i < 6; i++) {
        (*(int **)(self + 0x404))[i] = func_ov244_020cd438(self);
    }
    *(int *)(self + 0x408) = func_0203d15c(0x10);
    for (i = 0; i < 4; i++) {
        (*(int **)(self + 0x408))[i] = func_ov244_020d0ca4(self);
    }
    zero = data_02041dc8;
    cap.pos = zero;
    cap.axis = data_02042270;
    cap.length = 0x1000;
    cap.radius = 0x1800;
    slot = func_01fffca8(self + 0x144, 4, 100);
    *(int *)(self + 0x3e0) = *slot = func_ov107_020c3210(&cap);
    slot = func_01fffca8(self + 0x144, 4, 100);
    *(int *)(self + 0x3e4) = *slot = func_ov107_020c3210(&cap);
    slot = func_01fffca8(self + 0x144, 4, 100);
    *(int *)(self + 0x3e8) = *slot = func_ov107_020c3210(&cap);
    slot = func_01fffca8(self + 0x144, 4, 100);
    *(int *)(self + 0x3ec) = *slot = func_ov107_020c3210(&cap);
    slot = func_01fffca8(self + 0x144, 4, 100);
    *(int *)(self + 0x3f0) = *slot = func_ov107_020c3210(&cap);
    slot = func_01fffca8(self + 0x144, 4, 100);
    *(int *)(self + 0x3f4) = *slot = func_ov107_020c3210(&cap);
    cap.pos = zero;
    cap.axis = data_02042264;
    cap.length = 0x1000;
    cap.radius = 0x3000;
    slot = func_01fffca8(self + 0x144, 4, 100);
    *(int *)(self + 0x3f8) = *slot = func_ov107_020c3210(&cap);
    cap.radius = 0x2000;
    slot = func_01fffca8(self + 0x144, 4, 100);
    *(int *)(self + 0x3fc) = *slot = func_ov107_020c3210(&cap);
    place.pos = zero;
    place.scale = 0x2000;
    *(int *)(self + 0x39c) = (int)func_01fffca8(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x39c) = func_ov107_020c319c(&place);
    cap.pos = zero;
    axisX = data_0204227c;
    cap.axis = axisX;
    cap.length = 0x1000;
    cap.radius = 0x1a00;
    *(int *)(self + 0x3a0) = (int)func_01fffca8(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x3a0) = func_ov107_020c3210(&cap);
    cap.pos = zero;
    cap.axis = axisX;
    cap.length = 0x1000;
    cap.radius = 0x1a00;
    *(int *)(self + 0x3a4) = (int)func_01fffca8(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x3a4) = func_ov107_020c3210(&cap);
    func_0203355c(0x113);
}
