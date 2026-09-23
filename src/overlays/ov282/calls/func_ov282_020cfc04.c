/* Constructor of the ov282 enemy (the ov210/ov211 constructor with pose/radius 1.8, reaction id 0x733 and sound 0x16a). Installs the handlers, clears +0x1f4,
 * sets the +0x64 pose (scale 1.25), raises bits 3 and 4 of +0x1ae, builds the +0x384 rig from
 * pose 0 (subscribed to +0x9c, 12-channel animation set 1 bound at +0x388) and raises bit 1 of the
 * parent's +0x5c; resolves five bones (+0x3bc in set 3, +0x3c0/+0x3c4/+0x3c8/+0x3cc in set 1) and
 * the "move" handle of set 0x1b (+0x3b8); builds the eight sub-items of data_ov282_020d4678 into
 * the +0x3d0 pair table (registered, bit 1 of +0x5c); registers reaction 2/3 (0x500); allocates the
 * +0x3d4 slot for the ov282 3cdc child; reserves the +0x22c and +0x144 collision handles
 * (+0x3b0/+0x3b4) from a zero seed pointing up with scale 1.0 and radius 1.25, and loads sound
 * 0x117. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { int w[8]; } PoseTable;
typedef struct { Vec3 pos; Vec3 up; int scale; int radius; } Seed;
struct Pair { int res; int handle; };

extern void *func_ov107_020c9440(char *self, int kind);
extern int func_0203b898(void *res);
extern void func_0203bfb4(int list, int obj);
extern void func_0202a388(void *set, int model, void *anim, int n);
extern void func_0203b9ac(int obj, void *set);
extern int func_0203bee8(int obj, int set, const char *name);
extern int func_ov107_020c9e50(void *res, const char *name);
extern void *func_0203d15c(int size);
extern void func_ov107_020c9074(char *self, int obj);
extern void func_ov107_020c92b0(char *self, int a, int b, void *lift, int id);
extern int func_ov282_020d3cdc(char *self);
extern int *func_01fffca8(void *list, int stride, int max);
extern int func_ov107_020c3210(Seed *seed);
extern void func_0203355c(int id);
extern const PoseTable data_ov282_020d4678;
extern const char data_ov282_020d47ac[];
extern const char data_ov282_020d47b8[];
extern const char data_ov282_020d47c0[];
extern const char data_ov282_020d47cc[];
extern const char data_ov282_020d47dc[];
extern const char data_ov282_020d47ec[];
extern const Vec3 data_02041dc8;
extern const Vec3 data_02042264;
extern void func_ov282_020cfef0(void);
extern void func_ov282_020cff48(void);
extern void func_ov282_020cff6c(void);
extern void func_ov282_020cff98(void);
extern void func_ov282_020cffc4(void);
extern void func_ov282_020d0400(void);
extern void func_ov282_020d0254(void);
extern void func_ov282_020d044c(void);
extern void func_ov282_020d06c0(void);
extern void func_ov282_020d01d4(void);

void func_ov282_020cfc04(char *self)
{
    PoseTable poses;
    Seed seed;
    int i;
    int *p;
    int v;

    poses = data_ov282_020d4678;
    *(void **)(self + 8) = (void *)func_ov282_020cfef0;
    *(void **)(self + 0xc) = (void *)func_ov282_020cff48;
    *(void **)(self + 0x28) = (void *)func_ov282_020cff6c;
    *(void **)(self + 0x2c) = (void *)func_ov282_020cff98;
    *(void **)(self + 0x1c) = (void *)func_ov282_020cffc4;
    *(void **)(self + 0x30) = (void *)func_ov282_020d0400;
    *(void **)(self + 0x34) = (void *)func_ov282_020d0254;
    *(void **)(self + 0x1d0) = (void *)func_ov282_020d044c;
    *(void **)(self + 0x1e0) = (void *)func_ov282_020d06c0;
    *(void **)(self + 0x1dc) = (void *)func_ov282_020d01d4;
    *(int *)(self + 0x1f4) = 0;
    *(int *)(self + 0x70) = 0x1ccc;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0x1ccc;
    *(int *)(self + 0x6c) = 0;
    *(u16 *)(self + 0x1ae) |= 0x18;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(self, 0));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    func_0202a388(self + 0x388, *(int *)(*(int *)(self + 0x384) + 0x88), func_ov107_020c9440(self, 1), 0xc);
    func_0203b9ac(*(int *)(self + 0x384), self + 0x388);
    *(int *)(*(int *)(self + 0x9c) + 0x5c) |= 2;
    *(int *)(self + 0x3bc) = func_0203bee8(*(int *)(self + 0x384), 3, data_ov282_020d47ac);
    *(int *)(self + 0x3c0) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov282_020d47b8);
    *(int *)(self + 0x3c4) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov282_020d47c0);
    *(int *)(self + 0x3c8) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov282_020d47cc);
    *(int *)(self + 0x3cc) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov282_020d47dc);
    *(int *)(self + 0x3b8) = func_ov107_020c9e50(func_ov107_020c9440(self, 0x1b), data_ov282_020d47ec);
    *(void **)(self + 0x3d0) = func_0203d15c(0x40);
    for (i = 0; i < 8; i++) {
        (*(struct Pair **)(self + 0x3d0))[i].res = func_0203b898(func_ov107_020c9440(self, poses.w[i]));
        func_ov107_020c9074(self, (*(struct Pair **)(self + 0x3d0))[i].res);
        *(int *)((*(struct Pair **)(self + 0x3d0))[i].res + 0x5c) |= 2;
    }
    func_ov107_020c92b0(self, 2, 3, 0, 0x733);
    *(void **)(self + 0x3d4) = func_0203d15c(4);
    **(int **)(self + 0x3d4) = func_ov282_020d3cdc(self);
    seed.pos = data_02041dc8;
    seed.up = data_02042264;
    seed.scale = 0x1000;
    seed.radius = 0x1ccc;
    *(int **)(self + 0x3b0) = func_01fffca8(self + 0x22c, 0x10, 0x64);
    **(int **)(self + 0x3b0) = func_ov107_020c3210(&seed);
    p = func_01fffca8(self + 0x144, 4, 0x64);
    v = (*p = func_ov107_020c3210(&seed));
    *(int *)(self + 0x3b4) = v;
    func_0203355c(0x16a);
}
