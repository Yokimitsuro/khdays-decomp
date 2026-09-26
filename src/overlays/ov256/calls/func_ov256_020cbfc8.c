/* Constructor of the ov256 enemy. Clears +0x464, installs the handlers (+8, +0xc, +0x1c message,
 * +0x30, +0x28, +0x2c, +0x34, +0x1d0 hit, +0x1dc), sets bit 6 of the +0x60 high byte, the +0x64 pose
 * (scale 2.2) and the +0x1fc bounds box; builds the +0x384 body rig (pose 0x23, animation 0x25 bound
 * at +0x388) and the +0x3ac shell rig (pose 0, animation 2 at +0x3b0), both subscribed to +0x9c; then
 * five hidden joint groups (+0x3d8/+0x3e4/+0x3f0/+0x3fc/+0x408) each holding a segment model (poses
 * 0x49-0x4d at +0x3d4/+0x3e0/+0x3ec/+0x3f8/+0x404) and two more empty groups (+0x414, +0x420); sets
 * bit 3 of +0x1ae and resolves seven bones of the two rigs; the +0x450 bone of pose 0x46; the sixteen
 * sub-items of data_ov256_020d2444 into the +0x46c pair table (attached, hidden); reserves the
 * +0x22c/+0x144 handles of a placement at the origin with the pose scale (+0x428, +0x42c); creates the
 * two +0x434 and five +0x43c helpers and clears +0x45c and +0x468.
 * Codegen: compiled with opt_common_subs off (push/pop scoped); the +0x60 update re-reads the
 * halfword instead of reusing a copy. */
typedef unsigned short u16;
typedef unsigned char u8;
typedef void (*Callback)(void);
typedef struct { int x, y, z; } Vec3;
typedef struct { int id[16]; } IdTable;
typedef struct { Vec3 min; Vec3 max; } Bounds;
typedef struct { Vec3 pos; int scale; } Placement;
struct Pair { int res; int handle; };
struct Pairs { char pad[0x46c]; struct Pair pairs[16]; };
struct Bit0 { unsigned int b0 : 1; };

extern void func_ov256_020cc53c(void);
extern void func_ov256_020cc5d4(void);
extern void func_ov256_020cc738(void);
extern void func_ov256_020ccce8(void);
extern void func_ov256_020cc680(void);
extern void func_ov256_020cc6dc(void);
extern void func_ov256_020cc95c(void);
extern void func_ov256_020cd240(void);
extern void func_ov256_020ccba4(void);
extern void *func_ov107_020c9440(char *self, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern void func_0202a388(void *dst, int a, void *b, int n);
extern void func_0203b9ac(int obj, void *block);
extern int func_0203bf44(void);
extern int func_0203bee8(int item, int kind, const char *name);
extern int func_ov107_020c9e50(void *item, const char *name);
extern void func_ov107_020c9074(char *self, int item);
extern int *func_01fffca8(void *pool, int elementSize, int capacity);
extern int func_ov107_020c319c(const Placement *placement);
extern int func_ov256_020d10b0(char *self, u8 index);
extern int func_ov256_020d0388(char *self, u8 index);
extern IdTable data_ov256_020d2444;
extern const char data_ov256_020d268c[];
extern const char data_ov256_020d2694[];
extern const char data_ov256_020d269c[];
extern const char data_ov256_020d26a4[];
extern const char data_ov256_020d26ac[];
extern const char data_ov256_020d26b4[];
extern const char data_ov256_020d26c0[];
extern const char data_ov256_020d26cc[];
extern const Vec3 data_02041dc8;

#pragma push
#pragma opt_common_subs off
void func_ov256_020cbfc8(char *self)
{
    char *binding;
    IdTable ids = data_ov256_020d2444;
    Bounds bounds;
    Placement place;
    int i;
    int node;
    int *slot;

    bounds.min.x = -0x1c7c;
    bounds.min.y = 0;
    bounds.min.z = -0xa44;
    bounds.max.x = bounds.min.x + 0x38f9;
    bounds.max.y = bounds.min.y + 0x20a8;
    bounds.max.z = bounds.min.z;
    bounds.max.z += 0x107a;
    *(int *)(self + 0x464) = 0;
    *(Callback *)(self + 0x8) = func_ov256_020cc53c;
    *(Callback *)(self + 0xc) = func_ov256_020cc5d4;
    *(Callback *)(self + 0x1c) = func_ov256_020cc738;
    *(Callback *)(self + 0x30) = func_ov256_020ccce8;
    *(Callback *)(self + 0x28) = func_ov256_020cc680;
    *(Callback *)(self + 0x2c) = func_ov256_020cc6dc;
    *(Callback *)(self + 0x34) = func_ov256_020cc95c;
    *(Callback *)(self + 0x1d0) = func_ov256_020cd240;
    *(Callback *)(self + 0x1dc) = func_ov256_020ccba4;
    *(u16 *)(self + 0x60) = (*(u16 *)(self + 0x60) & ~0xff00) |
        ((((((unsigned int)*(u16 *)(self + 0x60) << 0x10) >> 0x18) | 0x40) << 0x18) >> 0x10);
    *(int *)(self + 0x70) = 0x2300;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0x2300;
    *(int *)(self + 0x6c) = 0;
    *(Bounds *)(self + 0x1fc) = bounds;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(self, 0x23));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    {
        void *anim = func_ov107_020c9440(self, 0x25);

        binding = self + 0x388;
        func_0202a388(binding, *(int *)(*(int *)(self + 0x384) + 0x88), anim, 0xc);
    }
    func_0203b9ac(*(int *)(self + 0x384), binding);
    *(int *)(self + 0x3ac) = func_0203b898(func_ov107_020c9440(self, 0));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x3ac));
    {
        void *anim = func_ov107_020c9440(self, 2);

        func_0202a388(self + 0x3b0, *(int *)(*(int *)(self + 0x3ac) + 0x88), anim, 0xc);
    }
    func_0203b9ac(*(int *)(self + 0x3ac), self + 0x3b0);
    *(int *)(self + 0x3d8) = func_0203bf44();
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x3d8));
    ((struct Bit0 *)(*(int *)(self + 0x3d8) + 0x5c))->b0 = 1;
    *(int *)(self + 0x3d4) = func_0203b898(func_ov107_020c9440(self, 0x49));
    func_0203bfb4(*(int *)(self + 0x3d8), *(int *)(self + 0x3d4));
    *(int *)(self + 0x3e4) = func_0203bf44();
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x3e4));
    ((struct Bit0 *)(*(int *)(self + 0x3e4) + 0x5c))->b0 = 1;
    *(int *)(self + 0x3e0) = func_0203b898(func_ov107_020c9440(self, 0x4a));
    func_0203bfb4(*(int *)(self + 0x3e4), *(int *)(self + 0x3e0));
    *(int *)(self + 0x3f0) = func_0203bf44();
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x3f0));
    ((struct Bit0 *)(*(int *)(self + 0x3f0) + 0x5c))->b0 = 1;
    *(int *)(self + 0x3ec) = func_0203b898(func_ov107_020c9440(self, 0x4b));
    func_0203bfb4(*(int *)(self + 0x3f0), *(int *)(self + 0x3ec));
    *(int *)(self + 0x3fc) = func_0203bf44();
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x3fc));
    ((struct Bit0 *)(*(int *)(self + 0x3fc) + 0x5c))->b0 = 1;
    *(int *)(self + 0x3f8) = func_0203b898(func_ov107_020c9440(self, 0x4c));
    func_0203bfb4(*(int *)(self + 0x3fc), *(int *)(self + 0x3f8));
    *(int *)(self + 0x408) = func_0203bf44();
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x408));
    ((struct Bit0 *)(*(int *)(self + 0x408) + 0x5c))->b0 = 1;
    *(int *)(self + 0x404) = func_0203b898(func_ov107_020c9440(self, 0x4d));
    func_0203bfb4(*(int *)(self + 0x408), *(int *)(self + 0x404));
    *(int *)(self + 0x414) = func_0203bf44();
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x414));
    ((struct Bit0 *)(*(int *)(self + 0x414) + 0x5c))->b0 = 1;
    *(int *)(self + 0x420) = func_0203bf44();
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x420));
    ((struct Bit0 *)(*(int *)(self + 0x420) + 0x5c))->b0 = 1;
    *(u16 *)(self + 0x100 + 0xae) |= 8;
    *(int *)(self + 0x3dc) = func_0203bee8(*(int *)(self + 0x384), 3, data_ov256_020d268c);
    *(int *)(self + 0x3e8) = func_0203bee8(*(int *)(self + 0x384), 3, data_ov256_020d2694);
    *(int *)(self + 0x3f4) = func_0203bee8(*(int *)(self + 0x3ac), 3, data_ov256_020d269c);
    *(int *)(self + 0x400) = func_0203bee8(*(int *)(self + 0x3ac), 3, data_ov256_020d26a4);
    *(int *)(self + 0x40c) = func_0203bee8(*(int *)(self + 0x3ac), 3, data_ov256_020d26ac);
    *(int *)(self + 0x418) = func_0203bee8(*(int *)(self + 0x384), 3, data_ov256_020d26b4);
    *(int *)(self + 0x424) = func_0203bee8(*(int *)(self + 0x384), 3, data_ov256_020d26c0);
    place = *(Placement *)(self + 0x64);
    place.pos = data_02041dc8;
    *(int *)(self + 0x450) = func_ov107_020c9e50(func_ov107_020c9440(self, 0x46), data_ov256_020d26cc);
    for (i = 0; i < 16; i++) {
        node = func_0203b898(func_ov107_020c9440(self, ids.id[i]));
        func_ov107_020c9074(self, ((struct Pairs *)self)->pairs[i].res = node);
        *(int *)(((struct Pairs *)self)->pairs[i].res + 0x5c) |= 2;
    }
    *(int **)(self + 0x428) = func_01fffca8(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x428) = func_ov107_020c319c(&place);
    slot = func_01fffca8(self + 0x144, 4, 100);
    node = func_ov107_020c319c(&place);
    *(int *)(self + 0x42c) = *slot = node;
    for (i = 0; i < 2; i++) {
        ((int *)(self + 0x434))[i] = func_ov256_020d10b0(self, i);
    }
    for (i = 0; i < 5; i++) {
        ((int *)(self + 0x43c))[i] = func_ov256_020d0388(self, i);
    }
    *(int *)(self + 0x45c) = 0;
    *(int *)(self + 0x468) = 0;
}
#pragma pop
