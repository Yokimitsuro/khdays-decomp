/* Constructor of the ov259 enemy. Keeps the save's variant flag (bit 2 of data_0204c240) in +0x428,
 * installs the handlers (+8, +0xc, +0x1c message, +0x30, +0x34, +0x28, +0x2c, +0x1d0 hit, +0x1dc), the
 * +0x1c9 kind (2), the unit +0x64 pose and the +0x1fc bounds box; builds the +0x38c body from pose 0
 * (1 for the variant; owned, callback 020cbfc8, subscribed to +0x9c), clears the two +0x394 slots
 * (-1), builds the +0x390 wing rig (pose 0x20, animation 0x21 at +0x3e0), the +0x40c bone of the body,
 * the +0x414 bone of pose 0x1f and the thirteen +0x430 sub-items of data_ov259_020d2f2c (attached,
 * hidden); the +0x404 / +0x408 placements come from the pose, the +0x384 and +0x388 helpers are
 * created (+0x42c set in between), and sound 0x17d (variant) or 0x172 loads. */
typedef unsigned char u8;
typedef void (*Callback)(void);
typedef struct { int x, y, z; } Vec3;
typedef struct { int id[13]; } IdTable13;
typedef struct { Vec3 min; Vec3 max; } Bounds;
struct Pair { int res; int handle; };
struct Ov259Parts { char pad[0x430]; struct Pair items[13]; };

extern void func_ov259_020cc508(void);
extern void func_ov259_020cc590(void);
extern void func_ov259_020cc678(void);
extern void func_ov259_020ccde8(void);
extern void func_ov259_020ccb0c(void);
extern void func_ov259_020cc610(void);
extern void func_ov259_020cc644(void);
extern void func_ov259_020cce44(void);
extern void func_ov259_020ccbc0(void);
extern void func_ov259_020cbfc8(void);
extern void *func_ov107_020c9440(char *self, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern void func_0202a388(void *dst, int a, void *b, int n);
extern void func_0203b9ac(int obj, void *block);
extern int func_0203bee8(int item, int kind, const char *name);
extern int func_ov107_020c9e50(void *item, const char *name);
extern void func_ov107_020c9074(char *self, int item);
extern int *func_01fffca8(void *pool, int elementSize, int capacity);
extern int func_ov107_020c319c(void *pose);
extern int func_ov259_020d1840(char *self);
extern int func_ov259_020d2780(char *self);
extern void func_0203355c(int resourceId);
extern IdTable13 data_ov259_020d2f2c;
extern u8 data_0204c240;
extern const char data_ov259_020d2fcc[];
extern const char data_ov259_020d2fd4[];

void func_ov259_020cc218(char *self)
{
    IdTable13 ids = data_ov259_020d2f2c;
    Bounds bounds;
    int i;
    int *slot;
    int node;

    *(int *)(self + 0x428) = data_0204c240 & 4;
    bounds.min.x = -0x190b;
    bounds.min.y = -6;
    bounds.min.z = -0x1fc4;
    bounds.max.x = bounds.min.x + 0x3217;
    bounds.max.y = bounds.min.y + 0x2cc3;
    bounds.max.z = bounds.min.z + 0x2597;
    *(Callback *)(self + 0x8) = func_ov259_020cc508;
    *(Callback *)(self + 0xc) = func_ov259_020cc590;
    *(Callback *)(self + 0x1c) = func_ov259_020cc678;
    *(Callback *)(self + 0x30) = func_ov259_020ccde8;
    *(Callback *)(self + 0x34) = func_ov259_020ccb0c;
    *(Callback *)(self + 0x28) = func_ov259_020cc610;
    *(Callback *)(self + 0x2c) = func_ov259_020cc644;
    *(Callback *)(self + 0x1d0) = func_ov259_020cce44;
    *(Callback *)(self + 0x1dc) = func_ov259_020ccbc0;
    *(u8 *)(self + 0x1c9) = 2;
    *(int *)(self + 0x70) = 0x1000;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0x1000;
    *(int *)(self + 0x6c) = 0;
    *(Bounds *)(self + 0x1fc) = bounds;
    *(int *)(self + 0x38c) = func_0203b898(func_ov107_020c9440(self, (data_0204c240 & 4) ? 1 : 0));
    *(char **)(*(int *)(self + 0x38c) + 0x84) = self;
    *(Callback *)(*(int *)(self + 0x38c) + 0x68) = func_ov259_020cbfc8;
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x38c));
    for (i = 0; i < 2; i++) {
        *(signed char *)(self + 0x394 + i) = -1;
    }
    *(int *)(self + 0x390) = func_0203b898(func_ov107_020c9440(self, 0x20));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x390));
    func_0202a388(self + 0x3e0, *(int *)(*(int *)(self + 0x390) + 0x88), func_ov107_020c9440(self, 0x21), 0xc);
    func_0203b9ac(*(int *)(self + 0x390), self + 0x3e0);
    *(int *)(self + 0x40c) = func_0203bee8(*(int *)(self + 0x38c), 3, data_ov259_020d2fcc);
    *(int *)(self + 0x414) = func_ov107_020c9e50(func_ov107_020c9440(self, 0x1f), data_ov259_020d2fd4);
    for (i = 0; i < 13; i++) {
        ((struct Ov259Parts *)self)->items[i].res = func_0203b898(func_ov107_020c9440(self, ids.id[i]));
        func_ov107_020c9074(self, ((struct Ov259Parts *)self)->items[i].res);
        *(int *)(((struct Ov259Parts *)self)->items[i].res + 0x5c) |= 2;
    }
    *(int **)(self + 0x404) = func_01fffca8(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x404) = func_ov107_020c319c(self + 0x64);
    slot = func_01fffca8(self + 0x144, 4, 100);
    node = func_ov107_020c319c(self + 0x64);
    *(int *)(self + 0x408) = *slot = node;
    *(int *)(self + 0x384) = func_ov259_020d1840(self);
    *(int *)(self + 0x42c) = 1;
    *(int *)(self + 0x388) = func_ov259_020d2780(self);
    func_0203355c(*(int *)(self + 0x428) != 0 ? 0x17d : 0x172);
}
