/* Constructor for the actor's sub-object: install the five entry points, set the
 * appearance flags, subscribe the main item, allocate the two child slots and
 * open the particle pool.
 *
 * The object itself is built by the allocator just above this one, which takes
 * 0x3a0 bytes and parks the owning actor at +0x398 -- so the slot pointer this
 * fills in at +0x39c is the object's very last word.
 *
 * Same template as the ov149 constructor, with this actor's flags nibble (0x40
 * rather than 0x46), its camera scale of 0x800, and the owner and slot pointers
 * moved from +0x38c/+0x390 to +0x398/+0x39c.
 */
typedef unsigned short u16;

struct Ov141ChildIds {
    int values[2];
};

struct Ov141Subitem {
    char pad00[0x5c];
    unsigned int flags5c;
};

struct Ov141PoolEntry {
    int value;
    int pad04;
    unsigned int flags : 8;
};

struct Ov141ChildSlot {
    struct Ov141Subitem *child;
    int pad04;
};

struct Ov141SubObj {
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
    struct Ov141Subitem *subscriber9c;
    char padA0[0x10e];
    u16 flags1ae;
    char pad1b0[0x20];
    void (*fn1d0)(void);
    char pad1d4[0x58];
    char pool22c[0x158];
    struct Ov141Subitem *subitem384;
    struct Ov141PoolEntry *poolEntry388;
    char pad38c[0x0c];
    struct Ov141SubObj *owner398;
    struct Ov141ChildSlot *slots39c;
};

extern const struct Ov141ChildIds data_ov141_020ce9dc;
extern void func_ov141_020cdb88(void);
extern void func_ov141_020cdbc8(void);
extern void func_ov141_020cdc00(void);
extern void func_ov141_020cdd10(void);
extern void func_ov141_020cdcb4(void);

extern void *func_ov107_020c9440(struct Ov141SubObj *owner, int index);
extern struct Ov141Subitem *func_0203b898(void *item);
extern void func_0203bfb4(struct Ov141Subitem *subscriber, struct Ov141Subitem *item);
extern void func_0203b9fc(struct Ov141Subitem *item, int state, int zero, int enabled);
extern void func_0203c7ac(struct Ov141Subitem *item, int value);
extern void *func_0203d15c(int size);
extern void func_ov107_020c9074(struct Ov141SubObj *owner, struct Ov141Subitem *item);
extern struct Ov141PoolEntry *func_01fffca8(void *pool, int elementSize, int capacity);
extern int func_ov107_020c319c(void *camera);

void func_ov141_020cd9e0(struct Ov141SubObj *self)
{
    struct Ov141ChildIds ids = data_ov141_020ce9dc;
    unsigned int flags;
    int i;

    self->fn08 = func_ov141_020cdb88;
    self->fn0c = func_ov141_020cdbc8;
    self->fn1c = func_ov141_020cdc00;
    self->fn30 = func_ov141_020cdd10;
    self->fn1d0 = func_ov141_020cdcb4;

    self->flags1ae |= 4;
    self->camera[3] = 0x800;
    self->subscriber9c->flags5c |= 4;

    flags = self->flags60;
    self->flags60 = flags & ~0xff00 |
        (((((flags << 0x10) >> 0x18) | 0x40) << 0x18) >> 0x10);

    self->subitem384 = func_0203b898(func_ov107_020c9440(self->owner398, 6));
    func_0203bfb4(self->subscriber9c, self->subitem384);
    func_0203b9fc(self->subitem384, 0, 0, 1);
    func_0203b9fc(self->subitem384, 2, 0, 1);
    func_0203c7ac(self->subitem384, 0);

    self->slots39c = func_0203d15c(0x10);

    for (i = 0; i < 2; i++) {
        self->slots39c[i].child =
            func_0203b898(func_ov107_020c9440(self->owner398, ids.values[i]));
        func_ov107_020c9074(self->owner398, self->slots39c[i].child);
        self->slots39c[i].child->flags5c |= 2;
    }

    self->poolEntry388 = func_01fffca8(self->pool22c, 0x10, 0x64);
    self->poolEntry388->value = func_ov107_020c319c(self->camera);
    self->poolEntry388->flags |= 2;
}
