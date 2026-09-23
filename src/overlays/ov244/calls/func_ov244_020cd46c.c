/* Construction of the ov244 enemy's item (x2 with ov277): installs the handlers (+8 020cd64c,
 * +0xc 020cd68c, +0x1c 020cd6c4, +0x30 020cd7f8, +0x1d0 020cd7ac), raises flags 0x6e in the +0x60
 * high byte, 0xc in +0x1ae and bit 2 of the +0x9c body's +0x5c, sets the +0x70 scale to 0.625 and
 * +0x54 to 0x10. The +0x388 sub-item is built from pose 0x2f of the +0x384 owner, the +0xa0 pose
 * is scaled by 0.5 (ca9c), the sub-item is subscribed to +0x9c, its channels 0, 1, 2 and 4 are
 * enabled and it is reset (c7ac); the three poses of data_ov244_020d36d0 build the +0x3a4 pair
 * table (registered, bit 1 of +0x5c), and the +0x22c collision handle (+0x38c) is reserved from
 * the +0x64 pose with bit 1 of its flag byte raised. */
typedef unsigned short u16;

struct PoseIds {
    int values[3];
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
    char pad34[0x20];
    int field54;
    char pad58[0x08];
    u16 flags60;
    char pad62[0x02];
    int pose[4];
    char pad74[0x28];
    struct Subitem *subscriber9c;
    char srtA0[0x10e];
    u16 flags1ae;
    char pad1b0[0x20];
    void (*fn1d0)(void);
    char pad1d4[0x58];
    char pool22c[0x158];
    struct Obj *owner384;
    struct Subitem *subitem388;
    struct PoolEntry *poolEntry38c;
    char pad390[0x14];
    struct ChildSlot *slots3a4;
};

extern const struct PoseIds data_ov244_020d36d0;
extern void func_ov244_020cd64c(void);
extern void func_ov244_020cd68c(void);
extern void func_ov244_020cd6c4(void);
extern void func_ov244_020cd7f8(void);
extern void func_ov244_020cd7ac(void);

extern void *func_ov107_020c9440(struct Obj *owner, int index);
extern struct Subitem *func_0203b898(void *item);
extern void func_0203ca9c(void *srt, int scale);
extern void func_0203bfb4(struct Subitem *subscriber, struct Subitem *item);
extern void func_0203b9fc(struct Subitem *item, int state, int zero, int enabled);
extern void func_0203c7ac(struct Subitem *item, int value);
extern void *func_0203d15c(int size);
extern void func_ov107_020c9074(struct Obj *self, struct Subitem *item);
extern struct PoolEntry *func_01fffca8(void *pool, int elementSize, int capacity);
extern int func_ov107_020c319c(void *pose);

void func_ov244_020cd46c(struct Obj *self)
{
    struct PoseIds ids = data_ov244_020d36d0;
    unsigned int flags;
    int i;

    self->fn08 = func_ov244_020cd64c;
    self->fn0c = func_ov244_020cd68c;
    self->fn1c = func_ov244_020cd6c4;
    self->fn30 = func_ov244_020cd7f8;
    self->fn1d0 = func_ov244_020cd7ac;

    flags = self->flags60;
    self->flags60 = flags & ~0xff00 |
        (((((flags << 0x10) >> 0x18) | 0x6e) << 0x18) >> 0x10);
    self->flags1ae |= 0xc;
    self->subscriber9c->flags5c |= 4;
    self->pose[3] = 0xa00;
    self->field54 = 0x10;

    self->subitem388 = func_0203b898(func_ov107_020c9440(self->owner384, 0x2f));
    func_0203ca9c(self->srtA0, 0x800);
    func_0203bfb4(self->subscriber9c, self->subitem388);
    func_0203b9fc(self->subitem388, 0, 0, 1);
    func_0203b9fc(self->subitem388, 1, 0, 1);
    func_0203b9fc(self->subitem388, 2, 0, 1);
    func_0203b9fc(self->subitem388, 4, 0, 1);
    func_0203c7ac(self->subitem388, 0);

    self->slots3a4 = func_0203d15c(0x18);
    for (i = 0; i < 3; i++) {
        self->slots3a4[i].child = func_0203b898(func_ov107_020c9440(self->owner384, ids.values[i]));
        func_ov107_020c9074(self, self->slots3a4[i].child);
        self->slots3a4[i].child->flags5c |= 2;
    }

    self->poolEntry38c = func_01fffca8(self->pool22c, 0x10, 0x64);
    self->poolEntry38c->value = func_ov107_020c319c(self->pose);
    self->poolEntry38c->flags |= 2;
}
