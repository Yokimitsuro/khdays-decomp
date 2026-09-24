/* Constructor of the ov254 boss. Installs the handlers (+8, +0xc, +0x28, +0x2c, +0x1c message, +0x30,
 * +0x34, +0x48, +0x1d0 hit, +0x1dc), the +0x1fc bounds box, kind 4, the +0x64 pose (scale 6.65) and
 * the +0x60 high bits 5-7 / +0x1ae bit 3. Builds the +0x384 body (pose 0, animation 1 at +0x38c,
 * bones +0x408 / +0x428 / +0x42c) and the +0x388 upper rig (pose 0x1f, animation 0x20 at +0x3b0,
 * seven bones +0x40c..+0x424), the +0x434 list of nine ground anchor points, the +0x430 bone of pose
 * 0x3e and the eight +0x4e8 sub-items of data_ov254_020d592c (attached, hidden). Five colliders are
 * placed at the origin: spheres of radius 7.0, 4.2 and 1/256 and two capsules along the forward axis
 * (length 8.4, radius 1.57); each goes both into the +0x144 pool (kept in +0x3f4) and the +0x22c pool
 * (kept in +0x3e0). The four helpers (+0x468, +0x45c, +0x460, +0x464), sixteen +0x46c shards and ten
 * +0x4ac debris pieces are created and sound 0x16d loads. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef void (*Callback)(void);
typedef struct { int x, y, z; } Vec3;
typedef struct { int id[8]; } IdTable8;
typedef struct { int w[6]; } Bounds;
typedef struct { Vec3 pos; int nRadius; } Sphere;
typedef struct { Vec3 p0; Vec3 dir; int nLength; int nRadius; } Segment;
struct Pair { int res; int handle; };
struct Ov254 {
    char pad000[0x3e0];
    int *bodyShapes[5];     /* +0x3e0 */
    int bodyNodes[5];       /* +0x3f4 */
    char pad408[0x46c - 0x408];
    int shards[16];         /* +0x46c */
    int debris[10];         /* +0x4ac */
    char pad4d4[0x4e8 - 0x4d4];
    struct Pair items[8];   /* +0x4e8 */
};

extern void func_ov254_020cc640(void);
extern void func_ov254_020cc6a4(void);
extern void func_ov254_020cc6c8(void);
extern void func_ov254_020cc754(void);
extern void func_ov254_020cc7e0(void);
extern void func_ov254_020ccf78(void);
extern void func_ov254_020cc994(void);
extern void func_ov254_020ccd18(void);
extern void func_ov254_020cd984(void);
extern void func_ov254_020cccc8(void);
extern void *func_ov107_020c9440(char *self, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern void func_0202a388(void *dst, int a, void *b, int n);
extern void func_0203b9ac(int obj, void *block);
extern int func_0203bee8(int item, int kind, const char *name);
extern void func_01fffc24(void *pool);
extern int *func_01fffca8(void *pool, int elementSize, int capacity);
extern int func_ov107_020c9e50(void *item, const char *name);
extern void func_ov107_020c9074(char *self, int item);
extern int func_ov107_020c3210(Segment *seg);
extern int func_ov107_020c319c(Sphere *sphere);
extern int func_ov254_020d41b8(char *self);
extern int func_ov254_020d2088(char *self);
extern int func_ov254_020d4d6c(char *self);
extern int func_ov254_020d5348(char *self);
extern int func_ov254_020d18f0(char *self);
extern int func_ov254_020d2b0c(char *self);
extern void func_0203355c(int resourceId);
extern IdTable8 data_ov254_020d592c;
extern Bounds data_ov254_020d5914;
extern const char data_ov254_020d598c[];
extern const char data_ov254_020d5994[];
extern const char data_ov254_020d5998[];
extern const char data_ov254_020d599c[];
extern const char data_ov254_020d59a4[];
extern const char data_ov254_020d59ac[];
extern const char data_ov254_020d59b8[];
extern const char data_ov254_020d59c4[];
extern const char data_ov254_020d59d0[];
extern const char data_ov254_020d59dc[];
extern const Vec3 data_02041dc8;
extern const Vec3 data_02042258;

static inline void SetAnchor(char *self, int x, int z)
{
    int *p = func_01fffca8(self + 0x434, 0xc, 100);

    p[0] = x;
    p[1] = 0;
    p[2] = z;
}

void func_ov254_020cbfc8(char *self)
{
    IdTable8 ids = data_ov254_020d592c;
    Sphere sph;
    Segment seg;
    Vec3 zero;
    int i;
    int *slot;
    int capsule;
    int k;
    int node;

    *(Callback *)(self + 0x8) = func_ov254_020cc640;
    *(Callback *)(self + 0xc) = func_ov254_020cc6a4;
    *(Callback *)(self + 0x28) = func_ov254_020cc6c8;
    *(Callback *)(self + 0x2c) = func_ov254_020cc754;
    *(Callback *)(self + 0x1c) = func_ov254_020cc7e0;
    *(Callback *)(self + 0x30) = func_ov254_020ccf78;
    *(Callback *)(self + 0x34) = func_ov254_020cc994;
    *(Callback *)(self + 0x48) = func_ov254_020ccd18;
    *(Callback *)(self + 0x1d0) = func_ov254_020cd984;
    *(Callback *)(self + 0x1dc) = func_ov254_020cccc8;
    *(Bounds *)(self + 0x1fc) = data_ov254_020d5914;
    *(u8 *)(self + 0x1c9) = 4;
    *(int *)(self + 0x70) = 0x1000;
    *(int *)(self + 0x70) = 0x6a65;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0;
    *(int *)(self + 0x6c) = 0;
    {
        u16 hw = *(u16 *)(self + 0x60);

        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0xe0) << 0x18) >> 0x10);
    }
    *(u16 *)(self + 0x100 + 0xae) |= 8;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(self, 0));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    func_0202a388(self + 0x38c, *(int *)(*(int *)(self + 0x384) + 0x88), func_ov107_020c9440(self, 1), 0xc);
    func_0203b9ac(*(int *)(self + 0x384), self + 0x38c);
    *(int *)(self + 0x408) = func_0203bee8(*(int *)(self + 0x384), 3, data_ov254_020d598c);
    *(int *)(self + 0x428) = func_0203bee8(*(int *)(self + 0x384), 3, data_ov254_020d5994);
    *(int *)(self + 0x42c) = func_0203bee8(*(int *)(self + 0x384), 3, data_ov254_020d5998);
    *(int *)(self + 0x388) = func_0203b898(func_ov107_020c9440(self, 0x1f));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x388));
    func_0202a388(self + 0x3b0, *(int *)(*(int *)(self + 0x388) + 0x88), func_ov107_020c9440(self, 0x20), 0xc);
    func_0203b9ac(*(int *)(self + 0x388), self + 0x3b0);
    *(int *)(self + 0x40c) = func_0203bee8(*(int *)(self + 0x388), 1, data_ov254_020d599c);
    *(int *)(self + 0x410) = func_0203bee8(*(int *)(self + 0x388), 3, data_ov254_020d599c);
    *(int *)(self + 0x414) = func_0203bee8(*(int *)(self + 0x388), 3, data_ov254_020d59a4);
    *(int *)(self + 0x418) = func_0203bee8(*(int *)(self + 0x388), 1, data_ov254_020d59ac);
    *(int *)(self + 0x41c) = func_0203bee8(*(int *)(self + 0x388), 1, data_ov254_020d59b8);
    *(int *)(self + 0x420) = func_0203bee8(*(int *)(self + 0x388), 1, data_ov254_020d59c4);
    *(int *)(self + 0x424) = func_0203bee8(*(int *)(self + 0x388), 1, data_ov254_020d59d0);
    func_01fffc24(self + 0x434);
    SetAnchor(self, -0x16000, -0xd000);
    SetAnchor(self, 0x9000, 0x4000);
    SetAnchor(self, 0x16000, 0x21000);
    SetAnchor(self, 0x5000, 0x2d000);
    SetAnchor(self, -0x2000, 0x32000);
    SetAnchor(self, -0x1b000, 0x2e000);
    SetAnchor(self, -0x28000, 0x2b000);
    SetAnchor(self, -0x24000, 0xe000);
    SetAnchor(self, -0x24000, 0);
    *(int *)(self + 0x430) = func_ov107_020c9e50(func_ov107_020c9440(self, 0x3e), data_ov254_020d59dc);
    for (i = 0; i < 8; i++) {
        ((struct Ov254 *)self)->items[i].res = func_0203b898(func_ov107_020c9440(self, ids.id[i]));
        func_ov107_020c9074(self, ((struct Ov254 *)self)->items[i].res);
        *(int *)(((struct Ov254 *)self)->items[i].res + 0x5c) |= 2;
    }
    zero = data_02041dc8;
    sph.pos = zero;
    seg.p0 = zero;
    sph.nRadius = 0x7b31;
    seg.dir = data_02042258;
    seg.nLength = 0x8664;
    seg.nRadius = 0x1933;
    for (k = 0; k < 5; k++) {
        capsule = 0;
        switch (k) {
        case 0:
            sph.nRadius = 0x6ffe;
            break;
        case 4:
            sph.nRadius = 0x10;
            break;
        case 1:
            sph.nRadius = 0x8664 >> 1;
            break;
        case 2:
            capsule = 1;
            break;
        case 3:
            capsule = 1;
            break;
        }
        slot = func_01fffca8(self + 0x144, 4, 100);
        if (capsule != 0) {
            node = func_ov107_020c3210(&seg);
        } else {
            node = func_ov107_020c319c(&sph);
        }
        *slot = node;
        ((struct Ov254 *)self)->bodyNodes[k] = node;
        ((struct Ov254 *)self)->bodyShapes[k] = func_01fffca8(self + 0x22c, 0x10, 100);
        if (capsule != 0) {
            *((struct Ov254 *)self)->bodyShapes[k] = func_ov107_020c3210(&seg);
        } else {
            *((struct Ov254 *)self)->bodyShapes[k] = func_ov107_020c319c(&sph);
        }
    }
    *(int *)(self + 0x468) = func_ov254_020d41b8(self);
    *(int *)(self + 0x45c) = func_ov254_020d2088(self);
    *(int *)(self + 0x460) = func_ov254_020d4d6c(self);
    *(int *)(self + 0x464) = func_ov254_020d5348(self);
    for (i = 0; i < 16; i++) {
        ((struct Ov254 *)self)->shards[i] = func_ov254_020d18f0(self);
    }
    for (i = 0; i < 10; i++) {
        ((struct Ov254 *)self)->debris[i] = func_ov254_020d2b0c(self);
    }
    func_0203355c(0x16d);
}
