/* Constructor of the ov238 enemy. Installs the handlers (+8, +0xc, +0x1c message, +0x30, +0x28, +0x2c,
 * +0x34, +0x1d0 hit, +0x1dc), the +0x1fc bounds box, the +0x64 pose (scale 1.41) and bit 3 of +0x1ae;
 * builds the +0x388 rig from pose 0 (raised 0.03, owned, callback 020cfc08, subscribed to +0x9c) with
 * four bones (+0x3ec, +0x3f8, +0x3f0, +0x3f4), the +0x3e0 bone of pose 0x18 and the nine +0x404 slot
 * models (kinds of data_ov238_020d368c) attached and hidden; four distinct entries of the 12-entry
 * data_ov238_020d3674 table are drawn at random into +0x3fc; a placement at the origin with the pose
 * scale fills the +0x38c / +0x3dc handles, the +0x384 helper is created (020d2640) with flag 2 on its
 * body, and sound 0x12e loads. */
typedef void (*Callback)(void);
typedef struct { int x, y, z; } Vec3;
typedef struct { short v[12]; } Order12;
typedef struct { int id[9]; } IdTable9;
typedef struct { Vec3 min; Vec3 max; } Bounds;
typedef struct { Vec3 pos; int scale; } Placement;
struct Pair { int res; int handle; };
struct Ov238Parts { char pad[0x404]; struct Pair items[9]; };

extern void func_ov238_020d00b4(void);
extern void func_ov238_020d0104(void);
extern void func_ov238_020d0348(void);
extern void func_ov238_020d05dc(void);
extern void func_ov238_020d02f8(void);
extern void func_ov238_020d0320(void);
extern void func_ov238_020d04e0(void);
extern void func_ov238_020d0638(void);
extern void func_ov238_020d0128(void);
extern void func_ov238_020cfc08(void);
extern void *func_ov107_020c9440(char *self, int index);
extern int func_0203b898(void *item);
extern void func_0203ca14(void *srt, int x, int y, int z);
extern int func_0203bfb4(int subscriber, int item);
extern int func_0203bee8(int item, int kind, const char *name);
extern int func_ov107_020c9e50(void *item, const char *name);
extern void func_ov107_020c9074(char *self, int item);
extern int func_02023eb4(int bound);
extern int *func_01fffca8(void *pool, int elementSize, int capacity);
extern int func_ov107_020c319c(const Placement *placement);
extern int func_ov238_020d2640(char *self);
extern void func_0203355c(int resourceId);
extern const Order12 data_ov238_020d3674;
extern const IdTable9 data_ov238_020d368c;
extern const char data_ov238_020d370c[];
extern const char data_ov238_020d3718[];
extern const char data_ov238_020d3724[];
extern const char data_ov238_020d3730[];
extern const Vec3 data_02041dc8;

void func_ov238_020cfd74(char *self)
{
    Bounds bounds;
    Placement place;
    Order12 order = data_ov238_020d3674;
    IdTable9 ids = data_ov238_020d368c;
    int i;
    int count;
    int *slot;
    int node;

    bounds.min.x = -0xeea;
    bounds.min.y = 0x17;
    bounds.min.z = -0x858;
    bounds.max.x = bounds.min.x + 0x1dd3;
    bounds.max.y = bounds.min.y + 0x1c27;
    bounds.max.z = bounds.min.z + 0xd64;
    *(Callback *)(self + 0x8) = func_ov238_020d00b4;
    *(Callback *)(self + 0xc) = func_ov238_020d0104;
    *(Callback *)(self + 0x1c) = func_ov238_020d0348;
    *(Callback *)(self + 0x30) = func_ov238_020d05dc;
    *(Callback *)(self + 0x28) = func_ov238_020d02f8;
    *(Callback *)(self + 0x2c) = func_ov238_020d0320;
    *(Callback *)(self + 0x34) = func_ov238_020d04e0;
    *(Callback *)(self + 0x1d0) = func_ov238_020d0638;
    *(Callback *)(self + 0x1dc) = func_ov238_020d0128;
    *(Bounds *)(self + 0x1fc) = bounds;
    *(int *)(self + 0x70) = 0x1680;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0x1680;
    *(int *)(self + 0x6c) = 0;
    *(unsigned short *)(self + 0x100 + 0xae) |= 8;
    *(int *)(self + 0x388) = func_0203b898(func_ov107_020c9440(self, 0));
    func_0203ca14((void *)(*(int *)(self + 0x388) + 4), 0, 0x80, 0);
    *(char **)(*(int *)(self + 0x388) + 0x84) = self;
    *(Callback *)(*(int *)(self + 0x388) + 0x68) = func_ov238_020cfc08;
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x388));
    *(int *)(self + 0x3ec) = func_0203bee8(*(int *)(self + 0x388), 1, data_ov238_020d370c);
    *(int *)(self + 0x3f8) = func_0203bee8(*(int *)(self + 0x388), 3, data_ov238_020d370c);
    *(int *)(self + 0x3f0) = func_0203bee8(*(int *)(self + 0x388), 1, data_ov238_020d3718);
    *(int *)(self + 0x3f4) = func_0203bee8(*(int *)(self + 0x388), 1, data_ov238_020d3724);
    place = *(Placement *)(self + 0x64);
    place.pos = data_02041dc8;
    *(int *)(self + 0x3e0) = func_ov107_020c9e50(func_ov107_020c9440(self, 0x18), data_ov238_020d3730);
    for (i = 0; i < 9; i++) {
        ((struct Ov238Parts *)self)->items[i].res = func_0203b898(func_ov107_020c9440(self, ids.id[i]));
        func_ov107_020c9074(self, ((struct Ov238Parts *)self)->items[i].res);
        *(int *)(((struct Ov238Parts *)self)->items[i].res + 0x5c) |= 2;
    }
    count = 0;
    do {
        short k = func_02023eb4(0xc);

        if (order.v[k] != -1) {
            ((short *)(self + 0x3fc))[count] = order.v[k];
            order.v[k] = -1;
            count++;
        }
    } while (count < 4);
    *(int **)(self + 0x38c) = func_01fffca8(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x38c) = func_ov107_020c319c(&place);
    slot = func_01fffca8(self + 0x144, 4, 100);
    node = func_ov107_020c319c(&place);
    *(int *)(self + 0x3dc) = *slot = node;
    *(int *)(self + 0x384) = func_ov238_020d2640(self);
    *(int *)(*(int *)(*(int *)(self + 0x384) + 0x9c) + 0x5c) |= 4;
    func_0203355c(0x12e);
}
