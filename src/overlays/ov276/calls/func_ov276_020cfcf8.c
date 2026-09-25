/* Constructor of the ov276 enemy: installs the handlers (+8 teardown, +0xc draw, +0x1c message,
 * +0x30 registry entry, +0x28/+0x2c veneers, +0x34 tick, +0x1d0 hit, +0x1dc/+0x1e0/+0x1e4
 * callbacks), seeds the +0x1fc bounding box, the +0x64 pose (scale 0x10cc, y 0x10cc) and bit 3
 * of +0x1ae; builds the primary item from pool entry 0 (+0x3a8: joint callback, back-link,
 * subscribed), binds pool entry 1 as its 12-slot animation set (+0x384), resolves the two named
 * joints (+0x3b4/+0x3b8), refreshes its callbacks and resets the +0x3c0/+0x444 and two +0x3ec
 * hit shapes; keeps the named motion handle from pool entry 0x17 (+0x470); creates the six
 * sub-items listed by the overlay's +0x2b88 table (+0x488: the first from the thread's +0x88
 * pool, the rest from the actor pool; attached, bit 1, polygon ids 3..0x1e for the last five),
 * registers three reactions (2/3 with a -0x10cc lift, 1/2 and 4/2) and two placements on the
 * +0x22c/+0x144 lists (+0x3ac/+0x3b0) at the zero vector, then loads sound 0x164. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;

struct Box {
    int xmin, ymin, zmin;
    int xmax, ymax, zmax;
};

struct PoolIds {
    int id[6];
};

struct Pose {
    Vec3 pos;
    int scale;
};

struct Lift {
    int a;
    int b;
    int c;
};

struct SubSlot {
    int item;
    int pad4;
};

struct HitShape {
    int w[11];
};

struct Ov276Actor {
    char pad000[0x64];
    int camera[4];
    char pad074[0x144 - 0x74];
    char pool144[0x3b0 - 0x144];
    int poolValue3b0;
    char pad3b4[0x3ec - 0x3b4];
    struct HitShape shapes[2];
    char pad444[0x488 - 0x444];
    struct SubSlot subs[6];
};

extern void func_ov276_020d00c0(void);
extern void func_ov276_020d0118(void);
extern void func_ov276_020d01ac(void);
extern void func_ov276_020d0504(void);
extern void WM_EndKeySharing_0x020d0194(void);
extern void WM_EndKeySharing_0x020d01a0(void);
extern void func_ov276_020d0374(void);
extern void func_ov276_020d0560(void);
extern void func_ov276_020d044c(void);
extern void func_ov276_020d08f8(void);
extern void func_ov276_020d0924(void);
extern void func_ov276_020cfc08(void);
extern void *func_ov107_020c9440(int pool, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern void func_0202a388(void *set, int model, void *pool, int count);
extern void func_0203b9ac(int item, void *set);
extern int func_0203bdfc(int item, const char *name);
extern void func_0203c7ac(int item, int a);
extern void func_0203c960(void *shape);
extern int func_ov107_020c9e50(void *item, const char *name);
extern int *OS_IsThreadAvailable_0x020c9848(void);
extern void func_ov107_020c9074(int self, int item);
extern void func_02016b60(void *model, int a, int id);
extern void func_ov107_020c92b0(int self, int a, int b, struct Lift *lift, int id);
extern int *func_01fffca8(void *list, int stride, int max);
extern int func_ov107_020c319c(void *pose);
extern void func_0203355c(int id);
extern const struct PoolIds data_ov276_020d2b88;
extern const char data_ov276_020d2c2c[];
extern const char data_ov276_020d2c3c[];
extern const char data_ov276_020d2c4c[];
extern const Vec3 data_02041dc8;

typedef struct { int x, y, z; } VecP_;
static inline void VecSetP_(VecP_ *v, int x, int y, int z) { v->x = x; v->y = y; v->z = z; }

void func_ov276_020cfcf8(char *self)
{
    struct PoolIds pools;
    struct Box box;
    struct Pose pose;
    struct Lift lift;
    struct Ov276Actor *actor;
    int *p;
    int handle;       /* the actor as the int handle the ov107 calls take */
    int i;
    int polyId;
    int value;

    pools = data_ov276_020d2b88;
    box.xmin = -0x1c7c;
    box.ymin = 0;
    box.zmin = -0xa44;
    box.xmax = box.xmin + 0x38f9;
    box.ymax = box.ymin + 0x20a8;
    box.zmax = box.zmin + 0x107a;
    *(void **)(self + 0x8) = func_ov276_020d00c0;
    *(void **)(self + 0xc) = func_ov276_020d0118;
    handle = (int)self;
    *(void **)(self + 0x1c) = func_ov276_020d01ac;
    *(void **)(self + 0x30) = func_ov276_020d0504;
    *(void **)(self + 0x28) = WM_EndKeySharing_0x020d0194;
    *(void **)(self + 0x2c) = WM_EndKeySharing_0x020d01a0;
    *(void **)(self + 0x34) = func_ov276_020d0374;
    *(void **)(self + 0x1d0) = func_ov276_020d0560;
    *(void **)(self + 0x1dc) = func_ov276_020d044c;
    *(void **)(self + 0x1e0) = func_ov276_020d08f8;
    *(void **)(self + 0x1e4) = func_ov276_020d0924;
    *(struct Box *)(self + 0x1fc) = box;
    *(int *)(self + 0x70) = 0x10cc;
    VecSetP_((VecP_ *)(self + 0x64), 0, *(int *)(self + 0x70), 0);
    *(u16 *)(self + 0x100 + 0xae) |= 8;
    polyId = 3;
    *(int *)(self + 0x3a8) = func_0203b898(func_ov107_020c9440(handle, 0));
    *(void **)(*(int *)(self + 0x3a8) + 0x74) = func_ov276_020cfc08;
    *(char **)(*(int *)(self + 0x3a8) + 0x84) = self;
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x3a8));
    func_0202a388(self + 0x384, *(int *)(*(int *)(self + 0x3a8) + 0x88), func_ov107_020c9440(handle, 1), 0xc);
    func_0203b9ac(*(int *)(self + 0x3a8), self + 0x384);
    *(int *)(self + 0x3b4) = func_0203bdfc(*(int *)(self + 0x3a8), data_ov276_020d2c2c);
    *(int *)(self + 0x3b8) = func_0203bdfc(*(int *)(self + 0x3a8), data_ov276_020d2c3c);
    func_0203c7ac(*(int *)(self + 0x3a8), 0);
    func_0203c960(self + 0x3c0);
    func_0203c960(self + 0x444);
    actor = (struct Ov276Actor *)self;
    for (i = 0; i < 2; i++) {
        func_0203c960(&actor->shapes[i]);
    }
    *(int *)(self + 0x470) = func_ov107_020c9e50(func_ov107_020c9440(handle, 0x17), data_ov276_020d2c4c);
    for (i = 0; i < 6; i++) {
        if (i < 1) {
            int *os = OS_IsThreadAvailable_0x020c9848();
            unsigned int kind = pools.id[i] & 0x1ff;
            unsigned int addr = (os[0x22] + 0x8000) & 0x00fffffc;
            addr = addr << 7;
            addr = addr | 0x80000000;
            value = func_0203b898((void *)(kind | addr));
        } else {
            value = func_0203b898(func_ov107_020c9440(handle, pools.id[i]));
        }
        func_ov107_020c9074(handle, (actor->subs[i].item = value));
        *(int *)(actor->subs[i].item + 0x5c) |= 2;
        if (i >= 1) {
            func_02016b60(*(void **)(*(int *)(actor->subs[i].item + 0x88) + 0x78), 0, polyId);
            polyId++;
            if (polyId >= 0x1f) {
                polyId = 3;
            }
        }
    }
    lift.c = lift.a = 0;
    lift.b = -0x10cc;
    func_ov107_020c92b0(handle, 2, 3, &lift, 0x6b8);
    func_ov107_020c92b0(handle, 1, 2, 0, 0x8f6);
    func_ov107_020c92b0(handle, 4, 2, 0, 0xb33);
    pose.pos = data_02041dc8;
    pose.scale = 0x10cc;
    *(int **)(self + 0x3ac) = func_01fffca8(self + 0x22c, 0x10, 0x64);
    **(int **)(self + 0x3ac) = func_ov107_020c319c(&pose);
    p = func_01fffca8(actor->pool144, 4, 0x64);
    value = (*p = func_ov107_020c319c(&pose));
    actor->poolValue3b0 = value;
    func_0203355c(0x164);
}
