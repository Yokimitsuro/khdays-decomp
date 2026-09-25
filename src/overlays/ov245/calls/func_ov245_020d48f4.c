/* func_ov245_020d48f4 -- constructor of the ov245 mounted actor: installs the handlers (+8
 * tick, +0xc draw, +0x1c message, +0x30 / +0x34 callbacks, +0x24 hook, +0x1dc finish), raises bit
 * 2 of +0x1ae and bits 2-6 of the +0x60 high byte, seeds the +0x64 pose at scale 1.25, builds the
 * primary item from pool entry 0x14 of the +0x398 pool (+0x384, subscribed), its named joint
 * (+0x394, kind 3) and the named motion of entry 0xf (+0x39c), the three +0x3b4 slot items from
 * entries 0x21..0x23 (attached, bit 1 of +0x5c), and from a request along data_02042258 at the
 * +0x70 scale two shapes: rate 5.0 on the pool's +0x22c list (+0x388) and rate 10.0 on the
 * +0x144 list (+0x38c); +0x390 starts empty. */
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 pos; Vec3 axis; int rate; int value; } ShapeRequest;
typedef void (*Callback)(void);
typedef unsigned short u16;
struct Ov245Slot { int pItem; int pad4; };
struct Ov245Self { char pad[0x3b4]; struct Ov245Slot slots[3]; };

extern void func_ov245_020d4ad8(void);
extern void func_ov245_020d4b18(void);
extern void func_ov245_020d4ba4(void);
extern void func_ov245_020d4e24(void);
extern void func_ov245_020d4ce0(void);
extern void func_ov245_020cc8ec(void);
extern void func_ov245_020d4ca8(void);
extern void *func_ov107_020c9440(int pool, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern int func_0203bee8(int item, int kind, const char *name);
extern int func_ov107_020c9e50(void *item, const char *name);
extern void func_ov107_020c9074(int self, int item);
extern int *func_01fffca8(void *list, int stride, int max);
extern int func_ov107_020c3210(ShapeRequest *req);
extern const char data_ov245_020d7254[];
extern const char data_ov245_020d725c[];
extern const Vec3 data_02041dc8;
extern const Vec3 data_02042258;

static inline void VEC_Set(Vec3 *v, int x, int y, int z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

void func_ov245_020d48f4(int self) {
    int pool = *(int *)(self + 0x398);
    ShapeRequest req;
    int *slot;
    int i;
    int item;

    *(Callback *)(self + 0x8) = func_ov245_020d4ad8;
    *(Callback *)(self + 0xc) = func_ov245_020d4b18;
    *(Callback *)(self + 0x1c) = func_ov245_020d4ba4;
    *(Callback *)(self + 0x30) = func_ov245_020d4e24;
    *(Callback *)(self + 0x34) = func_ov245_020d4ce0;
    *(Callback *)(self + 0x24) = func_ov245_020cc8ec;
    *(Callback *)(self + 0x1dc) = func_ov245_020d4ca8;
    *(u16 *)(self + 0x100 + 0xae) |= 4;
    {
        u16 hw = *(u16 *)(self + 0x60);
        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x7c) << 0x18) >> 0x10);
    }
    *(int *)(self + 0x70) = 0x1400;
    VEC_Set((Vec3 *)(self + 0x64), 0, *(int *)(self + 0x70), 0);
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(pool, 0x14));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    *(int *)(self + 0x394) = func_0203bee8(*(int *)(self + 0x384), 3, data_ov245_020d7254);
    *(int *)(self + 0x39c) = func_ov107_020c9e50(func_ov107_020c9440(pool, 0xf), data_ov245_020d725c);
    for (i = 0; i < 3; i++) {
        item = ((struct Ov245Self *)self)->slots[i].pItem = func_0203b898(func_ov107_020c9440(pool, i + 0x21));
        func_ov107_020c9074(self, item);
        *(int *)(((struct Ov245Self *)self)->slots[i].pItem + 0x5c) |= 2;
    }
    req.pos = data_02041dc8;
    req.axis = data_02042258;
    req.value = *(int *)(self + 0x70);
    req.rate = 0x5000;
    *(int **)(self + 0x388) = func_01fffca8((void *)(*(int *)(self + 0x398) + 0x22c), 0x10, 0x64);
    **(int **)(self + 0x388) = func_ov107_020c3210(&req);
    req.rate = 0xa000;
    slot = func_01fffca8((void *)(self + 0x144), 4, 0x64);
    *(int *)(self + 0x38c) = *slot = func_ov107_020c3210(&req);
    *(int *)(self + 0x390) = 0;
}
