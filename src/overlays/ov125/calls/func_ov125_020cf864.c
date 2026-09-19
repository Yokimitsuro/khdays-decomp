/* func_ov125_020cf864: sub-item constructor of the ov125 enemy (four handlers, speed 0x200,
 * capsule 0x1000/0x200 on the data_02041dc8 / data_02042240 axes). */
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct { int x, y, z; } Vec3;

typedef struct {
    Vec3 vPos;
    Vec3 vUp;
    int nRadius;
    int nHeight;
} Capsule;

typedef struct {
    int value;
    int pad_0004;
    u32 flags : 8;
} Ov125PoolEntry;

typedef struct {
    char pad_0000[0x08];
    void (*callback_0008)(void);
    void (*callback_000c)(void);
    char pad_0010[0x20];
    void (*callback_0030)(void);
    char pad_0034[0x2c];
    u16 flags_0060;
    char pad_0062[0x0e];
    int field_0070;
    char pad_0074[0x28];
    void *subscriber_009c;
    char pad_00a0[0x10e];
    u16 flags_01ae;
    char pad_01b0[0x20];
    void (*callback_01d0)(void);
    char pad_01d4[0x58];
    char pool_022c[0x158];
    void *subitem_0384;
    Ov125PoolEntry *poolEntry_0388;
    int owner_038c;
} Ov125Object;

extern void *func_ov107_020c9440(int owner, int index);
extern void *func_0203b898(void *item);
extern void func_0203bfb4(void *subscriber, void *item);
extern void func_0203b9fc(void *item, int state, int zero, int enabled);
extern void func_0203c7ac(void *item, int value);
extern Ov125PoolEntry *func_01fffca8(void *pool, int elementSize, int capacity);
extern int func_ov107_020c3210(Capsule *req);
extern void func_ov125_020cf9a0(void);
extern void func_ov125_020cf9bc(void);
extern void func_ov125_020cfa50(void);
extern void func_ov125_020cf9f4(void);
extern const Vec3 data_02041dc8;
extern const Vec3 data_02042240;

void func_ov125_020cf864(Ov125Object *self) {
    Capsule req;
    u16 v;

    self->callback_0008 = func_ov125_020cf9a0;
    self->callback_000c = func_ov125_020cf9bc;
    self->callback_0030 = func_ov125_020cfa50;
    self->callback_01d0 = func_ov125_020cf9f4;
    self->field_0070 = 0x200;
    self->flags_01ae |= 0x14;
    v = self->flags_0060;
    self->flags_0060 =
        (u16)((v & ~0xff00) | (((((u32)v << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10));
    self->subitem_0384 = func_0203b898(func_ov107_020c9440(self->owner_038c, 2));
    func_0203bfb4(self->subscriber_009c, self->subitem_0384);
    func_0203b9fc(self->subitem_0384, 0, 0, 1);
    func_0203c7ac(self->subitem_0384, 0);
    req.vPos = data_02041dc8;
    req.vUp = data_02042240;
    req.nRadius = 0x1000;
    req.nHeight = 0x200;
    self->poolEntry_0388 = func_01fffca8(self->pool_022c, 0x10, 100);
    self->poolEntry_0388->value = func_ov107_020c3210(&req);
    self->poolEntry_0388->flags |= 2;
}
