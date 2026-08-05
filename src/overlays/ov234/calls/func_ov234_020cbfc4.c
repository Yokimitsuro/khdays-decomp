typedef unsigned short u16;
typedef unsigned char u8;

struct Ov234Vec3 {
    int x;
    int y;
    int z;
};

struct Ov234Box {
    struct Ov234Vec3 min;
    struct Ov234Vec3 max;
};

struct Ov234Work {
    struct Ov234Vec3 vec;
    int scale;
};

struct Ov234TextureTable {
    int offsets[1];
};

struct Ov234InitFrame {
    volatile int textureScratch;
    struct Ov234Box box;
};

struct Ov234Actor {
    char pad000[0x08];
    void (*fn008)(void);
    void (*fn00c)(void);
    char pad010[0x0c];
    void (*fn01c)(void);
    char pad020[0x08];
    void (*fn028)(void);
    void (*fn02c)(void);
    void (*fn030)(void);
    char pad034[0x2c];
    u16 flags060;
    char pad062[0x02];
    int camera[4];
    char pad074[0x28];
    void *resource09c;
    char pad0a0[0xa4];
    char pool144[0x6a];
    u16 flags1ae;
    char pad1b0[0x19];
    u8 state1c9;
    char pad1ca[0x06];
    void (*fn1d0)(void);
    char pad1d4[0x08];
    void (*fn1dc)(void);
    char pad1e0[0x1c];
    struct Ov234Box box1fc;
    char pad214[0x18];
    char pool22c[0x158];
    char *handle384;
    int *slot388;
    int handle38c;
    char pad390[0x04];
    char work394[0x24];
    int value3b8;
    char *handle3bc;
};

extern void func_ov234_020cc1d8(void);
extern void func_ov234_020cc1fc(void);
extern void func_ov234_020cc274(void);
extern void func_ov234_020cc4e0(void);
extern void func_ov234_020cc518(void);
extern void func_ov234_020cc574(void);
extern void WM_EndKeySharing_0x020cc25c(void);
extern void WM_EndKeySharing_0x020cc268(void);

extern const struct Ov234TextureTable data_ov234_020cd100;
extern unsigned func_ov107_020c9440();
extern char *func_0203b898(unsigned);
extern void func_0203bfb4(void *, char *);
extern void func_0203b9ac(char *, void *);
extern void func_0203ca14(void *, int, int, int);
extern void func_0203ca9c(void *, int);
extern void func_ov107_020c9074(struct Ov234Actor *, int);
extern int *func_01fffca8(void *, int, int);
extern int func_ov107_020c319c(void *);
extern int func_0203355c(int);

int func_ov234_020cbfc4(struct Ov234Actor *arg0)
{
    struct Ov234Actor *self;
    int minY = 0x17;
    int minX = 0xfffff116;
    int minZ = 0xfffff7a8;
    struct Ov234TextureTable textureTable = data_ov234_020cd100;
    struct Ov234Work work;
    struct Ov234Box box;
    int *slot;

#pragma opt_dead_assignments off
    box.min.x = 1;
#pragma opt_dead_assignments on
    self = arg0;

    box.min.x = minX;
    box.min.y = minY;
    box.min.z = minZ;
    box.max.x = box.min.x + 0x1dd3;
    box.max.y = box.min.y + 0x1c27;
    box.max.z = box.min.z + 0xd64;

    self->fn008 = func_ov234_020cc1d8;
    self->fn00c = func_ov234_020cc1fc;
    self->fn01c = func_ov234_020cc274;
    self->fn030 = func_ov234_020cc518;
    self->fn028 = WM_EndKeySharing_0x020cc25c;
    self->fn02c = WM_EndKeySharing_0x020cc268;
    self->fn1d0 = func_ov234_020cc574;
    self->fn1dc = func_ov234_020cc4e0;

    self->state1c9 = 2;
    self->flags1ae |= 4;
    {
        unsigned value = self->flags060;
        self->flags060 = (u16)((value & ~0xff00) |
            (((((value << 0x10) >> 0x18) | 0xa0) << 0x18) >> 0x10));
    }

    {
        self->camera[3] = 0x700;
        self->box1fc = box;

        self->handle384 =
            func_0203b898(func_ov107_020c9440(self, 0));
        func_0203bfb4(self->resource09c, self->handle384);
        func_0203b9ac(self->handle384, self->work394);
        func_0203ca14(self->handle384 + 4, 0, 0x380, 0);
        func_0203ca9c((char *)self + 0xa0, 0xccd);

        self->handle3bc = func_0203b898(
            func_ov107_020c9440(self, textureTable.offsets[0]));
        func_ov107_020c9074(self, (int)self->handle3bc);
        *(int *)(self->handle3bc + 0x5c) |= 2;
    }

    work.vec.x = 0;
    work.vec.y = 0;
    work.vec.z = 0;
    work.scale = 0x1200;

    self->slot388 = func_01fffca8(self->pool22c, 0x10, 0x64);
    *self->slot388 = func_ov107_020c319c(&work);

    slot = func_01fffca8(self->pool144, 4, 0x64);
    *slot = func_ov107_020c319c(&self->camera[0]);
    self->handle38c = *slot;

    self->value3b8 = 0;
    return func_0203355c(0x178);
}
