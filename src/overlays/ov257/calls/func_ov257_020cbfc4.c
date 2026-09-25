/* func_ov257_020cbfc4 = Ov257_EnemyConstruct. Constructor of the ov257 enemy (sibling of the ov235 and
 * ov255 constructors): looks up its effect resource (+0x404), installs its handlers (+8 update, +0xc
 * draw, +0x10, +0x1c message, +0x28, +0x2c, +0x30, +0x34, +0x1d0 hit filter, +0x1dc motion set),
 * raises bit 3 of +0x1ae and bit 5 of the +0x60 high byte and sets the +0x64 pose (scale 2.0). It
 * builds two rigs with their bindings -- body (+0x384/+0x388, poses 0, 1) and arms (+0x38c/+0x390,
 * poses 0x23, 0x24) -- resolves the +0x3d8 and +0x3d4 body parts and, on the arms rig, the four
 * +0x3dc (kind 1) and +0x3ec (kind 3) parts named by data_ov257_020d3074/020d3084; subscribes the
 * four +0x394 items of the data_ov257_020d3064 poses and attaches four +0x3a4 pose-0x4b items (all
 * hidden, +0x3a4 ones flagged), keeps the +0x3d0 motion part (pose 0x46), three collision capsules
 * (+0x3b4, +0x3b8, +0x3bc) plus four thin ones (+0x3c0..+0x3cc) and a +0x3fc placement (hidden), then
 * the twelve effect pairs of +0x400 (nine from the effect resource, three from the
 * data_ov257_020d3094 poses) and loads the voice bank (+0x408: 0x17f in the alternate language,
 * else 0x17a). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef void (*Callback)(void);
typedef struct { int x, y, z; } Vec3;
typedef struct { int id[12]; } IdTable;
typedef struct { int id[4]; } IdTable4;
typedef struct { void *name[4]; } NameTable4;
typedef struct { Vec3 pos; int scale; } Placement;
typedef struct { Vec3 pos; Vec3 axis; int length; int radius; } Capsule;
struct Pair { int res; int handle; };
struct Nib { u8 lo : 4, hi : 4; };
struct Bit0 { unsigned bit0 : 1; };

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
extern IdTable4 data_ov257_020d3064;
extern NameTable4 data_ov257_020d3074;
extern NameTable4 data_ov257_020d3084;
extern IdTable data_ov257_020d3094;
extern const char data_ov257_020d33cc[];
extern const char data_ov257_020d33dc[];
extern const char data_ov257_020d33e0[];
extern const char data_ov257_020d33ec[];
extern const Vec3 data_02042270;
extern const Vec3 data_02042264;
extern const Vec3 data_02042258;
extern const Vec3 data_02041dc8;
extern u8 data_0204c240;
extern void func_ov257_020cc5d0(void);
extern void func_ov257_020cc678(void);
extern void func_ov257_020cc6b0(void);
extern void func_ov257_020cc6fc(void);
extern void func_ov257_020ccd9c(void);
/* ov257 handlers 020cca20 / 020cca2c; the symbol table names them after an SDK routine */
extern void WM_EndKeySharing_0x020cca20(void);
extern void WM_EndKeySharing_0x020cca2c(void);
extern void func_ov257_020cca38(void);
extern void func_ov257_020ccde8(void);
extern void func_ov257_020ccbac(void);

void func_ov257_020cbfc4(char *self)
{
    Capsule cap;
    Placement place;
    IdTable ids = data_ov257_020d3094;
    IdTable4 armIds = data_ov257_020d3064;
    NameTable4 names1;
    NameTable4 names3;
    Vec3 up;
    int i;
    int *slot;
    u16 hw;

    *(int *)(self + 0x404) = func_ov107_020c9c24(data_ov257_020d33cc);
    /* written three times: the dead copies are dropped after scheduling but spend its budget, which
     * keeps the ROM's order further down (as in Ov255_EnemyConstruct) */
    *(Callback *)(self + 0x8) = func_ov257_020cc5d0;
    *(Callback *)(self + 0x8) = func_ov257_020cc5d0;
    *(Callback *)(self + 0x8) = func_ov257_020cc5d0;
    *(Callback *)(self + 0xc) = func_ov257_020cc678;
    *(Callback *)(self + 0x10) = func_ov257_020cc6b0;
    *(Callback *)(self + 0x1c) = func_ov257_020cc6fc;
    *(Callback *)(self + 0x30) = func_ov257_020ccd9c;
    *(Callback *)(self + 0x28) = WM_EndKeySharing_0x020cca20;
    *(Callback *)(self + 0x2c) = WM_EndKeySharing_0x020cca2c;
    *(Callback *)(self + 0x34) = func_ov257_020cca38;
    *(Callback *)(self + 0x1d0) = func_ov257_020ccde8;
    *(Callback *)(self + 0x1dc) = func_ov257_020ccbac;
    *(u16 *)(self + 0x100 + 0xae) |= 8;
    hw = *(u16 *)(self + 0x60);
    *(u16 *)(self + 0x60) = (hw & ~0xff00) |
        ((((((unsigned int)hw << 0x10) >> 0x18) | 0x20) << 0x18) >> 0x10);
    *(int *)(self + 0x70) = 0x2000;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0x2000;
    *(int *)(self + 0x6c) = 0;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(self, 0));
    *(char **)(self + 0x3d8) = func_0203bee8(*(int *)(self + 0x384), 3, data_ov257_020d33dc);
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    *(void **)(self + 0x388) = func_0203d15c(0x24);
    func_0202a388(*(void **)(self + 0x388), *(int *)(*(int *)(self + 0x384) + 0x88), func_ov107_020c9440(self, 1), 0xc);
    func_0203b9ac(*(int *)(self + 0x384), *(void **)(self + 0x388));
    *(char **)(self + 0x3d4) = func_0203bee8(*(int *)(self + 0x384), 3, data_ov257_020d33e0);
    *(int *)(self + 0x38c) = func_0203b898(func_ov107_020c9440(self, 0x23));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x38c));
    *(void **)(self + 0x390) = func_0203d15c(0x24);
    func_0202a388(*(void **)(self + 0x390), *(int *)(*(int *)(self + 0x38c) + 0x88), func_ov107_020c9440(self, 0x24), 0xc);
    func_0203b9ac(*(int *)(self + 0x38c), *(void **)(self + 0x390));
    names1 = data_ov257_020d3074;
    names3 = data_ov257_020d3084;
    for (i = 0; i < 4; i++) {
        ((char **)(self + 0x3dc))[i] = func_0203bee8(*(int *)(self + 0x38c), 1, names1.name[i]);
        ((char **)(self + 0x3ec))[i] = func_0203bee8(*(int *)(self + 0x38c), 3, names3.name[i]);
    }
    for (i = 0; i < 4; i++) {
        ((int *)(self + 0x394))[i] = func_0203b898(func_ov107_020c9440(self, armIds.id[i]));
        func_0203bfb4(*(int *)(self + 0x9c), ((int *)(self + 0x394))[i]);
        *(int *)(((int *)(self + 0x394))[i] + 0x5c) |= 2;
    }
    for (i = 0; i < 4; i++) {
        ((int *)(self + 0x3a4))[i] = func_0203b898(func_ov107_020c9440(self, 0x4b));
        func_ov107_020c9074(self, ((int *)(self + 0x3a4))[i]);
        *(int *)(((int *)(self + 0x3a4))[i] + 0x5c) |= 2;
        ((struct Bit0 *)(((int *)(self + 0x3a4))[i] + 0x5c))->bit0 = 1;
    }
    *(void **)(self + 0x3d0) = func_ov107_020c9e50(func_ov107_020c9440(self, 0x46), data_ov257_020d33ec);
    cap.length = 0xa00;
    cap.radius = 0x1200;
    cap.pos.x = 0;
    cap.pos.y = 0;
    cap.pos.z = 0;
    up = data_02042270;
    cap.axis = up;
    *(int **)(self + 0x3b4) = func_01fffca8(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x3b4) = func_ov107_020c3210(&cap);
    cap.length = 0xa00;
    cap.radius = 0x1600;
    cap.pos.x = 0;
    cap.pos.y = 0;
    cap.pos.z = 0;
    cap.axis = up;
    slot = func_01fffca8(self + 0x144, 4, 100);
    *(int *)(self + 0x3b8) = *slot = func_ov107_020c3210(&cap);
    cap.length = 0xa00;
    cap.radius = 0x1600;
    cap.pos.x = 0;
    cap.pos.y = 0x1600;
    cap.pos.z = 0;
    cap.axis = data_02042264;
    slot = func_01fffca8(self + 0x144, 4, 100);
    *(int *)(self + 0x3bc) = *slot = func_ov107_020c3210(&cap);
    cap.length = 0x2c00;
    cap.radius = 0x600;
    cap.pos.x = 0;
    cap.pos.y = 0;
    cap.pos.z = 0;
    cap.axis = data_02042258;
    for (i = 0; i < 4; i++) {
        slot = func_01fffca8(self + 0x144, 4, 100);
        ((int *)(self + 0x3c0))[i] = *slot = func_ov107_020c3210(&cap);
    }
    place.pos = data_02041dc8;
    place.scale = 0x1000;
    slot = func_01fffca8(self + 0x144, 4, 100);
    *(int *)(self + 0x3fc) = *slot = func_ov107_020c319c(&place);
    ((struct Nib *)*(int *)(self + 0x3fc))->hi &= ~1;
    *(struct Pair **)(self + 0x400) = func_0203d15c(0x60);
    for (i = 0; i < 9; i++) {
        (*(struct Pair **)(self + 0x400))[i].res = func_0203b898((void *)((((*(int *)(self + 0x404) + 0x8000) & 0xfffffc) << 7 | 0x80000000)
            | (i & 0x1ff)));
        func_ov107_020c9074(self, (*(struct Pair **)(self + 0x400))[i].res);
        *(int *)((*(struct Pair **)(self + 0x400))[i].res + 0x5c) |= 2;
    }
    for (; i < 12; i++) {
        (*(struct Pair **)(self + 0x400))[i].res = func_0203b898(func_ov107_020c9440(self, ids.id[i]));
        func_ov107_020c9074(self, (*(struct Pair **)(self + 0x400))[i].res);
        *(int *)((*(struct Pair **)(self + 0x400))[i].res + 0x5c) |= 2;
    }
    *(int *)(self + 0x408) = (data_0204c240 & 4) ? 0x17f : 0x17a;
    func_0203355c(*(int *)(self + 0x408));
}
