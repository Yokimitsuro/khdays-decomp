/* Constructor of the ov146 actor: installs the handlers (+8 destroy, +0x1c spawn message, +0x28 /
 * +0x2c / +0x30 callbacks, +0x34 block-chain propagation, +0x1d0 damage, +0x1dc motion binding,
 * +0x1e0 / +0x1e4), the pose scale 0.75 and the +0x1fc bounds (min (-0.93, 0.006, -0.52), extent
 * (1.86, 1.76, 0.84)); builds the body model from pool entry 0 (+0x384, subscribed) with its Broot
 * joint (+0x3c0) and entry 1 as motion on the +0x388 track; five hidden parts (+0x3c4, stride 8) from
 * the ids of data_ov146_020cf4f8 -- the first three relative to the running thread's resource, the
 * last two from the pool; actions 2, 1 and 4 at 2.0; the pose as a hit shape on the +0x22c (+0x3ac)
 * and +0x144 (+0x3b0) lists; the two helpers 020ce308 / 020cee30 (+0x3b8 / +0x3bc) and sound 0x125. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct { int x, y, z; } Vec3;
typedef void (*Callback)(void);
typedef struct { Vec3 min; Vec3 max; } Box;
typedef struct { Vec3 v; int nScale; } Pose;
typedef struct { int id[5]; } PartIds;
struct Ov146Part { int item; int pad; };

extern void func_ov146_020cc2ac(void);
extern void func_ov146_020cc35c(void);
extern void func_ov146_020cc5ec(void);
extern void func_ov146_020cc2f4(void);
extern void func_ov146_020cc328(void);
extern void func_ov146_020cc508(void);
extern void func_ov146_020cc658(void);
extern void func_ov146_020cc570(void);
extern void func_ov146_020cc7dc(void);
extern void func_ov146_020cc808(void);
extern void *func_ov107_020c9440(char *self, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern int func_0203bee8(int item, int kind, const char *name);
extern void func_0202a388(void *track, int model, void *resource, int slot);
extern void func_0203b9ac(int item, void *track);
extern int OS_IsThreadAvailable_0x020c9848(void);
extern void func_ov107_020c9074(char *self, int item);
extern void func_ov107_020c92b0(char *self, int action, int a, int b, int scale);
extern int *func_01fffca8(void *list, int stride, int max);
extern int func_ov107_020c319c(Pose *pose);
extern int func_ov146_020ce308(char *self);
extern int func_ov146_020cee30(char *self);
extern void func_0203355c(int id);
extern const PartIds data_ov146_020cf4f8;
extern const char data_ov146_020cf52c[];
extern const Vec3 data_02041dc8;

void func_ov146_020cbfc4(char *self)
{
    PartIds ids = data_ov146_020cf4f8;
    Box box;
    Pose pose;
    int minX;
    int minY;
    int minZ;
    int *slot;
    int i;

    minX = -0xeea;
    minZ = -0x858;
    minY = 0x17;
    *(Callback *)(self + 0x8) = func_ov146_020cc2ac;
    *(Callback *)(self + 0x1c) = func_ov146_020cc35c;
    box.min.x = minX;
    box.min.y = minY;
    box.min.z = minZ;
    box.max.x = box.min.x + 0x1dd3;
    box.max.y = box.min.y + 0x1c27;
    box.max.z = box.min.z + 0xd64;
    *(Callback *)(self + 0x30) = func_ov146_020cc5ec;
    *(Callback *)(self + 0x28) = func_ov146_020cc2f4;
    *(Callback *)(self + 0x2c) = func_ov146_020cc328;
    *(Callback *)(self + 0x34) = func_ov146_020cc508;
    *(Callback *)(self + 0x1d0) = func_ov146_020cc658;
    *(Callback *)(self + 0x1dc) = func_ov146_020cc570;
    *(Callback *)(self + 0x1e0) = func_ov146_020cc7dc;
    *(Callback *)(self + 0x1e4) = func_ov146_020cc808;
    *(int *)(self + 0x70) = 0xc00;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0xc00;
    *(int *)(self + 0x6c) = 0;
    *(Box *)(self + 0x1fc) = box;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(self, 0));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    *(int *)(self + 0x3c0) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov146_020cf52c);
    func_0202a388(self + 0x388, *(int *)(*(int *)(self + 0x384) + 0x88), func_ov107_020c9440(self, 1), 0xc);
    func_0203b9ac(*(int *)(self + 0x384), self + 0x388);
    for (i = 0; i < 5; i++) {
        int item;

        if (i < 3) {
            item = func_0203b898((void *)((ids.id[i] & 0x1ff)
                | ((((*(int *)(OS_IsThreadAvailable_0x020c9848() + 0x88) + 0x8000) & 0xfffffc) << 7) | 0x80000000)));
        } else {
            item = func_0203b898(func_ov107_020c9440(self, ids.id[i]));
        }
        ((struct Ov146Part *)(self + 0x3c4))[i].item = item;
        func_ov107_020c9074(self, ((struct Ov146Part *)(self + 0x3c4))[i].item);
        *(int *)(((struct Ov146Part *)(self + 0x3c4))[i].item + 0x5c) |= 2;
    }
    func_ov107_020c92b0(self, 2, 1, 0, 0x2000);
    func_ov107_020c92b0(self, 1, 1, 0, 0x2000);
    func_ov107_020c92b0(self, 4, 1, 0, 0x2000);
    pose = *(Pose *)(self + 0x64);
    pose.v = data_02041dc8;
    *(int **)(self + 0x3ac) = func_01fffca8(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x3ac) = func_ov107_020c319c(&pose);
    slot = func_01fffca8(self + 0x144, 4, 100);
    *(int *)(self + 0x3b0) = *slot = func_ov107_020c319c(&pose);
    *(int *)(self + 0x3b8) = func_ov146_020ce308(self);
    *(int *)(self + 0x3bc) = func_ov146_020cee30(self);
    func_0203355c(0x125);
}
