/* Constructor of the ov237 enemy (and of its split partner). Installs the handlers (+8, +0xc, +0x1c
 * message, +0x20, +0x28, +0x2c, +0x30, +0x34 update, +0x48, +0x1d0 damage, +0x1dc, +0x1ec hit relay,
 * +0x1f0) and the +0x1fc bounds (-0.67 / 0.005 / -0.88 to 0.67 / 6.83 / 1.24), kind 1, bit 5 set and bit 6
 * cleared in the +0x60 high byte, bit 3 of +0x1ae, a 2.3 radius and the +0x64 pose. Builds the +0x384
 * body rig (pose 0, work list 1 at +0x388) with four bones (+0x444, +0x448, +0x44c, +0x3d4) and the
 * +0x3ac arm rig (pose 0x1a) with five joints for each arm (+0x41c, names data_ov237_020d19f8) and
 * work list 0x1b (+0x3b0) plus two bones (+0x454, +0x458); a 1/2 grab reach (+0x58); the 19 hidden
 * sub-items of data_ov237_020d1a20 in the +0x490 pair table; the 0x47 hand item (+0x3d8). Shapes: a
 * 1.25 placement (+0x488) and a unit capsule (+0x48c) on the +0x22c pool, a 0.5 placement (+0x3ec), a
 * unit capsule (+0x3f0) and ten 0.375 arm capsules (+0x3f4 / +0x408) on the +0x144 pool. Creates the
 * shot (020d0ab0, +0x3e0), the 0x3b effect rig (+0x3e4, hooked to 020cbfc4) and the spark emitter
 * (+0x3e8). The first one built also creates its partner ("Ms/40", +0x4a4, +0x4ac / +0x4b0 set), then
 * loads sound 0x12d. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef void (*Callback)(void);
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 min; Vec3 max; } Bounds;
typedef struct { Vec3 pos; int scale; } Placement;
typedef struct { Vec3 pos; Vec3 axis; int length; int radius; } Capsule;
typedef struct { const char *name[2][5]; } JointNames;
typedef struct { int id[19]; } IdTable19;
struct Pair { int res; int handle; };
struct Ov237Body { char pad[0x3f4]; int arms[2][5]; int joints[2][5]; };

extern void func_ov237_020cc788(void);
extern void func_ov237_020cc80c(void);
extern void func_ov237_020cc840(void);
extern void func_ov237_020cc8a8(void);
extern void func_ov237_020cd12c(void);
extern void func_ov237_020ccc00(void);
extern void func_ov237_020ccef0(void);
extern void func_ov237_020ccf2c(void);
extern void WM_EndKeySharing_0x020cc800(void);
extern void func_ov237_020cd1bc(void);
extern void func_ov237_020ccfe8(void);
extern void func_ov237_020ccf68(void);
extern void func_ov237_020ccfb4(void);
extern void func_ov237_020cbfc4(void);
extern void func_ov237_020cc08c(char *self);
extern void *func_ov107_020c9440(char *self, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern void func_0202a388(void *slot, int bank, void *record, int d);
extern void func_0203b9ac(int rig, void *slot);
extern int func_0203bee8(int item, int kind, const char *name);
extern int func_0203d15c(int size);
extern void func_ov107_020c9074(char *self, int item);
extern int func_ov107_020c9e50(void *item, const char *name);
extern int *func_01fffca8(void *pool, int elementSize, int capacity);
extern int func_ov107_020c3210(const Capsule *capsule);
extern int func_ov107_020c319c(const Placement *placement);
extern int func_ov237_020d0ab0(char *self);
extern int func_0203c1b0(void *record, int kind);
extern int func_ov237_020d1544(char *self);
extern void OS_SPrintf(char *buf, const char *fmt, int a);
extern int func_ov107_020c9c24(char *buf);
extern void func_ov107_020c6624(int obj, int arg);
extern void func_0203355c(int resourceId);
extern const JointNames data_ov237_020d19f8;
extern const IdTable19 data_ov237_020d1a20;
extern const char data_ov237_020d1c88[];
extern const char data_ov237_020d1c94[];
extern const char data_ov237_020d1ca0[];
extern const char data_ov237_020d1ca8[];
extern const char data_ov237_020d1cb4[];
extern const char data_ov237_020d1cbc[];
extern const char data_ov237_020d1cc4[];
extern const char data_ov237_020d1ccc[];
/* read through a const view: lets the check load hoist above the effect-rig stores (ROM order) */
extern const signed char data_ov237_020d1ce0;
extern const Vec3 data_02041dc8;
extern const Vec3 data_02042264;

void func_ov237_020cc08c(char *self)
{
    IdTable19 ids;
    JointNames names;
    Bounds bounds;
    Placement place;
    Capsule cap;
    Vec3 zero;
    Vec3 up;
    int k;
    int i;
    int *slot;

    names = data_ov237_020d19f8;
    ids = data_ov237_020d1a20;
    bounds.min.x = -0xabd;
    bounds.min.y = 0x15;
    bounds.min.z = -0xe0c;
    bounds.max.x = bounds.min.x + 0x157a;
    bounds.max.y = bounds.min.y + 0x6d37;
    bounds.max.z = bounds.min.z + 0x21ee;
    *(Callback *)(self + 0x8) = func_ov237_020cc788;
    *(Callback *)(self + 0xc) = func_ov237_020cc80c;
    *(Callback *)(self + 0x20) = func_ov237_020cc840;
    *(Callback *)(self + 0x1c) = func_ov237_020cc8a8;
    *(Callback *)(self + 0x30) = func_ov237_020cd12c;
    *(Callback *)(self + 0x34) = func_ov237_020ccc00;
    *(Callback *)(self + 0x28) = func_ov237_020ccef0;
    *(Callback *)(self + 0x2c) = func_ov237_020ccf2c;
    *(Callback *)(self + 0x48) = WM_EndKeySharing_0x020cc800;
    *(Callback *)(self + 0x1d0) = func_ov237_020cd1bc;
    *(Callback *)(self + 0x1dc) = func_ov237_020ccfe8;
    *(Bounds *)(self + 0x1fc) = bounds;
    *(u8 *)(self + 0x1c9) = 1;
    *(Callback *)(self + 0x1ec) = func_ov237_020ccf68;
    *(Callback *)(self + 0x1f0) = func_ov237_020ccfb4;
    {
        u16 hw = *(u16 *)(self + 0x60);

        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x20) << 0x18) >> 0x10);
    }
    *(u16 *)(self + 0x1ae) |= 8;
    *(int *)(self + 0x70) = 0x2500;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0x2500;
    *(int *)(self + 0x6c) = 0;
    *(u16 *)(self + 0x1ae) |= 8;
    {
        u16 hw = *(u16 *)(self + 0x60);

        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(unsigned short)((((unsigned int)hw << 0x10) >> 0x18) & ~0x40) << 0x18) >> 0x10);
    }
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(self, 0));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    func_0202a388(self + 0x388, *(int *)(*(int *)(self + 0x384) + 0x88), func_ov107_020c9440(self, 1), 0xc);
    func_0203b9ac(*(int *)(self + 0x384), self + 0x388);
    *(int *)(self + 0x444) = func_0203bee8(*(int *)(self + 0x384), 3, data_ov237_020d1c94);
    *(int *)(self + 0x448) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov237_020d1ca0);
    *(int *)(self + 0x44c) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov237_020d1ca8);
    *(int *)(self + 0x3d4) = func_0203bee8(*(int *)(self + 0x384), 3, data_ov237_020d1cb4);
    *(int *)(self + 0x3ac) = func_0203b898(func_ov107_020c9440(self, 0x1a));
    for (k = 0; k < 2; k++) {
        for (i = 0; i < 5; i++) {
            ((struct Ov237Body *)self)->joints[k][i] = func_0203bee8(*(int *)(self + 0x3ac), 1, names.name[k][i]);
        }
    }
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x3ac));
    func_0202a388(self + 0x3b0, *(int *)(*(int *)(self + 0x3ac) + 0x88), func_ov107_020c9440(self, 0x1b), 0xc);
    func_0203b9ac(*(int *)(self + 0x3ac), self + 0x3b0);
    *(int *)(self + 0x454) = func_0203bee8(*(int *)(self + 0x3ac), 3, data_ov237_020d1cbc);
    *(int *)(self + 0x458) = func_0203bee8(*(int *)(self + 0x3ac), 3, data_ov237_020d1cc4);
    *(int *)(self + 0x58) = 0x800;
    *(int *)(self + 0x490) = func_0203d15c(0x98);
    for (i = 0; i < 0x13; i++) {
        ((struct Pair *)*(int *)(self + 0x490))[i].res = func_0203b898(func_ov107_020c9440(self, ids.id[i]));
        func_ov107_020c9074(self, ((struct Pair *)*(int *)(self + 0x490))[i].res);
        *(int *)(((struct Pair *)*(int *)(self + 0x490))[i].res + 0x5c) |= 2;
    }
    *(int *)(self + 0x3d8) = func_ov107_020c9e50(func_ov107_020c9440(self, 0x47), data_ov237_020d1ccc);
    *(int *)(self + 0x4b0) = 0;
    *(int *)(self + 0x4ac) = 0;
    zero = data_02041dc8;
    place.pos = zero;
    place.scale = 0x1400;
    *(int *)(self + 0x488) = (int)func_01fffca8(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x488) = func_ov107_020c319c(&place);
    cap.pos = zero;
    up = data_02042264;
    cap.axis = up;
    cap.length = 0x1000;
    cap.radius = 0x1000;
    *(int *)(self + 0x48c) = (int)func_01fffca8(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x48c) = func_ov107_020c3210(&cap);
    place.pos = zero;
    place.scale = 0x800;
    slot = func_01fffca8(self + 0x144, 4, 100);
    *(int *)(self + 0x3ec) = *slot = func_ov107_020c319c(&place);
    cap.pos = zero;
    cap.axis = up;
    cap.length = 0x1000;
    cap.radius = 0x1000;
    slot = func_01fffca8(self + 0x144, 4, 100);
    *(int *)(self + 0x3f0) = *slot = func_ov107_020c3210(&cap);
    cap.pos = zero;
    cap.axis = up;
    cap.length = 0x1000;
    cap.radius = 0x600;
    for (i = 0; i < 5; i++) {
        slot = func_01fffca8(self + 0x144, 4, 100);
        ((struct Ov237Body *)self)->arms[0][i] = *slot = func_ov107_020c3210(&cap);
        slot = func_01fffca8(self + 0x144, 4, 100);
        ((struct Ov237Body *)self)->arms[1][i] = *slot = func_ov107_020c3210(&cap);
    }
    *(int *)(self + 0x3e0) = func_ov237_020d0ab0(self);
    *(int *)(*(int *)(*(int *)(self + 0x3e0) + 0x9c) + 0x5c) |= 4;
    *(int *)(self + 0x3e4) = func_0203c1b0(func_ov107_020c9440(self, 0x3b), 5);
    func_ov107_020c9074(self, *(int *)(self + 0x3e4));
    *(int *)(self + 0x3e8) = func_ov237_020d1544(self);
    *(Callback *)(*(int *)(self + 0x3e4) + 0x6c) = func_ov237_020cbfc4;
    *(char **)(*(int *)(self + 0x3e4) + 0x84) = self;
    *(int *)(*(int *)(self + 0x3e4) + 0x5c) |= 2;
    if (data_ov237_020d1ce0 == 0) {
        char buf[0x1d] = {0};

        *(int *)(self + 0x4b0) = 1;
        *(int *)(self + 0x4ac) = 1;
        *(signed char *)&data_ov237_020d1ce0 = 1;
        *(int *)(self + 0x4a4) = func_0203d15c(0x4d0);
        *(u8 *)(*(int *)(self + 0x4a4) + 0x19c) = 0x40;
        OS_SPrintf(buf, data_ov237_020d1c88, *(u8 *)(*(int *)(self + 0x4a4) + 0x19c));
        *(int *)(*(int *)(self + 0x4a4) + 0x1a4) = func_ov107_020c9c24(buf);
        *(void **)(*(int *)(self + 0x4a4) + 0x18c) = func_ov237_020cc08c;
        func_ov107_020c6624(*(int *)(self + 0x4a4), *(int *)(self + 0x1a0));
        *(u16 *)(*(int *)(self + 0x4a4) + 0x1ae) |= 8;
    }
    func_0203355c(0x12d);
}
