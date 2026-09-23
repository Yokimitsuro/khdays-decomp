/* Constructor of the ov267 enemy. Installs the handlers (+8, +0xc draw,
 * +0x1c message, +0x20, +0x24 message pack, +0x28, +0x2c, +0x30, +0x34 update, +0x38, +0x1d0 hit
 * filter, +0x1dc, +0x1e0, +0x1e4), clears the +0x5e4 list, sets the +0x64 pose (scale 3.5), the
 * +0x1fc bounds box (+/-2.0 wide, 2.0 tall), bits 5 and 7 of the +0x60 high byte and bit 3 of
 * +0x1ae; builds the +0x384 rig from pose 0 (owned by the enemy, callback func_ov267_020cfc3c,
 * subscribed to +0x9c, lowered 2.0) and resolves its six bones (+0x58c, +0x590, +0x598, +0x59c,
 * +0x5a0, +0x5a4); builds the sixteen +0x38c chain items (pose 1, the last one pose 2; each keeps
 * the "tip" bone at +0x594, the first one is owned by the enemy with callback
 * func_ov267_020d0114), all hidden, subscribed and posed with the identity quaternion at +0x3cc;
 * builds the +0x388 grab part from pose 0xd (callback func_ov267_020d0180, bone at +0x588);
 * registers action 2/3 lowered by the scale (rate 0.6) and action 1/2 (rate 0.8); builds the
 * ten sub-items of data_ov267_020d5d40 into the +0x60c pair table (the first two from the shared
 * scene resource), reserves the +0x22c/+0x144 handles of three shapes (+0x4cc/+0x4d8: a capsule
 * of length 1.0 and radius 2.0, then two placements of scale 1.0), creates the two +0x5cc
 * trails (func_ov267_020d46d0) and the +0x5d4 shadow (func_ov267_020d5708), and loads sound
 * 0x15e. */
typedef unsigned short u16;
typedef void (*Callback)(void);
typedef struct { int x, y, z; } Vec3;
typedef struct { int w[4]; } Quat;
typedef struct { int id[10]; } IdTable;
typedef struct { int w[6]; } Box;
typedef struct { Vec3 pos; int scale; } Placement;
typedef struct { Vec3 pos; Vec3 axis; int length; int radius; } Capsule;
struct Items { char pad[0x38c]; int items[16]; };
struct Poses { char pad[0x3cc]; Quat pose[16]; };
struct Pair { int res; int handle; };
struct Pairs { char pad[0x60c]; struct Pair pairs[10]; };
struct b1 { unsigned int b0 : 1; };

extern void func_ov267_020d07e8(void);
extern void func_ov267_020d0858(void);
extern void func_ov267_020d0918(void);
extern void func_ov267_020d1418(void);
extern void func_ov267_020d0888(void);
extern void func_ov267_020d08d0(void);
extern void func_ov267_020d0d90(void);
extern void func_ov267_020d0e30(void);
extern void func_ov267_020d0ec4(void);
extern void func_ov267_020d1134(void);
extern void func_ov267_020d1474(void);
extern void func_ov267_020d10a4(void);
extern void func_ov267_020d16a4(void);
extern void func_ov267_020d16d0(void);
extern void func_ov267_020cfc3c(void);
extern void func_ov267_020d0114(void);
extern void func_ov267_020d0180(void);
extern void func_01fffc24(void *list);
extern void *func_ov107_020c9440(char *self, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern void func_0203ca14(void *srt, int x, int y, int z);
extern int func_0203bdfc(int item, const char *name);
extern void func_0203c7ac(int item, int a);
extern void func_ov107_020c92b0(char *self, int slot, int a, const Vec3 *v, int c);
extern char *OS_IsThreadAvailable_0x020c9848(void);
extern void func_ov107_020c9074(char *self, int item);
extern int *func_01fffca8(void *pool, int elementSize, int capacity);
extern int func_ov107_020c3210(const Capsule *capsule);
extern int func_ov107_020c319c(const Placement *placement);
extern int func_ov267_020d46d0(char *self);
extern int func_ov267_020d5708(char *self);
extern void func_0203355c(int resourceId);
extern IdTable data_ov267_020d5d40;
extern const char data_ov267_020d5d8c[];
extern const char data_ov267_020d5d9c[];
extern const char data_ov267_020d5da8[];
extern const char data_ov267_020d5db4[];
extern const char data_ov267_020d5dc4[];
extern const char data_ov267_020d5dd0[];
extern const char data_ov267_020d5ddc[];
extern const char data_ov267_020d5de4[];
extern const Quat data_020420f8;
extern const Vec3 data_02041dc8;
extern const Vec3 data_02042264;

void func_ov267_020d025c(char *self)
{
    IdTable ids = data_ov267_020d5d40;
    Box params;
    Placement place;
    Capsule cap;
    Vec3 lift;
    Quat quat;
    Vec3 zero;
    u16 hw;
    int i;
    int *slot;
    int node;

    params.w[0] = -0x2000;
    params.w[1] = 0;
    params.w[2] = -0x2000;
    params.w[3] = 0x2000;
    params.w[4] = 0x2000;
    params.w[5] = 0x2000;
    *(Callback *)(self + 0x8) = func_ov267_020d07e8;
    *(Callback *)(self + 0xc) = func_ov267_020d0858;
    *(Callback *)(self + 0x1c) = func_ov267_020d0918;
    *(Callback *)(self + 0x30) = func_ov267_020d1418;
    *(Callback *)(self + 0x28) = func_ov267_020d0888;
    *(Callback *)(self + 0x2c) = func_ov267_020d08d0;
    *(Callback *)(self + 0x34) = func_ov267_020d0d90;
    *(Callback *)(self + 0x20) = func_ov267_020d0e30;
    *(Callback *)(self + 0x24) = func_ov267_020d0ec4;
    *(Callback *)(self + 0x38) = func_ov267_020d1134;
    *(Callback *)(self + 0x1d0) = func_ov267_020d1474;
    *(Callback *)(self + 0x1dc) = func_ov267_020d10a4;
    *(Callback *)(self + 0x1e0) = func_ov267_020d16a4;
    *(Callback *)(self + 0x1e4) = func_ov267_020d16d0;
    func_01fffc24(self + 0x5e4);
    /* the default scale first: the overwritten store is dropped after scheduling but still
     * spends the scheduler's budget for this block, which keeps the rig callback's load order */
    *(int *)(self + 0x70) = 0x1000;
    *(int *)(self + 0x70) = 0x3800;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0x3800;
    *(int *)(self + 0x6c) = 0;
    *(Box *)(self + 0x1fc) = params;
    hw = *(u16 *)(self + 0x60);
    *(u16 *)(self + 0x60) = (hw & ~0xff00) |
        ((((((unsigned int)hw << 0x10) >> 0x18) | 0xa0) << 0x18) >> 0x10);
    *(u16 *)(self + 0x100 + 0xae) |= 8;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(self, 0));
    *(char **)(*(int *)(self + 0x384) + 0x84) = self;
    *(Callback *)(*(int *)(self + 0x384) + 0x74) = func_ov267_020cfc3c;
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    func_0203ca14((void *)(*(int *)(self + 0x384) + 4), 0, 0, -0x2000);
    *(int *)(self + 0x58c) = func_0203bdfc(*(int *)(self + 0x384), data_ov267_020d5d8c);
    *(int *)(self + 0x590) = func_0203bdfc(*(int *)(self + 0x384), data_ov267_020d5d9c);
    *(int *)(self + 0x598) = func_0203bdfc(*(int *)(self + 0x384), data_ov267_020d5da8);
    *(int *)(self + 0x59c) = func_0203bdfc(*(int *)(self + 0x384), data_ov267_020d5db4);
    *(int *)(self + 0x5a0) = func_0203bdfc(*(int *)(self + 0x384), data_ov267_020d5dc4);
    *(int *)(self + 0x5a4) = func_0203bdfc(*(int *)(self + 0x384), data_ov267_020d5dd0);
    *(char **)(self + 0x2cc) = self + 0x514;
    quat = data_020420f8;
    for (i = 0; i < 16; i++) {
        if (i < 15) {
            ((struct Items *)self)->items[i] = func_0203b898(func_ov107_020c9440(self, 1));
            *(int *)(self + 0x594) = func_0203bdfc(((struct Items *)self)->items[i], data_ov267_020d5ddc);
        } else {
            ((struct Items *)self)->items[i] = func_0203b898(func_ov107_020c9440(self, 2));
        }
        if (i == 0) {
            *(Callback *)(((struct Items *)self)->items[i] + 0x6c) = func_ov267_020d0114;
            *(char **)(((struct Items *)self)->items[i] + 0x84) = self;
        }
        *(int *)(((struct Items *)self)->items[i] + 0x5c) |= 2;
        ((struct b1 *)(((struct Items *)self)->items[i] + 0x5c))->b0 = 1;
        func_0203bfb4(*(int *)(self + 0x9c), ((struct Items *)self)->items[i]);
        func_0203c7ac(((struct Items *)self)->items[i], 0);
        ((struct Poses *)self)->pose[i] = quat;
    }
    *(int *)(self + 0x57c) = 0;
    *(int *)(self + 0x388) = func_0203b898(func_ov107_020c9440(self, 0xd));
    *(Callback *)(*(int *)(self + 0x388) + 0x6c) = func_ov267_020d0180;
    *(char **)(*(int *)(self + 0x388) + 0x84) = self;
    func_0203c7ac(*(int *)(self + 0x388), 0);
    *(int *)(self + 0x588) = func_0203bdfc(*(int *)(self + 0x388), data_ov267_020d5de4);
    lift.x = 0;
    lift.y = -0x3800;
    lift.z = 0;
    func_ov107_020c92b0(self, 2, 3, &lift, 0x99a);
    func_ov107_020c92b0(self, 1, 2, 0, 0xccd);
    for (i = 0; i < 10; i++) {
        if (i <= 1) {
            node = func_0203b898((void *)((ids.id[i] & 0x1ff)
                | (((*(int *)(OS_IsThreadAvailable_0x020c9848() + 0x88) + 0x8000) & 0xfffffc) << 7 | 0x80000000)));
        } else {
            node = func_0203b898(func_ov107_020c9440(self, ids.id[i]));
        }
        func_ov107_020c9074(self, ((struct Pairs *)self)->pairs[i].res = node);
        *(int *)(((struct Pairs *)self)->pairs[i].res + 0x5c) |= 2;
    }
    zero = data_02041dc8;
    place.scale = 0x1000;
    place.pos = zero;
    cap.pos = zero;
    cap.axis = data_02042264;
    cap.length = 0x1000;
    cap.radius = 0x2000;
    for (i = 0; i < 3; i++) {
        ((int **)(self + 0x4cc))[i] = func_01fffca8(self + 0x22c, 0x10, 100);
        *((int **)(self + 0x4cc))[i] = i == 0 ? func_ov107_020c3210(&cap) : func_ov107_020c319c(&place);
        slot = func_01fffca8(self + 0x144, 4, 100);
        node = i == 0 ? func_ov107_020c3210(&cap) : func_ov107_020c319c(&place);
        ((int *)(self + 0x4d8))[i] = *slot = node;
    }
    for (i = 0; i < 2; i++) {
        ((int *)(self + 0x5cc))[i] = func_ov267_020d46d0(self);
    }
    *(int *)(self + 0x5d4) = func_ov267_020d5708(self);
    func_0203355c(0x15e);
}
