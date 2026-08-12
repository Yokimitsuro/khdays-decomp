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

struct OutgoingFrame {
    unsigned int outgoing;
    struct CameraWork work;
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
    char pad20[0x10];
    ObjCallback fn30;
    ObjCallback fn34;
    char pad38[0x2c];
    int camera64[4];
    char pad74[0x28];
    struct Subscriber *subscriber9c;
    char padA0[0xa4];
    char pool144[0x6a];
    u16 flags1ae;
    char pad1b0[0x20];
    ObjCallback fn1d0;
    ObjCallback fn1d4;
    char pad1d8[0x04];
    ObjCallback fn1dc;
    ObjCallback fn1e0;
    char pad1e4[0x10];
    int field1f4;
    char pad1f8[0x34];
    char pool22c[0x158];
    struct CreatedItem *subitem384;
    struct PoolEntry *poolEntry388;
    int poolValue38c;
};

extern const struct CameraWork data_ov185_020d16ac;
extern struct RollingCounter data_ov185_020d16d0;

extern void func_ov185_020cfbb8(struct Obj *self);
extern void func_ov185_020cfbd4(struct Obj *self);
extern void func_ov185_020cfc4c(struct Obj *self);
extern void func_ov185_020cfdf4(struct Obj *self);
extern void func_ov185_020cfdbc(struct Obj *self);
extern void func_ov185_020cfcc0(struct Obj *self);
extern void func_ov185_020cfe40(struct Obj *self);
extern void func_ov185_020cffd0(struct Obj *self);
extern void func_ov185_020cfcd8(struct Obj *self);

extern void *func_ov107_020c9440(struct Obj *self, int index);
extern struct CreatedItem *func_0203b898(void *item);
extern int func_0203bfb4(struct Subscriber *subscriber, struct CreatedItem *item);
extern void func_02016b60(void *config, unsigned int index, unsigned int variant);
extern void func_ov107_020c92b0(struct Obj *, int, unsigned int, int);
extern struct PoolEntry *func_01fffca8(void *pool, int elementSize, int capacity);
extern int func_ov107_020c319c(void *camera);
extern void func_0203355c(int resourceId, int value);

/*
 * Constructor for the ov185 actor.
 *
 * Installs the nine handler entries, clears the counter, seeds the camera work
 * record from the overlay spawn table, raises the ring flag and the subscriber
 * flag, then creates the subitem, registers it, and configures its slot with a
 * rolling sequence number that advances modulo 32.  Finally it reserves two
 * pool slots, takes a camera handle for each, and announces the second as
 * resource 0x120.
 *
 * The 0x1000 written just before the spawn call is a field of the local frame,
 * not a fifth argument.  The frame begins at the outgoing argument slot, so the
 * callee does read the value there, but in the source it is an ordinary field
 * store and the call takes four parameters.  The store survives because the
 * frame's other field is address-taken, being handed to the camera index helper
 * twice.  Written as an argument instead, the compiler treats it as call setup,
 * delays it, and the whole surrounding window comes out permuted.
 */
void func_ov185_020cfa2c(struct Obj *self)
{
    struct OutgoingFrame frame;
    frame.work = data_ov185_020d16ac;
    struct PoolEntry *slot;
    int result;
    u8 capacity;
    self->fn08 = func_ov185_020cfbb8;
    self->fn0c = func_ov185_020cfbd4;
    self->fn1c = func_ov185_020cfc4c;
    self->fn30 = func_ov185_020cfdf4;
    self->fn34 = func_ov185_020cfdbc;
    self->fn1d4 = func_ov185_020cfcc0;
    self->fn1d0 = func_ov185_020cfe40;
    self->fn1e0 = func_ov185_020cffd0;
    self->fn1dc = func_ov185_020cfcd8;

    self->field1f4 = 0;
    *(struct CameraWork *)self->camera64 = frame.work;
    self->flags1ae |= 0x10;
    self->subscriber9c->flags5c |= 4;

    self->subitem384 = func_0203b898(func_ov107_020c9440(self, 0));
    func_0203bfb4(self->subscriber9c, self->subitem384);
    func_02016b60(self->subitem384->container88->config78, 3,
                  data_ov185_020d16d0.value);

    data_ov185_020d16d0.value = (data_ov185_020d16d0.value + 1) & 0x1f;
    frame.outgoing = 0x1000;
    func_ov107_020c92b0(self, 2, 2, 0);

    self->poolEntry388 = func_01fffca8(self->pool22c, 0x10, 0x64);

    {
        result = func_ov107_020c319c(&frame.work);
        capacity = 0x64;
        self->poolEntry388->value = result;

        slot = func_01fffca8(self->pool144, 4, capacity);
        result = (slot->value = func_ov107_020c319c(&frame.work));
        self->poolValue38c = result;

        func_0203355c(0x120, result);
    }
}
