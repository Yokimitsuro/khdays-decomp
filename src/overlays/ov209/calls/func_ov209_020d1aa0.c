/* Constructor of the ov209 enemy (byte-identical to ov208's, x3 with ov268). Installs the handlers (+8, +0xc draw,
 * +0x1c message, +0x28, +0x2c, +0x30, +0x34 update, +0x1d0 hit filter, +0x1dc, +0x1e0), sets the
 * +0x1fc bounds box, the +0x64 pose (scale 2.36) and bit 3 of +0x1ae, builds the +0x384 rig from
 * pose 0 (+0x74 callback func_ov209_020d1a24, back-pointer at +0x84, subscribed to +0x9c,
 * 12-channel animation set 1 bound at +0x388, reset) and resolves five bones (+0x3d0/+0x3d4/+0x3d8
 * /+0x3dc in set 1, +0x3cc in set 3). Registers actions 0/2 (rate 1.05), 2/3 lowered 2.36
 * (0.49) and 1/2 (0.65); builds the five sub-items of data_ov209_020d65a4 into the +0x40c pair
 * table (the first from the shared scene resources, registered, bit 1 of +0x5c); keeps the
 * "move" handle of set 0x18 (+0x3ac); reserves the +0x22c and +0x144 collision handles (+0x3b4/
 * +0x3bc) from a zero capsule pointing up (radius 1.32, height 1.47), the +0x22c/+0x144 placements
 * +0x3b8 (0.76), +0x3c0 (1.0) and +0x3c4/+0x3c8 (1.43); spawns the item into +0x3b0 and loads
 * sound 0x154. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { int w[5]; } PoseTable;
typedef struct { Vec3 min; Vec3 max; } Bounds;
typedef struct { Vec3 pos; Vec3 up; int radius; int height; } Capsule;
typedef struct { Vec3 pos; int scale; } Placement;
struct Pair { int res; int handle; };

extern unsigned func_ov107_020c9440(char *self, int kind);
extern int func_0203b898(unsigned res);
extern void func_0203bfb4(int list, int obj);
extern void func_0202a388(void *set, int model, unsigned anim, int n);
extern void func_0203b9ac(int obj, void *set);
extern void func_0203c7ac(int obj, int v);
extern int func_0203bee8(int obj, int set, const char *name);
extern void func_ov107_020c92b0(char *self, int a, int b, Vec3 *lift, int rate);
extern void *func_0203d15c(int size);
extern char *OS_IsThreadAvailable_0x020c9848(void);
extern void func_ov107_020c9074(char *self, int obj);
extern int func_ov107_020c9e50(unsigned res, const char *name);
extern int *func_01fffca8(void *list, int stride, int max);
extern int func_ov107_020c3210(Capsule *capsule);
extern int func_ov107_020c319c(Placement *placement);
extern int func_ov209_020d5554(char *self);
extern void func_0203355c(int id);
extern const PoseTable data_ov209_020d65a4;
extern const char data_ov209_020d664c[];
extern const char data_ov209_020d6658[];
extern const char data_ov209_020d6668[];
extern const char data_ov209_020d6678[];
extern const char data_ov209_020d6680[];
extern const char data_ov209_020d6690[];
extern const Vec3 data_02041dc8;
extern const Vec3 data_02042264;
extern void func_ov209_020d1f58(void);
extern void func_ov209_020d1fa8(void);
extern void func_ov209_020d2208(void);
extern void func_ov209_020d293c(void);
extern void func_ov209_020d23bc(void);
extern void func_ov209_020d23e4(void);
extern void func_ov209_020d252c(void);
extern void func_ov209_020d2998(void);
extern void func_ov209_020d2c7c(void);
extern void func_ov209_020d24b4(void);
extern void func_ov209_020d1a24(void);

typedef void (*Callback)();
static inline void VEC_Set(Vec3 *v, int x, int y, int z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

void func_ov209_020d1aa0(char *self)
{
    PoseTable poses;
    Placement place;
    Capsule capsule;
    Bounds box;
    Vec3 lift;
    Vec3 zero;
    int i;
    int *p;
    int v;

    poses = data_ov209_020d65a4;
    box.min.x = -0x209e;
    box.min.y = -0x16;
    box.min.z = -0xb9b;
    box.max.x = box.min.x + 0x4117;
    box.max.y = box.min.y + 0x1eed;
    box.max.z = box.min.z + 0x1947;
    *(Callback *)(self + 0x8) = func_ov209_020d1f58;
    *(Callback *)(self + 0xc) = func_ov209_020d1fa8;
    *(Callback *)(self + 0x1c) = func_ov209_020d2208;
    *(Callback *)(self + 0x30) = func_ov209_020d293c;
    *(Callback *)(self + 0x28) = func_ov209_020d23bc;
    *(Callback *)(self + 0x2c) = func_ov209_020d23e4;
    *(Callback *)(self + 0x34) = func_ov209_020d252c;
    *(Callback *)(self + 0x1d0) = func_ov209_020d2998;
    *(Callback *)(self + 0x1e0) = func_ov209_020d2c7c;
    *(Callback *)(self + 0x1dc) = func_ov209_020d24b4;
    *(Bounds *)(self + 0x1fc) = box;
    *(int *)(self + 0x70) = 0x25b3;
    VEC_Set((Vec3 *)(self + 0x64), 0, *(int *)(self + 0x70), 0);
    *(u16 *)(self + 0x1ae) |= 8;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(self, 0));
    *(void **)(*(int *)(self + 0x384) + 0x74) = (void *)func_ov209_020d1a24;
    *(char **)(*(int *)(self + 0x384) + 0x84) = self;
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    func_0202a388(self + 0x388, *(int *)(*(int *)(self + 0x384) + 0x88), func_ov107_020c9440(self, 1), 0xc);
    func_0203b9ac(*(int *)(self + 0x384), self + 0x388);
    func_0203c7ac(*(int *)(self + 0x384), 0);
    *(int *)(self + 0x3d0) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov209_020d664c);
    *(int *)(self + 0x3d4) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov209_020d6658);
    *(int *)(self + 0x3d8) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov209_020d6668);
    *(int *)(self + 0x3cc) = func_0203bee8(*(int *)(self + 0x384), 3, data_ov209_020d6678);
    *(int *)(self + 0x3dc) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov209_020d6680);
    lift.x = 0;
    lift.y = -0x25b3;
    lift.z = 0;
    func_ov107_020c92b0(self, 0, 2, 0, 0x10da);
    func_ov107_020c92b0(self, 2, 3, &lift, 0x7c7);
    func_ov107_020c92b0(self, 1, 2, 0, 0xa5f);
    *(void **)(self + 0x40c) = func_0203d15c(0x28);
    for (i = 0; i < 5; i++) {
        if (i <= 0) {
            unsigned mask = 0xfffffc;
            (*(struct Pair **)(self + 0x40c))[i].res = func_0203b898(
                (((*(unsigned *)(OS_IsThreadAvailable_0x020c9848() + 0x88) + 0x8000) & mask) << 7 | 0x80000000)
                | (poses.w[i] & 0x1ff));
        } else {
            (*(struct Pair **)(self + 0x40c))[i].res = func_0203b898(func_ov107_020c9440(self, poses.w[i]));
        }
        func_ov107_020c9074(self, (*(struct Pair **)(self + 0x40c))[i].res);
        *(int *)((*(struct Pair **)(self + 0x40c))[i].res + 0x5c) |= 2;
    }
    *(int *)(self + 0x3ac) = func_ov107_020c9e50(func_ov107_020c9440(self, 0x18), data_ov209_020d6690);
    zero = data_02041dc8;
    capsule.pos = zero;
    capsule.up = data_02042264;
    capsule.radius = 0x1510;
    capsule.height = 0x1790;
    *(int **)(self + 0x3b4) = func_01fffca8(self + 0x22c, 0x10, 0x6e);
    **(int **)(self + 0x3b4) = func_ov107_020c3210(&capsule);
    p = func_01fffca8(self + 0x144, 4, 0x64);
    v = (*p = func_ov107_020c3210(&capsule));
    *(int *)(self + 0x3bc) = v;
    place.pos = zero;
    place.scale = 0xc27;
    *(int **)(self + 0x3b8) = func_01fffca8(self + 0x22c, 0x10, 0x64);
    **(int **)(self + 0x3b8) = func_ov107_020c319c(&place);
    place.scale = 0x1009;
    p = func_01fffca8(self + 0x144, 4, 0x64);
    v = (*p = func_ov107_020c319c(&place));
    *(int *)(self + 0x3c0) = v;
    place.pos = zero;
    place.scale = 0x16d8;
    p = func_01fffca8(self + 0x144, 4, 0x64);
    v = (*p = func_ov107_020c319c(&place));
    *(int *)(self + 0x3c4) = v;
    p = func_01fffca8(self + 0x144, 4, 0x64);
    v = (*p = func_ov107_020c319c(&place));
    *(int *)(self + 0x3c8) = v;
    *(int *)(self + 0x3b0) = func_ov209_020d5554(self);
    func_0203355c(0x154);
}
