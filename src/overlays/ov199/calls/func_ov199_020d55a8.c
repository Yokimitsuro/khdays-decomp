typedef unsigned short u16;

struct ChildIds {
    int values[2];
};

struct Subitem {
    char pad00[0x5c];
    unsigned int flags5c;
};

struct PoolEntry {
    int value;
    int pad04;
    unsigned int flags : 8;
};

struct ChildSlot {
    struct Subitem *child;
    int pad04;
};

struct Obj {
    char pad00[0x08];
    void (*fn08)(void);
    void (*fn0c)(void);
    char pad10[0x0c];
    void (*fn1c)(void);
    char pad20[0x10];
    void (*fn30)(void);
    char pad34[0x2c];
    u16 flags60;
    char pad62[0x02];
    int camera[4];
    char pad74[0x28];
    struct Subitem *subscriber9c;
    char padA0[0x10e];
    u16 flags1ae;
    char pad1b0[0x20];
    void (*fn1d0)(void);
    char pad1d4[0x58];
    char pool22c[0x158];
    struct Subitem *subitem384;
    struct PoolEntry *poolEntry388;
    int field38c;
    struct Obj *owner390;
    struct ChildSlot slots394[2];
};

extern const struct ChildIds data_ov199_020d611c;
extern void func_ov199_020d5774(void);
extern void func_ov199_020d57ac(void);
extern void func_ov199_020d57e4(void);
extern void func_ov199_020d5974(void);
extern void func_ov199_020d5910(void);

extern void *func_ov107_020c9440(struct Obj *owner, int index);
extern struct Subitem *func_0203b898(void *item);
extern void func_0203bfb4(struct Subitem *subscriber, struct Subitem *item);
extern void func_0203b9fc(struct Subitem *item, int state, int zero, int enabled);
extern void func_0203c7ac(struct Subitem *item, int value);
extern void func_ov107_020c9074(struct Obj *self, struct Subitem *item);
extern struct PoolEntry *func_01fffca8(void *pool, int elementSize, int capacity);
extern int func_ov107_020c319c(void *camera);

void func_ov199_020d55a8(struct Obj *self)
{
    struct ChildIds ids = data_ov199_020d611c;
    struct Obj *owner = self->owner390;
    unsigned int flags;
    int i;

    self->fn08 = func_ov199_020d5774;
    self->fn0c = func_ov199_020d57ac;
    self->fn1c = func_ov199_020d57e4;
    self->fn30 = func_ov199_020d5974;
    self->fn1d0 = func_ov199_020d5910;

    flags = self->flags60;
    self->flags60 = flags & ~0xff00 |
        (((((flags << 0x10) >> 0x18) | 0x4e) << 0x18) >> 0x10);
    self->flags1ae |= 0x14;
    self->camera[3] = 0xa00;

    self->subscriber9c->flags5c |= 4;

    self->subitem384 = func_0203b898(func_ov107_020c9440(owner, 2));
    func_0203bfb4(self->subscriber9c, self->subitem384);
    func_0203b9fc(self->subitem384, 0, 0, 1);
    func_0203b9fc(self->subitem384, 2, 0, 1);
    func_0203b9fc(self->subitem384, 4, 0, 1);
    func_0203b9fc(self->subitem384, 1, 0, 1);
    func_0203c7ac(self->subitem384, 0);

    for (i = 0; i < 2; i++) {
        func_ov107_020c9074(
            self,
            self->slots394[i].child =
                func_0203b898(func_ov107_020c9440(owner, ids.values[i])));
        self->slots394[i].child->flags5c |= 2;
    }

    self->poolEntry388 = func_01fffca8(self->pool22c, 0x10, 0x64);
    self->poolEntry388->value = func_ov107_020c319c(self->camera);
    self->poolEntry388->flags |= 2;
    self->field38c = 0;
}
