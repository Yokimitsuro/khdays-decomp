/* Constructor of the ov213 enemy's companion (x2 with ov273): installs the handlers (+8, +0xc
 * draw, +0x1c message, +0x30, +0x1dc), raises flags 0x1d in +0x1ae and 0x64 in the +0x60 high
 * byte, sets the +0x1c9 group to 2, clears +0x54/+0x58 and places the +0x64 pose at the origin
 * with scale 0.25. Builds the +0x388 and +0x38c rigs from poses 0x1c and 0x3c of the +0x384 pool
 * (both subscribed to +0x9c), a one-slot +0x3a8 table holding the sub-item of the pool's shared
 * pose (data_ov273_020d6b68; registered, bit 1 of +0x5c), and reserves the +0x144 collision handle
 * (+0x390) from a capsule at the origin along -z (radius 1.82, height 0.31). The shared pose
 * id is read first and kept in the frame across the rig construction. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 pos; Vec3 up; int radius; int height; } Capsule;

extern unsigned func_ov107_020c9440(int pool, int kind);
extern int func_0203b898(unsigned res);
extern void func_0203bfb4(int list, int obj);
extern void *func_0203d15c(int size);
extern void func_ov107_020c9074(char *self, int obj);
extern int *func_01fffca8(void *list, int stride, int max);
extern int func_ov107_020c3210(Capsule *capsule);
extern int data_ov273_020d6b68;
extern const Vec3 data_02041dc8;
extern const Vec3 data_02042258;
extern void func_ov273_020d4398(void);
extern void func_ov273_020d43d0(void);
extern void func_ov273_020d4404(void);
extern void func_ov273_020d459c(void);
extern void func_ov273_020d44f0(void);

void func_ov273_020d41e8(char *self)
{
    volatile int shared;
    Vec3 zero;
    Capsule capsule;
    u16 v;
    int *p;
    int h;

    *(void **)(self + 8) = (void *)func_ov273_020d4398;
    *(void **)(self + 0xc) = (void *)func_ov273_020d43d0;
    *(void **)(self + 0x1c) = (void *)func_ov273_020d4404;
    *(void **)(self + 0x30) = (void *)func_ov273_020d459c;
    *(void **)(self + 0x1dc) = (void *)func_ov273_020d44f0;
    *(u16 *)(self + 0x1ae) |= 0x1d;
    shared = data_ov273_020d6b68;
    v = *(u16 *)(self + 0x60);
    *(u16 *)(self + 0x60) = (u16)((v & ~0xff00) | (((((unsigned int)v << 0x10) >> 0x18 | 0x64) << 0x18) >> 0x10));
    *(unsigned char *)(self + 0x1c9) = 2;
    *(int *)(self + 0x54) = 0;
    *(int *)(self + 0x58) = 0;
    zero = data_02041dc8;
    *(Vec3 *)(self + 0x64) = zero;
    /* default scale first: the overwritten store is dropped after scheduling but spends the
     * block's scheduling budget, which keeps the ROM's capsule stores ahead of the fca8 call */
    *(int *)(self + 0x70) = 0x1000;
    *(int *)(self + 0x70) = 0x400;
    *(int *)(self + 0x388) = func_0203b898(func_ov107_020c9440(*(int *)(self + 0x384), 0x1c));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x388));
    *(int *)(self + 0x38c) = func_0203b898(func_ov107_020c9440(*(int *)(self + 0x384), 0x3c));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x38c));
    *(void **)(self + 0x3a8) = func_0203d15c(8);
    **(int **)(self + 0x3a8) = func_0203b898(func_ov107_020c9440(*(int *)(self + 0x384), shared));
    func_ov107_020c9074(self, **(int **)(self + 0x3a8));
    *(int *)(**(int **)(self + 0x3a8) + 0x5c) |= 2;
    capsule.pos = zero;
    capsule.up = data_02042258;
    capsule.radius = 0x1d1e;
    capsule.height = 0x500;
    p = func_01fffca8(self + 0x144, 4, 0x64);
    h = (*p = func_ov107_020c3210(&capsule));
    *(int *)(self + 0x390) = h;
}
