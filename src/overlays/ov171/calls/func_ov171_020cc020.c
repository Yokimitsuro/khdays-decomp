/* Constructor of the ov171 enemy (twins by byte identity). Installs the handlers (+8 release, +0xc
 * draw veneer, +0x1c spawn message, +0x28/+0x2c/+0x30 callbacks, +0x34 tick, +0x1d0 hit,
 * +0x1dc/+0x1e0 finish), sets bit 6 of the +0x60 high byte, the +0x70 latch (0xbb3), zeroes
 * the +0x64 camera vector, writes the {-1,0,-1,1,1,1} bounds at +0x1fc, builds the model item
 * from table entry 0 (subscribed, translated 0xbb3 down, its +0x74 callback and +0x84 owner
 * set, +0xad cleared) and resolves the "Bone04"/"body" handles into +0x38c/+0x390/+0x394; then
 * allocates the 3-entry effect set at +0x39c from the table's three ids (each attached and
 * flagged), registers the four action slots (0/2/1/4) with 0x2ecc, creates the two pools at
 * +0x388/+0x398 seeded with the camera key, allocates the +0x3ac child and requests resource
 * 0x140. Codegen: the item stores are spelled `*(Callback *)(*(int *)(self + 0x384) + 0x74)`
 * on the `char *self` parameter (the pool load of the value is then emitted before the item
 * load and the shared zero sits in r4); the bounds block sits before the +0x60 update. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int a, b, c; } Vec3b;
typedef struct { Vec3 vector; int scalar; } CameraWork;
typedef struct { int w[6]; } Bounds;
typedef struct { int id[3]; } IdTable;
typedef struct { int subitem; int pad; } Slot;
typedef unsigned short u16;
typedef void (*Callback)(void);

extern void func_ov171_020cc344(void);
extern void WM_EndKeySharing_ov171_0x020cc384(void);
extern void func_ov171_020cc3e0(void);
extern void func_ov171_020cc760(void);
extern void func_ov171_020cc390(void);
extern void func_ov171_020cc3b8(void);
extern void func_ov171_020cc628(void);
extern void func_ov171_020cc7bc(void);
extern void func_ov171_020cc5f8(void);
extern void func_ov171_020cc9dc(void);
extern void func_ov171_020cbfc4(void);
extern void *func_ov107_020c9440(char *self, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern void func_0203ca14(void *srt, int x, int y, int z);
extern int func_0203bee8(int item, int kind, void *name);
extern int *func_0203d15c(int size);
extern void func_ov107_020c9074(char *self, int item);
extern void func_ov107_020c92b0(char *self, int slot, int a, int b, int c);
extern int *func_01fffca8(void *pool, int elementSize, int capacity);
extern int func_ov107_020c319c(void *camera);
extern void func_0203355c(int resourceId);
extern int *func_ov171_020ce108(char *self);
extern Vec3 data_02041dc8;
extern IdTable data_ov171_020ceeac;
extern char data_ov171_020ceecc[];
extern char data_ov171_020ceed4[];

void func_ov171_020cc020(char *self)
{
    IdTable ids = data_ov171_020ceeac;
    Bounds bounds;
    CameraWork work;
    Vec3 v;
    u16 hw;
    int i;
    int *slot;

    *(Callback *)(self + 0x8) = func_ov171_020cc344;
    *(Callback *)(self + 0xc) = WM_EndKeySharing_ov171_0x020cc384;
    *(Callback *)(self + 0x1c) = func_ov171_020cc3e0;
    *(Callback *)(self + 0x30) = func_ov171_020cc760;
    *(Callback *)(self + 0x28) = func_ov171_020cc390;
    *(Callback *)(self + 0x2c) = func_ov171_020cc3b8;
    *(Callback *)(self + 0x34) = func_ov171_020cc628;
    *(Callback *)(self + 0x1d0) = func_ov171_020cc7bc;
    *(Callback *)(self + 0x1dc) = func_ov171_020cc5f8;
    *(Callback *)(self + 0x1e0) = func_ov171_020cc9dc;
    bounds.w[0] = -0x1000;
    bounds.w[2] = -0x1000;
    bounds.w[1] = 0;
    bounds.w[3] = 0x1000;
    bounds.w[4] = 0x1000;
    bounds.w[5] = 0x1000;
    hw = *(u16 *)(self + 0x60);
    *(u16 *)(self + 0x60) = (hw & ~0xff00) |
        ((((((unsigned int)hw << 0x10) >> 0x18) | 0x40) << 0x18) >> 0x10);
    *(int *)(self + 0x70) = 0xbb3;
    v = data_02041dc8;
    *(Vec3b *)(self + 0x64) = *(Vec3b *)&data_02041dc8;
    *(Bounds *)(self + 0x1fc) = bounds;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(self, 0));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    func_0203ca14((void *)(*(int *)(self + 0x384) + 4), 0, -0xbb3, 0);
    *(Callback *)(*(int *)(self + 0x384) + 0x74) = func_ov171_020cbfc4;
    *(char **)(*(int *)(self + 0x384) + 0x84) = self;
    *(unsigned char *)(*(int *)(self + 0x384) + 0xad) = 0;
    *(int *)(self + 0x38c) = func_0203bee8(*(int *)(self + 0x384), 3, data_ov171_020ceecc);
    *(int *)(self + 0x390) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov171_020ceecc);
    *(int *)(self + 0x394) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov171_020ceed4);
    *(int **)(self + 0x39c) = func_0203d15c(0x18);
    for (i = 0; i < 3; i++) {
        if (i < 0) {
            (*(Slot **)(self + 0x39c))[i].subitem = func_0203b898((void *)ids.id[i]);
        } else {
            (*(Slot **)(self + 0x39c))[i].subitem = func_0203b898(func_ov107_020c9440(self, ids.id[i]));
        }
        func_ov107_020c9074(self, (*(Slot **)(self + 0x39c))[i].subitem);
        *(int *)((*(Slot **)(self + 0x39c))[i].subitem + 0x5c) |= 2;
    }
    func_ov107_020c92b0(self, 0, 1, 0, 0x2ecc);
    func_ov107_020c92b0(self, 2, 1, 0, 0x2ecc);
    func_ov107_020c92b0(self, 1, 1, 0, 0x2ecc);
    func_ov107_020c92b0(self, 4, 1, 0, 0x2ecc);
    work = *(CameraWork *)(self + 0x64);
    work.vector = v;
    *(int **)(self + 0x388) = func_01fffca8(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x388) = func_ov107_020c319c(&work);
    slot = func_01fffca8(self + 0x144, 4, 100);
    *(int *)(self + 0x398) = *slot = func_ov107_020c319c(&work);
    *(int **)(self + 0x3ac) = func_ov171_020ce108(self);
    func_0203355c(0x140);
}
