/* func_ov235_020cbfc4 = Ov235_EnemyConstruct. Constructor of the ov235 enemy: looks up its effect resource (+0x3c0), installs its handlers
 * (+8 update, +0xc draw, +0x1c message, +0x28, +0x2c, +0x30, +0x34, +0x1d0 hit filter, +0x1dc
 * motion set), raises bit 3 of +0x1ae and bit 5 of the +0x60 high byte and sets the +0x64 pose
 * (scale 1.5). It builds three rigs with their bindings -- body (+0x384/+0x388, pose 0, 1),
 * head (+0x394/+0x398, poses 0x50, 0x51) and wings (+0x38c/+0x390, poses 0x28, 0x29) -- and
 * resolves the +0x3b0, +0x3ac and +0x3b4 parts, the +0x3a8 motion part (pose 0x78), three
 * collision capsules (+0x39c, +0x3a0, +0x3a4; radius 1.125, length 0.625) and a +0x3b8 placement
 * (hidden), then the eleven effect pairs of +0x3bc (the first eight from the effect resource, the
 * rest from the data_ov235_020d22d0 poses; all hidden) and loads the voice bank (+0x3c8: 0x17f
 * in the alternate language, else 0x17a). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef void (*Callback)(void);
typedef struct { int x, y, z; } Vec3;
typedef struct { int id[11]; } IdTable;
typedef struct { Vec3 pos; int scale; } Placement;
typedef struct { Vec3 pos; Vec3 axis; int length; int radius; } Capsule;
struct Pair { int res; int handle; };
struct Nib { u8 lo : 4, hi : 4; };

extern int func_ov107_020c9c24(const char *name);
extern void *func_ov107_020c9440(char *self, int index);
extern int func_0203b898(void *res);
extern char *func_0203bee8(int rig, int kind, const char *name);
extern void func_0203bfb4(int subscriber, int item);
extern void *func_0203d15c(int size);
extern void func_0202a388(void *binding, int model, void *res, int count);
extern void func_0203b9ac(int rig, void *binding);
extern void *func_ov107_020c9e50(void *res, const char *name);
extern int *func_01fffca8(void *pool, int elementSize, int capacity);
extern int func_ov107_020c3210(const Capsule *capsule);
extern int func_ov107_020c319c(const Placement *placement);
extern void func_ov107_020c9074(char *self, int item);
extern void func_0203355c(int resourceId);
extern IdTable data_ov235_020d22d0;
extern const char data_ov235_020d258c[];
extern const char data_ov235_020d259c[];
extern const char data_ov235_020d25a8[];
extern const char data_ov235_020d25b4[];
extern const char data_ov235_020d25c0[];
extern const Vec3 data_02042270;
extern const Vec3 data_02042264;
extern const Vec3 data_02041dc8;
extern u8 data_0204c240;
extern void func_ov235_020cc494(void);
extern void func_ov235_020cc51c(void);
extern void func_ov235_020cc554(void);
extern void func_ov235_020ccb3c(void);
/* ov235 handlers 020cc8a0 / 020cc8ac; the symbol table names them after an SDK routine */
extern void WM_EndKeySharing_0x020cc8a0(void);
extern void WM_EndKeySharing_0x020cc8ac(void);
extern void func_ov235_020cc8b8(void);
extern void func_ov235_020ccb88(void);
extern void func_ov235_020cc9a0(void);

void func_ov235_020cbfc4(char *self)
{
    Capsule cap;
    Placement place;
    IdTable ids = data_ov235_020d22d0;
    Vec3 up;
    int i;
    int *slot;
    u16 hw;

    *(int *)(self + 0x3c0) = func_ov107_020c9c24(data_ov235_020d258c);
    /* The first handler is stored five times (two statements and a triple chained assignment): the
     * dead copies are dropped after scheduling but spend its budget, which keeps the ROM's order
     * further down (as in Ov261_EnemyConstruct). */
    *(Callback *)(self + 0x8) = func_ov235_020cc494;
    *(Callback *)(self + 0x8) = func_ov235_020cc494;
    *(Callback *)(self + 0x8) = *(Callback *)(self + 0x8) = *(Callback *)(self + 0x8) = func_ov235_020cc494;
    *(Callback *)(self + 0xc) = func_ov235_020cc51c;
    *(Callback *)(self + 0x1c) = func_ov235_020cc554;
    *(Callback *)(self + 0x30) = func_ov235_020ccb3c;
    *(Callback *)(self + 0x28) = WM_EndKeySharing_0x020cc8a0;
    *(Callback *)(self + 0x2c) = WM_EndKeySharing_0x020cc8ac;
    *(Callback *)(self + 0x34) = func_ov235_020cc8b8;
    *(Callback *)(self + 0x1d0) = func_ov235_020ccb88;
    *(Callback *)(self + 0x1dc) = func_ov235_020cc9a0;
    *(u16 *)(self + 0x100 + 0xae) |= 8;
    hw = *(u16 *)(self + 0x60);
    *(u16 *)(self + 0x60) = (hw & ~0xff00) |
        ((((((unsigned int)hw << 0x10) >> 0x18) | 0x20) << 0x18) >> 0x10);
    *(int *)(self + 0x70) = 0x1800;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0x1800;
    *(int *)(self + 0x6c) = 0;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(self, 0));
    *(char **)(self + 0x3b0) = func_0203bee8(*(int *)(self + 0x384), 3, data_ov235_020d259c);
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    *(void **)(self + 0x388) = func_0203d15c(0x24);
    func_0202a388(*(void **)(self + 0x388), *(int *)(*(int *)(self + 0x384) + 0x88), func_ov107_020c9440(self, 1), 0xc);
    slot = (int *)(self + 0x9c);    /* the owner, through the same slot local as the placements below */
    func_0203b9ac(*(int *)(self + 0x384), *(void **)(self + 0x388));
    *(char **)(self + 0x3ac) = func_0203bee8(*(int *)(self + 0x384), 3, data_ov235_020d25a8);
    *(int *)(self + 0x394) = func_0203b898(func_ov107_020c9440(self, 0x50));
    func_0203bfb4(*slot, *(int *)(self + 0x394));
    *(void **)(self + 0x398) = func_0203d15c(0x24);
    func_0202a388(*(void **)(self + 0x398), *(int *)(*(int *)(self + 0x394) + 0x88), func_ov107_020c9440(self, 0x51), 0xc);
    func_0203b9ac(*(int *)(self + 0x394), *(void **)(self + 0x398));
    *(char **)(self + 0x3b4) = func_0203bee8(*(int *)(self + 0x394), 3, data_ov235_020d25b4);
    *(int *)(self + 0x38c) = func_0203b898(func_ov107_020c9440(self, 0x28));
    func_0203bfb4(*slot, *(int *)(self + 0x38c));
    *(void **)(self + 0x390) = func_0203d15c(0x24);
    func_0202a388(*(void **)(self + 0x390), *(int *)(*(int *)(self + 0x38c) + 0x88), func_ov107_020c9440(self, 0x29), 0xc);
    func_0203b9ac(*(int *)(self + 0x38c), *(void **)(self + 0x390));
    *(void **)(self + 0x3a8) = func_ov107_020c9e50(func_ov107_020c9440(self, 0x78), data_ov235_020d25c0);
    cap.length = 0xa00;
    cap.radius = 0x1200;
    cap.pos.x = 0;
    cap.pos.y = 0;
    cap.pos.z = 0;
    up = data_02042270;
    cap.axis = up;
    *(int **)(self + 0x39c) = func_01fffca8(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x39c) = func_ov107_020c3210(&cap);
    cap.length = 0xa00;
    cap.radius = 0x1200;
    cap.pos.x = 0;
    cap.pos.y = 0;
    cap.pos.z = 0;
    cap.axis = up;
    slot = func_01fffca8(self + 0x144, 4, 100);
    *(int *)(self + 0x3a0) = *slot = func_ov107_020c3210(&cap);
    cap.length = 0xa00;
    cap.radius = 0x1200;
    cap.pos.x = 0;
    cap.pos.y = 0x1200;
    cap.pos.z = 0;
    cap.axis = data_02042264;
    slot = func_01fffca8(self + 0x144, 4, 100);
    *(int *)(self + 0x3a4) = *slot = func_ov107_020c3210(&cap);
    place.pos = data_02041dc8;
    place.scale = 0x1000;
    slot = func_01fffca8(self + 0x144, 4, 100);
    *(int *)(self + 0x3b8) = *slot = func_ov107_020c319c(&place);
    ((struct Nib *)*(int *)(self + 0x3b8))->hi &= ~1;
    *(struct Pair **)(self + 0x3bc) = func_0203d15c(0x58);
    for (i = 0; i < 8; i++) {
        (*(struct Pair **)(self + 0x3bc))[i].res = func_0203b898((void *)((((*(int *)(self + 0x3c0) + 0x8000) & 0xfffffc) << 7 | 0x80000000)
            | (i & 0x1ff)));
        func_ov107_020c9074(self, (*(struct Pair **)(self + 0x3bc))[i].res);
        *(int *)((*(struct Pair **)(self + 0x3bc))[i].res + 0x5c) |= 2;
    }
    for (; i < 11; i++) {
        (*(struct Pair **)(self + 0x3bc))[i].res = func_0203b898(func_ov107_020c9440(self, ids.id[i]));
        func_ov107_020c9074(self, (*(struct Pair **)(self + 0x3bc))[i].res);
        *(int *)((*(struct Pair **)(self + 0x3bc))[i].res + 0x5c) |= 2;
    }
    *(int *)(self + 0x3c8) = (data_0204c240 & 4) ? 0x17f : 0x17a;
    func_0203355c(*(int *)(self + 0x3c8));
}
