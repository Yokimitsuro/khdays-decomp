/* Constructor of the ov246 enemy (and its byte-identical twin): installs the handlers (+8 tick
 * 020cc248, +0xc 020cc290, +0x1c message 020cc398, +0x30 020cc728, +0x28 020cc53c, +0x2c
 * 020cc564, +0x34 020cc58c, +0x1d0 on-hit 020cc784, +0x1e0 release 020cc99c, +0x1dc finish
 * 020cc2dc), seeds the +0x64 pose (scale 0x1800, y 0x1800), builds the primary item from pool
 * entry 0 (subscribed), resolves its two mode-3 joints (+0x398 data_ov246_020d312c, +0x394
 * data_ov246_020d3134), keeps the data_ov246_020d3138 motion handle of pool entry 1 (+0x39c),
 * the eight sub-items of the data_ov246_020d30c0 kinds in a fresh 64-byte slot table (+0x390,
 * attached, bit 1 on their +0x5c), configures actions 0/1/2/4 (mode 1, rate 0x3000), creates a
 * placement from the +0x64 pose on the +0x22c list (+0x384) and a capsule (zero position, world
 * Y axis, radius 0x1000, height 0x1800) on the +0x144 list (+0x38c); +0x3a0 is built by
 * func_ov246_020d1b1c and sound 0x158 is loaded. */
struct Ov246Vec3 {
    int x;
    int y;
    int z;
};

struct Ov246Capsule {
    struct Ov246Vec3 vPos;
    struct Ov246Vec3 vUp;
    int nRadius;
    int nHeight;
};

struct Ov246Kinds { int w[8]; };

struct Ov246SubitemSlot {
    void *subitem;
    int pad;
};

extern struct Ov246Kinds data_ov246_020d30c0;
extern struct Ov246Vec3 data_02041dc8;
extern struct Ov246Vec3 data_02042264;
extern const char data_ov246_020d312c[];
extern const char data_ov246_020d3134[];
extern const char data_ov246_020d3138[];

extern void func_ov246_020cfe84(void);
extern void func_ov246_020cfecc(void);
extern void func_ov246_020cffd4(void);
extern void func_ov246_020d0360(void);
extern void func_ov246_020d0174(void);
extern void func_ov246_020d019c(void);
extern void func_ov246_020d01c4(void);
extern void func_ov246_020d03bc(void);
extern void func_ov246_020d05d0(void);
extern void func_ov246_020cff18(void);
extern void *func_ov246_020d1b1c(int *self);

extern void *func_ov107_020c9440();
extern void *func_0203b898();
extern void func_0203bfb4();
extern char *func_0203bee8();
extern void *func_ov107_020c9e50();
extern void *func_0203d15c();
extern void func_ov107_020c9074();
extern void func_ov107_020c92b0();
extern void *func_01fffca8();
extern int func_ov107_020c319c();
extern int func_ov107_020c3210(struct Ov246Capsule *req);
extern void func_0203355c();

void func_ov246_020cfc04(int param)
{
    struct Ov246Kinds kinds;
    struct Ov246Capsule req;
    int i;

    kinds = data_ov246_020d30c0;

    *(void **)(param + 0x08) = func_ov246_020cfe84;
    *(void **)(param + 0x0c) = func_ov246_020cfecc;
    *(void **)(param + 0x1c) = func_ov246_020cffd4;
    *(void **)(param + 0x30) = func_ov246_020d0360;
    *(void **)(param + 0x28) = func_ov246_020d0174;
    *(void **)(param + 0x2c) = func_ov246_020d019c;
    *(void **)(param + 0x34) = func_ov246_020d01c4;
    *(void **)(param + 0x1d0) = func_ov246_020d03bc;
    *(void **)(param + 0x1e0) = func_ov246_020d05d0;
    *(void **)(param + 0x1dc) = func_ov246_020cff18;

    *(int *)(param + 0x70) = 0x1800;
    *(int *)(param + 0x64) = 0;
    *(int *)(param + 0x68) = 0x1800;
    *(int *)(param + 0x6c) = 0;

    {
        int *self = (int *)param;

        ((void **)self)[0xe2] = func_0203b898(func_ov107_020c9440(self, 0));
        func_0203bfb4(self[0x27], ((void **)self)[0xe2]);
        ((void **)self)[0xe6] = func_0203bee8(self[0xe2], 3, data_ov246_020d312c);
        ((void **)self)[0xe5] = func_0203bee8(self[0xe2], 3, data_ov246_020d3134);
        ((void **)self)[0xe7] = func_ov107_020c9e50(func_ov107_020c9440(self, 1), data_ov246_020d3138);
        ((void **)self)[0xe4] = func_0203d15c(0x40);

        for (i = 0; i < 8; i++) {
            ((struct Ov246SubitemSlot *)((void **)self)[0xe4])[i].subitem =
                func_0203b898(func_ov107_020c9440(self, kinds.w[i]));
            func_ov107_020c9074(self,
                ((struct Ov246SubitemSlot *)((void **)self)[0xe4])[i].subitem);
            *(int *)((char *)((struct Ov246SubitemSlot *)
                ((void **)self)[0xe4])[i].subitem + 0x5c) |= 2;
        }

        func_ov107_020c92b0(self, 0, 1, 0, 0x3000);
        func_ov107_020c92b0(self, 1, 1, 0, 0x3000);
        func_ov107_020c92b0(self, 2, 1, 0, 0x3000);
        func_ov107_020c92b0(self, 4, 1, 0, 0x3000);

        ((void **)self)[0xe1] = func_01fffca8(self + 0x8b, 0x10, 100);
        *((int **)self)[0xe1] = func_ov107_020c319c(self + 0x19);

        req.vPos = data_02041dc8;
        req.vUp = data_02042264;
        req.nRadius = 0x1000;
        req.nHeight = 0x1800;
        {
            int *p = func_01fffca8(self + 0x51, 4, 100);
            self[0xe3] = *p = func_ov107_020c3210(&req);
        }
        ((void **)self)[0xe8] = func_ov246_020d1b1c(self);
        func_0203355c(0x158);
    }
}
