typedef unsigned char u8;
typedef unsigned short u16;

struct Obj;
typedef void (*ObjCallback)(struct Obj *self);

struct Vec3 {
    int x;
    int y;
    int z;
};

struct CameraWork {
    struct Vec3 vector;
    int scalar;
};

struct ConfigContainer {
    char pad00[0x78];
    void *config78;
};

struct Subscriber {
    char pad00[0x5c];
    unsigned int flags5c;
};

struct CreatedItem {
    char pad00[0x88];
    struct ConfigContainer *container88;
};

struct PoolEntry {
    int value;
};

struct RollingCounter {
    u8 value;
};

struct Obj {
    char pad00[0x08];
    ObjCallback fn08;
    ObjCallback fn0c;
    char pad10[0x0c];
    ObjCallback fn1c;
    char pad20[0x08];
    ObjCallback fn28;
    ObjCallback fn2c;
    ObjCallback fn30;
    ObjCallback fn34;
    char pad38[0x28];
    u16 flags60;
    char pad62[0x02];
    int camera64[4];
    char pad74[0x28];
    struct Subscriber *subscriber9c;
    char padA0[0xa4];
    char pool144[0x6a];
    u16 flags1ae;
    char pad1b0[0x20];
    ObjCallback fn1d0;
    char pad1d4[0x08];
    ObjCallback fn1dc;
    ObjCallback fn1e0;
    char pad1e4[0x08];
    ObjCallback fn1ec;
    ObjCallback fn1f0;
    char pad1f4[0x04];
    ObjCallback fn1f8;
    char pad1fc[0x30];
    char pool22c[0x158];
    struct CreatedItem *subitem384;
    struct PoolEntry *poolEntry388;
    int poolValue38c;
    void **entities390;
    char spawner394[0x14];
};

extern const struct CameraWork data_ov186_020d34b0;
extern struct RollingCounter data_ov186_020d34e0;

extern void func_ov186_020cfe54(struct Obj *self);
extern void func_ov186_020cfe78(struct Obj *self);
extern void func_ov186_020d01e0(struct Obj *self);
extern void func_ov186_020cff98(struct Obj *self);
extern void func_ov186_020d0000(struct Obj *self);
extern void func_ov186_020d003c(struct Obj *self);
extern void func_ov186_020d00c4(struct Obj *self);
extern void func_ov186_020d022c(struct Obj *self);
extern void func_ov186_020d03bc(struct Obj *self);
extern void func_ov186_020cfed4(struct Obj *self);
extern void func_ov186_020d0104(struct Obj *self);
extern void func_ov186_020d0164(struct Obj *self);
extern void func_ov186_020d01a4(struct Obj *self);

extern void *func_ov107_020c9440(struct Obj *self, int index);
extern struct CreatedItem *func_0203b898(void *item);
extern int func_0203bfb4(struct Subscriber *subscriber, struct CreatedItem *item);
extern void func_02016b60(void *config, unsigned int index, unsigned int variant);
extern void func_ov107_020c92b0(struct Obj *, int, unsigned int, int, int);
extern struct PoolEntry *func_01fffca8(void *pool, int elementSize, int capacity);
extern int func_ov107_020c319c(void *camera);
extern void func_ov107_020c2f94(int kind, void *spawner);
extern void **func_0203d15c(int size);
extern void *func_ov186_020d17c0(void *spawner);
extern void func_0203355c(int resourceId);

/*
 * Constructor for the ov185 actor.
 *
 * Installs the thirteen handler entries, raises bit 6 of the actor flag byte,
 * seeds the camera work record from the overlay spawn table, raises the ring
 * flag and the subscriber flag, then creates the subitem, registers it, and
 * configures slots 0, 2 and 3 with a rolling sequence number that advances to
 * 0x1e and then wraps back to 3.
 *
 * It then reserves two pool slots and takes a camera handle for each, loads the
 * parameter table at 0x394 from the archive, allocates the four entry child
 * table at 0x390, creates the four child entities from that parameter table,
 * and announces resource 0x120.
 *
 * The 0x2000 is a genuine fifth stacked argument of the spawn call here, unlike
 * in the smaller sibling at 020cfa2c where the same store is a field of a local
 * frame.  The two cases are told apart by where the store lands: as an argument
 * it is call setup and sits immediately before the branch, and as a field store
 * the scheduler is free to hoist it above the surrounding work.
 */
void func_ov186_020cfc08(struct Obj *self)
{
    struct CameraWork work;
    struct PoolEntry *slot;
    int result;
    int i;
    u16 v;

    work = data_ov186_020d34b0;
    self->fn08 = func_ov186_020cfe54;
    self->fn0c = func_ov186_020cfe78;
    self->fn30 = func_ov186_020d01e0;
    self->fn28 = func_ov186_020cff98;
    self->fn2c = func_ov186_020d0000;
    self->fn1c = func_ov186_020d003c;
    self->fn34 = func_ov186_020d00c4;
    self->fn1d0 = func_ov186_020d022c;
    self->fn1e0 = func_ov186_020d03bc;
    self->fn1dc = func_ov186_020cfed4;
    self->fn1ec = func_ov186_020d0104;
    self->fn1f0 = func_ov186_020d0164;
    self->fn1f8 = func_ov186_020d01a4;

    v = self->flags60;
    self->flags60 = (u16)((v & ~0xff00)
                          | ((((((unsigned int)v << 0x10) >> 0x18) | 0x40)
                              << 0x18) >> 0x10));
    *(struct CameraWork *)self->camera64 = work;
    self->flags1ae |= 0x10;
    self->subscriber9c->flags5c |= 4;

    self->subitem384 = func_0203b898(func_ov107_020c9440(self, 0));
    func_0203bfb4(self->subscriber9c, self->subitem384);
    func_02016b60(self->subitem384->container88->config78, 0,
                  data_ov186_020d34e0.value);
    func_02016b60(self->subitem384->container88->config78, 2,
                  data_ov186_020d34e0.value);
    func_02016b60(self->subitem384->container88->config78, 3,
                  data_ov186_020d34e0.value);

    data_ov186_020d34e0.value = data_ov186_020d34e0.value + 1;
    if (data_ov186_020d34e0.value >= 0x1f) {
        data_ov186_020d34e0.value = 3;
    }
    func_ov107_020c92b0(self, 2, 2, 0, 0x2000);

    self->poolEntry388 = func_01fffca8(self->pool22c, 0x10, 0x64);
    self->poolEntry388->value = func_ov107_020c319c(&work);

    slot = func_01fffca8(self->pool144, 4, 0x64);
    result = (slot->value = func_ov107_020c319c(&work));
    self->poolValue38c = result;

    func_ov107_020c2f94(2, self->spawner394);
    self->entities390 = func_0203d15c(0x10);
    for (i = 0; i < 4; i++) {
        self->entities390[i] = func_ov186_020d17c0(self->spawner394);
    }
    func_0203355c(0x120);
}
