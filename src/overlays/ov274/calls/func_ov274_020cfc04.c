/* Constructor of the ov274 enemy (and its byte-identical twins): installs the handlers (+8
 * 020d0080, +0xc draw 020d00d8, +0x1c message 020d0330, +0x30 020d0ce8, +0x2c 020d0444, +0x34
 * tick 020d05f4, +0x1d0 on-hit 020d0d34, +0x1e0 release 020d105c, +0x1dc finish 020d0508),
 * seeds the +0x64 pose (scale 0x1d00, y 0x1d00) and bit 3 of +0x1ae, builds the primary item
 * from pool entry 0 (subscribed), attaches pool entry 1's animation to its +0x88 track through
 * the +0x388 block (0202a388 / b9ac, finalised), resolves six named joints (+0x3c8 / +0x3cc /
 * +0x3d0 / +0x3dc mode 1, +0x3d4 / +0x3d8 mode 3), the five sub-items of the
 * data_ov274_020d4194 kinds in a fresh 40-byte slot table (+0x3e0, attached, bit 1 on their
 * +0x5c), configures actions 0/2/1/4 (modes 2/3/2/2, the second with a (0, -0x1d00, 0) offset,
 * rates 0x1000 / 0x99a / 0xccd / 0x1000), keeps pool entry 0x14's data_ov274_020d431c motion
 * handle (+0x3b4), and creates from the zero position: a 0.5 placement on the +0x22c list
 * (+0x3ac), a capsule (world Y axis, radius 1.0, height 0x1333) on the +0x22c list with 110
 * slots (+0x3b0), a capsule of height 0x1050 on the +0x144 list (+0x3b8) and placements of
 * scale 0xccc there (three) (+0x3bc / +0x3c0 / +0x3c4); sound 0x163 is loaded. */
struct Ov274Vec3 {
    int x;
    int y;
    int z;
};

struct Ov274Pose {
    struct Ov274Vec3 position;
    int scale;
};

struct Ov274Capsule {
    struct Ov274Vec3 vPos;
    struct Ov274Vec3 vUp;
    int nRadius;
    int nHeight;
};

struct Ov274Kinds { int w[5]; };

struct Ov274SubitemSlot {
    void *subitem;
    int pad;
};

extern struct Ov274Kinds data_ov274_020d4194;
extern struct Ov274Vec3 data_02041dc8;
extern struct Ov274Vec3 data_02042264;
extern const char data_ov274_020d42cc[];
extern const char data_ov274_020d42d8[];
extern const char data_ov274_020d42e8[];
extern const char data_ov274_020d42f8[];
extern const char data_ov274_020d4300[];
extern const char data_ov274_020d4310[];
extern const char data_ov274_020d431c[];

extern void func_ov274_020d0080(void);
extern void func_ov274_020d00d8(void);
extern void func_ov274_020d0330(void);
extern void func_ov274_020d0ce8(void);
extern void func_ov274_020d0444(void);
extern void func_ov274_020d05f4(void);
extern void func_ov274_020d0d34(void);
extern void func_ov274_020d105c(void);
extern void func_ov274_020d0508(void);

extern void *func_ov107_020c9440();
extern void *func_0203b898();
extern void func_0203bfb4();
extern void func_0202a388();
extern void func_0203b9ac();
extern void func_0203c7ac();
extern char *func_0203bee8();
extern void *func_ov107_020c9e50();
extern void *func_0203d15c();
extern void func_ov107_020c9074();
extern void func_ov107_020c92b0();
extern void *func_01fffca8();
extern int func_ov107_020c319c();
extern int func_ov107_020c3210(struct Ov274Capsule *req);
extern void func_0203355c();

void func_ov274_020cfc04(int param)
{
    struct Ov274Kinds kinds;
    struct Ov274Pose pose;
    struct Ov274Capsule capsule;
    struct Ov274Vec3 offset;
    struct Ov274Vec3 base;
    struct Ov274Vec3 axis;
    int i;

    kinds = data_ov274_020d4194;

    *(void **)(param + 0x08) = func_ov274_020d0080;
    *(void **)(param + 0x0c) = func_ov274_020d00d8;
    *(void **)(param + 0x1c) = func_ov274_020d0330;
    *(void **)(param + 0x30) = func_ov274_020d0ce8;
    *(void **)(param + 0x2c) = func_ov274_020d0444;
    *(void **)(param + 0x34) = func_ov274_020d05f4;
    *(void **)(param + 0x1d0) = func_ov274_020d0d34;
    *(void **)(param + 0x1e0) = func_ov274_020d105c;
    *(void **)(param + 0x1dc) = func_ov274_020d0508;

    *(int *)(param + 0x70) = 0x1d00;
    *(int *)(param + 0x64) = 0;
    *(int *)(param + 0x68) = 0x1d00;
    *(int *)(param + 0x6c) = 0;
    *(unsigned short *)(param + 0x100 + 0xae) |= 8;

    {
        int *self = (int *)param;

        ((void **)self)[0xe1] = func_0203b898(func_ov107_020c9440(self, 0));
        func_0203bfb4(self[0x27], ((void **)self)[0xe1]);
        func_0202a388(self + 0xe2, *(int *)(self[0xe1] + 0x88), func_ov107_020c9440(self, 1), 0xc);
        func_0203b9ac(self[0xe1], self + 0xe2);
        func_0203c7ac(self[0xe1], 0);
        ((void **)self)[0xf2] = func_0203bee8(self[0xe1], 1, data_ov274_020d42cc);
        ((void **)self)[0xf3] = func_0203bee8(self[0xe1], 1, data_ov274_020d42d8);
        ((void **)self)[0xf4] = func_0203bee8(self[0xe1], 1, data_ov274_020d42e8);
        ((void **)self)[0xf5] = func_0203bee8(self[0xe1], 3, data_ov274_020d42f8);
        ((void **)self)[0xf7] = func_0203bee8(self[0xe1], 1, data_ov274_020d4300);
        ((void **)self)[0xf6] = func_0203bee8(self[0xe1], 3, data_ov274_020d4310);
        ((void **)self)[0xf8] = func_0203d15c(0x28);

        for (i = 0; i < 5; i++) {
            ((struct Ov274SubitemSlot *)((void **)self)[0xf8])[i].subitem =
                func_0203b898(func_ov107_020c9440(self, kinds.w[i]));
            func_ov107_020c9074(self,
                ((struct Ov274SubitemSlot *)((void **)self)[0xf8])[i].subitem);
            *(int *)((char *)((struct Ov274SubitemSlot *)
                ((void **)self)[0xf8])[i].subitem + 0x5c) |= 2;
        }

        offset.x = 0;
        offset.y = -0x1d00;
        offset.z = 0;
        func_ov107_020c92b0(self, 0, 2, 0, 0x1000);
        func_ov107_020c92b0(self, 2, 3, &offset, 0x99a);
        func_ov107_020c92b0(self, 1, 2, 0, 0xccd);
        func_ov107_020c92b0(self, 4, 2, 0, 0x1000);

        ((void **)self)[0xed] = func_ov107_020c9e50(func_ov107_020c9440(self, 0x14), data_ov274_020d431c);

        base = data_02041dc8;
        pose.position = base;
        pose.scale = 0x800;
        ((void **)self)[0xeb] = func_01fffca8(self + 0x8b, 0x10, 100);
        *((int **)self)[0xeb] = func_ov107_020c319c(&pose);

        capsule.vPos = base;
        axis = data_02042264;
        capsule.vUp = axis;
        capsule.nRadius = 0x1000;
        capsule.nHeight = 0x1333;
        ((void **)self)[0xec] = func_01fffca8(self + 0x8b, 0x10, 110);
        *((int **)self)[0xec] = func_ov107_020c3210(&capsule);

        capsule.vPos = base;
        capsule.vUp = axis;
        capsule.nRadius = 0x1000;
        capsule.nHeight = 0x1050;
        {
            int *p = func_01fffca8(self + 0x51, 4, 100);
            self[0xee] = *p = func_ov107_020c3210(&capsule);
        }
        pose.position = base;
        pose.scale = 0xccc;
        {
            int *p = func_01fffca8(self + 0x51, 4, 100);
            self[0xef] = *p = func_ov107_020c319c(&pose);
        }
        pose.position = base;
        pose.scale = 0xccc;
        {
            int *p = func_01fffca8(self + 0x51, 4, 100);
            self[0xf0] = *p = func_ov107_020c319c(&pose);
        }
        pose.position = base;
        pose.scale = 0xccc;
        {
            int *p = func_01fffca8(self + 0x51, 4, 100);
            self[0xf1] = *p = func_ov107_020c319c(&pose);
        }
        func_0203355c(0x163);
    }
}
