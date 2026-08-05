typedef unsigned short u16;

struct Vec3 { int x, y, z; };
struct Box { struct Vec3 min, max; };

struct Subitem {
    char pad00[0x5c];
    unsigned int flags5c;
    char pad60[0x0c];
    void (*callback6c)(void);
    char pad70[0x04];
    void (*callback74)(void);
    char pad78[0x0c];
    void *owner84;
};

struct Obj {
    char pad00[0x08];
    void (*fn08)(void);
    void (*fn0c)(void);
    char pad10[0x0c];
    void (*fn1c)(void);
    char pad20[0x08];
    void (*fn28)(void);
    void (*fn2c)(void);
    void (*fn30)(void);
    void (*fn34)(void);
    char pad38[0x28];
    u16 flags60;
    char pad62[0x02];
    int camera[4];
    char pad74[0x28];
    void *subscriberList9c;
    char padA0[0xa4];
    char pool144[0x8c];
    void (*fn1d0)(void);
    char pad1d4[0x08];
    void (*fn1dc)(void);
    void (*fn1e0)(void);
    void (*fn1e4)(void);
    char pad1e8[0x14];
    struct Box box;
    char pad214[0x18];
    char pool22c[0x158];
    struct Subitem *subitem384;
    struct Subitem *subitem388;
    int *poolEntry38c;
    int poolValue390;
    char pad394[0x04];
    int child398[3];
    char pad3a4[0x18];
    int angle3bc;
    int quaternion3c0[4];
    int resourceId3d0;
    int resourceId3d4;
    char pad3d8[0x18];
    struct Subitem *subitem3f0;
};

extern void func_ov148_020d0094(void);
extern void func_ov148_020d00c0(void);
extern void func_ov148_020d0288(void);
extern void func_ov148_020d03e4(void);
extern void func_ov148_020d0140(void);
extern void func_ov148_020d017c(void);
extern void func_ov148_020d01b8(void);
extern void func_ov148_020d0440(void);
extern void func_ov148_020d03ac(void);
extern void func_ov148_020d05a4(void);
extern void func_ov148_020d05d0(void);
extern void func_ov148_020cfc04(void);
extern void func_ov148_020cfc4c(void);
extern int func_ov148_020d1940(struct Obj *self);

extern char data_ov148_020d250c[];
extern char data_ov148_020d2514[];
extern struct Vec3 data_02042264;

extern void *func_ov107_020c9440(struct Obj *self, int index);
extern struct Subitem *func_0203b898(void *item);
extern void func_0203bfb4(void *list, struct Subitem *item);
extern int func_0203bdfc(struct Subitem *item, char *name);
extern void func_0203c7ac(struct Subitem *item, int value);
extern void func_0202f188(int *out, struct Vec3 *axis, int angle);
extern void func_ov107_020c92b0(struct Obj *self, int index, int a, int b, int scale);
extern void func_ov107_020c9074(struct Obj *self, struct Subitem *item);
extern int *func_01fffca8(void *pool, int size, int count);
extern int func_ov107_020c319c(void *camera);
extern void func_0203355c(int id);

void func_ov148_020cfdc8(struct Obj *self)
{
    struct Box box;
    struct Subitem *item;
    int *slot;
    int value;
    int i;
    unsigned int flags;

    self->fn08 = func_ov148_020d0094;
    self->fn0c = func_ov148_020d00c0;
    self->fn1c = func_ov148_020d0288;
    self->fn30 = func_ov148_020d03e4;
    self->fn28 = func_ov148_020d0140;
    self->fn2c = func_ov148_020d017c;
    self->fn34 = func_ov148_020d01b8;
    self->fn1d0 = func_ov148_020d0440;
    self->fn1dc = func_ov148_020d03ac;
    self->fn1e0 = func_ov148_020d05a4;
    self->fn1e4 = func_ov148_020d05d0;

    box.min.x = -0x1800;
    box.min.z = -0x1800;
    box.min.y = 0;
    box.max.x = 0x1800;
    box.max.y = 0x1800;
    box.max.z = 0x1800;

    flags = self->flags60;
    self->flags60 = flags & ~0xff00 |
        (((((flags << 0x10) >> 0x18) | 0x40) << 0x18) >> 0x10);

    self->camera[3] = 0xa00;
    self->camera[0] = 0;
    self->camera[1] = 0xa00;
    self->camera[2] = 0;

    self->box = box;

    self->subitem384 = func_0203b898(func_ov107_020c9440(self, 0));
    self->subitem384->callback74 = func_ov148_020cfc04;
    self->subitem384->owner84 = self;
    func_0203bfb4(self->subscriberList9c, self->subitem384);
    self->resourceId3d4 = func_0203bdfc(self->subitem384, data_ov148_020d250c);

    (self->subitem388 = func_0203b898(func_ov107_020c9440(self, 1)))->callback6c = func_ov148_020cfc4c;
    self->subitem388->owner84 = self;
    func_0203c7ac(self->subitem388, 0);
    self->resourceId3d0 = func_0203bdfc(self->subitem388, data_ov148_020d2514);

    self->angle3bc = 0x10c1;
    func_0202f188(self->quaternion3c0, &data_02042264, self->angle3bc);

    func_ov107_020c92b0(self, 0, 1, 0, 0x1800);
    func_ov107_020c92b0(self, 2, 1, 0, 0x1800);
    func_ov107_020c92b0(self, 1, 1, 0, 0x1800);
    func_ov107_020c92b0(self, 4, 1, 0, 0x1800);

    item = self->subitem3f0 = func_0203b898(func_ov107_020c9440(self, 4));
    func_ov107_020c9074(self, item);
    item->flags5c |= 2;

    self->poolEntry38c = func_01fffca8(self->pool22c, 0x10, 0x64);
    *self->poolEntry38c = func_ov107_020c319c(self->camera);

    slot = func_01fffca8(self->pool144, 4, 0x64);
    value = (*slot = func_ov107_020c319c(self->camera));
    self->poolValue390 = value;

    for (i = 0; i < 3; i++) {
        self->child398[i] = func_ov148_020d1940(self);
    }

    func_0203355c(0x126);
}





