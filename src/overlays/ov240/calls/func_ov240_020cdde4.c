#pragma opt_dead_assignments off
#pragma opt_propagation off
/* Constructor of the ov240 enemy: resolves the overlay's config into +0x384, installs the
 * handlers (+8 tick, +0xc draw, +0x1c message, +0x30 callback, +0x1d0 hit, +0x1dc config,
 * +0x1e0/+0x1e4 callbacks), seeds the +0x64 pose (scale 0x1000, y 0x1000) and the +0x1fc
 * bounding box; builds the primary item from pool entry 0 (subscribed), keeps the "move" motion
 * handle (+0x398), creates the pool entry 3/4 sub-items (+0x39c/+0x3a4, attached, bit 1), the
 * kind-1/kind-0 sub-items derived from the config (+0x3ac/+0x3b4, attached, bit 1) and the pool
 * entry 2 sub-item (+0x3bc, attached, bit 1), two placements on the +0x22c/+0x144 lists
 * (+0x38c/+0x390) and loads sound 0x139. */
typedef void (*Callback)(void);

struct Subitem {
    char pad000[0x5c];
    unsigned int flags5c;
};

struct Box {
    int xmin, ymin, zmin;
    int xmax, ymax, zmax;
};

struct Ov240Actor {
    char pad000[0x8];
    Callback fn08;
    Callback fn0c;
    char pad010[0xc];
    Callback fn1c;
    char pad020[0x10];
    Callback fn30;
    char pad034[0x30];
    int camera[4];
    char pad074[0x28];
    int subscriberList9c;
    char pad0a0[0xa4];
    char pool144[0x8c];
    Callback fn1d0;
    char pad1d4[8];
    Callback fn1dc;
    Callback fn1e0;
    Callback fn1e4;
    char pad1e8[0x14];
    struct Box box;
    char pad214[0x18];
    char pool22c[0x158];
    int config384;
    struct Subitem *subitem388;
    void **poolEntry38c;
    void *poolValue390;
    char pad394[4];
    int motion398;
    struct Subitem *subitem39c;
    char pad3a0[4];
    struct Subitem *subitem3a4;
    char pad3a8[4];
    struct Subitem *subitem3ac;
    char pad3b0[4];
    struct Subitem *subitem3b4;
    char pad3b8[4];
    struct Subitem *subitem3bc;
};

extern int func_ov107_020c9c24(const char *buf);
extern void func_ov240_020ce07c(void);
extern void func_ov240_020ce0c4(void);
extern void func_ov240_020ce138(void);
extern void func_ov240_020ce2e4(void);
extern void func_ov240_020ce340(void);
extern void func_ov240_020ce2ac(void);
extern void func_ov240_020ce568(void);
extern void func_ov240_020ce594(void);
extern void *func_ov107_020c9440(struct Ov240Actor *self, int index);
extern struct Subitem *func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, struct Subitem *item);
extern int func_ov107_020c9e50(void *item, const char *name);
extern void func_ov107_020c9074(struct Ov240Actor *self, struct Subitem *item);
extern void **func_01fffca8(void *pool, int size, int count);
extern void *func_ov107_020c319c(void *camera);
extern void func_0203355c(int id);
extern const char data_ov240_020cfb8c[];
extern const char data_ov240_020cfb9c[];

void func_ov240_020cdde4(struct Ov240Actor *self)
{
    int minX;
    int minY;
    int minZ;
    struct Box box;
    struct Subitem *item;
    void **slot;
    void *value;

    self->config384 = func_ov107_020c9c24(data_ov240_020cfb8c);
    minX = -0xeea;
    box.xmin = minX;
    minY = 0x17;
    box.ymin = minY;
    minZ = -0x858;
    box.zmin = minZ;
    box.xmax = box.xmin + 0x1dd3;
    box.ymax = box.ymin + 0x1c27;
    box.zmax = box.zmin + 0xd64;

    self->fn08 = func_ov240_020ce07c;
    self->fn0c = func_ov240_020ce0c4;
    self->fn1c = func_ov240_020ce138;
    self->fn30 = func_ov240_020ce2e4;
    self->fn1d0 = func_ov240_020ce340;
    self->fn1dc = func_ov240_020ce2ac;
    self->fn1e0 = func_ov240_020ce568;
    self->fn1e4 = func_ov240_020ce594;
    self->camera[3] = 0x1000;
    self->camera[0] = 0;
    self->camera[1] = 0x1000;
    self->camera[2] = 0;
    self->box = box;
    self->subitem388 = func_0203b898(func_ov107_020c9440(self, 0));
    func_0203bfb4(self->subscriberList9c, self->subitem388);
    self->motion398 = func_ov107_020c9e50(func_ov107_020c9440(self, 1), data_ov240_020cfb9c);
    item = self->subitem39c =
        func_0203b898(func_ov107_020c9440(self, 3));
    func_ov107_020c9074(self, item);
    item->flags5c |= 2;
    item = self->subitem3a4 = func_0203b898(func_ov107_020c9440(self, 4));
    func_ov107_020c9074(self, item);
    item->flags5c |= 2;
    #pragma opt_scheduling off
        { struct Ov240Actor *owner = self; struct Subitem **out = &self->subitem3ac;
        item = *out = func_0203b898((void *)((((self->config384 + 0x8000) & 0xfffffc) << 7) | 0x80000001));
        func_ov107_020c9074(owner, item); }
    item->flags5c |= 2;
    item = self->subitem3b4 = func_0203b898((void *)((((self->config384 + 0x8000) & 0xfffffc) << 7) | 0x80000000));
    func_ov107_020c9074(self, item);
    item->flags5c |= 2;
    item = self->subitem3bc = func_0203b898(func_ov107_020c9440(self, 2));
    func_ov107_020c9074(self, item);
    { struct Ov240Actor *owner = self; void *pool = self->pool22c;
        owner->poolEntry38c = func_01fffca8(pool, (item->flags5c |= 2, 0x10), 0x64); }
    *self->poolEntry38c = func_ov107_020c319c(self->camera);
    slot = func_01fffca8(self->pool144, 4, 0x64);
    value = (*slot = func_ov107_020c319c(self->camera));
    self->poolValue390 = value;
    func_0203355c(0x139);
}
