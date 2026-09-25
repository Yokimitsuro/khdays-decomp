/* func_ov255_020cbfc4 = Ov255_EnemyConstruct. Constructor of the ov255 enemy (the ov235 constructor's
 * sibling): looks up its effect resource (+0x3f4), installs its handlers (+8 update, +0xc draw, +0x1c
 * message, +0x28, +0x2c, +0x30, +0x34, +0x1d0 hit filter, +0x1dc motion set), raises bit 3 of +0x1ae and
 * bit 5 of the +0x60 high byte and sets the +0x64 pose (scale 1.625). It builds two rigs with their
 * bindings -- body (+0x384/+0x388, poses 0, 1) and arms (+0x38c/+0x390, poses 0x24, 0x25) -- and
 * resolves the +0x3ac, +0x3a8, +0x3b0, +0x3b4 and +0x3b8 parts, the +0x3a4 motion part (pose 0x48),
 * four collision capsules (+0x394, +0x398, +0x39c and a long thin one at +0x3a0) and a +0x3e8
 * placement (hidden), then the twelve effect pairs of +0x3ec (the first nine from the effect
 * resource, the rest from the data_ov255_020d29d8 poses; all hidden), nine sub-objects (+0x3f0, each
 * told its index at +0x3bc) and loads the voice bank (+0x3f8: 0x17f in the alternate language,
 * else 0x17a). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef void (*Callback)(void);
typedef struct { int x, y, z; } Vec3;
typedef struct { int id[12]; } IdTable;
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
extern char *func_ov255_020d1848(char *owner);
extern IdTable data_ov255_020d29d8;
extern const char data_ov255_020d2bec[];
extern const char data_ov255_020d2bfc[];
extern const char data_ov255_020d2c08[];
extern const char data_ov255_020d2c14[];
extern const char data_ov255_020d2c18[];
extern const char data_ov255_020d2c24[];
extern const char data_ov255_020d2c28[];
extern const Vec3 data_02042270;
extern const Vec3 data_02042264;
extern const Vec3 data_02042258;
extern const Vec3 data_02041dc8;
extern u8 data_0204c240;
extern void func_ov255_020cc4f8(void);
extern void func_ov255_020cc570(void);
extern void func_ov255_020cc608(void);
extern void func_ov255_020ccbbc(void);
extern void func_ov255_020cc94c(void);
extern void func_ov255_020cc988(void);
extern void func_ov255_020cc9c4(void);
extern void func_ov255_020ccc08(void);
extern void func_ov255_020cca7c(void);

void func_ov255_020cbfc4(char *self)
{
    Capsule cap;
    Placement place;
    IdTable ids = data_ov255_020d29d8;
    Vec3 up;
    int i;
    int *slot;
    u16 hw;

    *(int *)(self + 0x3f4) = func_ov107_020c9c24(data_ov255_020d2bec);
    /* written three times: the dead copies are dropped after scheduling but spend its budget, which
     * keeps the ROM's order further down (as in Ov235_EnemyConstruct) */
    *(Callback *)(self + 0x8) = func_ov255_020cc4f8;
    *(Callback *)(self + 0x8) = func_ov255_020cc4f8;
    *(Callback *)(self + 0x8) = func_ov255_020cc4f8;
    *(Callback *)(self + 0xc) = func_ov255_020cc570;
    *(Callback *)(self + 0x1c) = func_ov255_020cc608;
    *(Callback *)(self + 0x30) = func_ov255_020ccbbc;
    *(Callback *)(self + 0x28) = func_ov255_020cc94c;
    *(Callback *)(self + 0x2c) = func_ov255_020cc988;
    *(Callback *)(self + 0x34) = func_ov255_020cc9c4;
    *(Callback *)(self + 0x1d0) = func_ov255_020ccc08;
    *(Callback *)(self + 0x1dc) = func_ov255_020cca7c;
    *(u16 *)(self + 0x100 + 0xae) |= 8;
    hw = *(u16 *)(self + 0x60);
    *(u16 *)(self + 0x60) = (hw & ~0xff00) |
        ((((((unsigned int)hw << 0x10) >> 0x18) | 0x20) << 0x18) >> 0x10);
    *(int *)(self + 0x70) = 0x1a00;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0x1a00;
    *(int *)(self + 0x6c) = 0;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(self, 0));
    *(char **)(self + 0x3ac) = func_0203bee8(*(int *)(self + 0x384), 3, data_ov255_020d2bfc);
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    *(void **)(self + 0x388) = func_0203d15c(0x24);
    func_0202a388(*(void **)(self + 0x388), *(int *)(*(int *)(self + 0x384) + 0x88), func_ov107_020c9440(self, 1), 0xc);
    func_0203b9ac(*(int *)(self + 0x384), *(void **)(self + 0x388));
    *(char **)(self + 0x3a8) = func_0203bee8(*(int *)(self + 0x384), 3, data_ov255_020d2c08);
    *(int *)(self + 0x38c) = func_0203b898(func_ov107_020c9440(self, 0x24));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x38c));
    *(void **)(self + 0x390) = func_0203d15c(0x24);
    func_0202a388(*(void **)(self + 0x390), *(int *)(*(int *)(self + 0x38c) + 0x88), func_ov107_020c9440(self, 0x25), 0xc);
    func_0203b9ac(*(int *)(self + 0x38c), *(void **)(self + 0x390));
    *(char **)(self + 0x3b0) = func_0203bee8(*(int *)(self + 0x38c), 3, data_ov255_020d2c14);
    *(char **)(self + 0x3b4) = func_0203bee8(*(int *)(self + 0x38c), 3, data_ov255_020d2c18);
    *(char **)(self + 0x3b8) = func_0203bee8(*(int *)(self + 0x38c), 3, data_ov255_020d2c24);
    *(void **)(self + 0x3a4) = func_ov107_020c9e50(func_ov107_020c9440(self, 0x48), data_ov255_020d2c28);
    cap.length = 0xa00;
    cap.radius = 0x1200;
    cap.pos.x = 0;
    cap.pos.y = 0;
    cap.pos.z = 0;
    up = data_02042270;
    cap.axis = up;
    *(int **)(self + 0x394) = func_01fffca8(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x394) = func_ov107_020c3210(&cap);
    cap.length = 0xa00;
    cap.radius = 0x1200;
    cap.pos.x = 0;
    cap.pos.y = 0;
    cap.pos.z = 0;
    cap.axis = up;
    slot = func_01fffca8(self + 0x144, 4, 100);
    *(int *)(self + 0x398) = *slot = func_ov107_020c3210(&cap);
    cap.length = 0xa00;
    cap.radius = 0x1200;
    cap.pos.x = 0;
    cap.pos.y = 0x1200;
    cap.pos.z = 0;
    cap.axis = data_02042264;
    slot = func_01fffca8(self + 0x144, 4, 100);
    *(int *)(self + 0x39c) = *slot = func_ov107_020c3210(&cap);
    cap.length = 0x3000;
    cap.radius = 0x800;
    cap.pos.x = 0;
    cap.pos.y = 0;
    cap.pos.z = 0;
    cap.axis = data_02042258;
    slot = func_01fffca8(self + 0x144, 4, 100);
    *(int *)(self + 0x3a0) = *slot = func_ov107_020c3210(&cap);
    place.pos = data_02041dc8;
    place.scale = 0x1000;
    slot = func_01fffca8(self + 0x144, 4, 100);
    *(int *)(self + 0x3e8) = *slot = func_ov107_020c319c(&place);
    ((struct Nib *)*(int *)(self + 0x3e8))->hi &= ~1;
    *(struct Pair **)(self + 0x3ec) = func_0203d15c(0x60);
    for (i = 0; i < 9; i++) {
        (*(struct Pair **)(self + 0x3ec))[i].res = func_0203b898((void *)((((*(int *)(self + 0x3f4) + 0x8000) & 0xfffffc) << 7 | 0x80000000)
            | (i & 0x1ff)));
        func_ov107_020c9074(self, (*(struct Pair **)(self + 0x3ec))[i].res);
        *(int *)((*(struct Pair **)(self + 0x3ec))[i].res + 0x5c) |= 2;
    }
    for (; i < 12; i++) {
        (*(struct Pair **)(self + 0x3ec))[i].res = func_0203b898(func_ov107_020c9440(self, ids.id[i]));
        func_ov107_020c9074(self, (*(struct Pair **)(self + 0x3ec))[i].res);
        *(int *)((*(struct Pair **)(self + 0x3ec))[i].res + 0x5c) |= 2;
    }
    *(char ***)(self + 0x3f0) = func_0203d15c(0x1fa4);
    for (i = 0; i < 9; i++) {
        (*(char ***)(self + 0x3f0))[i] = func_ov255_020d1848(self);
        *(int *)((*(char ***)(self + 0x3f0))[i] + 0x3bc) = i;
    }
    *(int *)(self + 0x3f8) = (data_0204c240 & 4) ? 0x17f : 0x17a;
    func_0203355c(*(int *)(self + 0x3f8));
}
