/* func_ov245_020d3838 -- constructor of the ov245 four-shape actor: installs the handlers (+8
 * tick, +0xc draw, +0x1c message, +0x30 / +0x34 callbacks, +0x24 hook, +0x1d0 hit, +0x1dc
 * finish), raises bits 2, 4, 5 and 6 of the +0x60 high byte, seeds the +0x64 pose at scale 1.5,
 * builds the primary item from pool entry 0x13 of the +0x3b4 pool (+0x384, subscribed) with its
 * four named joints (+0x3b0 kind 3, +0x3a4 / +0x3a8 / +0x3ac kind 1), the +0x3b8 / +0x3c0
 * sub-items from entries 0x1e / 0x1f (attached, bit 1 of +0x5c), a shape on the +0x22c list
 * (+0x388, rate 3.0 / value 1.5 along data_02042264, bit 1 of its +8 low byte) and four on the
 * +0x144 list (+0x38c.., value 0.75, the last 1.5); +0x39c starts empty. */
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 pos; Vec3 axis; int rate; int value; } ShapeRequest;
typedef void (*Callback)(void);
typedef unsigned short u16;
struct w8 { unsigned int lo : 8, rest : 24; };
struct Ov245Self { char pad[0x38c]; int shapes[4]; };

extern void func_ov245_020d3aac(void);
extern void func_ov245_020d3ae4(void);
extern void func_ov245_020d3b24(void);
extern void func_ov245_020d3d60(void);
extern void func_ov245_020d3c24(void);
extern void func_ov245_020cc8ec(void);
extern void func_ov245_020d3d14(void);
extern void func_ov245_020d3bec(void);
extern void *func_ov107_020c9440(int pool, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern int func_0203bee8(int item, int kind, const char *name);
extern void func_ov107_020c9074(int self, int item);
extern int *func_01fffca8(void *list, int stride, int max);
extern int func_ov107_020c3210(ShapeRequest *req);
extern const char data_ov245_020d7234[];
extern const char data_ov245_020d723c[];
extern const char data_ov245_020d7244[];
extern const char data_ov245_020d724c[];
extern const Vec3 data_02041dc8;
extern const Vec3 data_02042264;

typedef struct { int x, y, z; } VecP_;

static inline void VecSetP_(VecP_ *v, int x, int y, int z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

/* self is a byte pointer, as in the ROM's unsigned address arithmetic */
void func_ov245_020d3838(char *self) {
    int pool = *(int *)(self + 0x3b4);
    ShapeRequest req;
    int *slot;
    int item;
    int i;

    *(Callback *)(self + 0x8) = func_ov245_020d3aac;
    *(Callback *)(self + 0xc) = func_ov245_020d3ae4;
    *(Callback *)(self + 0x1c) = func_ov245_020d3b24;
    *(Callback *)(self + 0x30) = func_ov245_020d3d60;
    *(Callback *)(self + 0x34) = func_ov245_020d3c24;
    *(Callback *)(self + 0x24) = func_ov245_020cc8ec;
    *(Callback *)(self + 0x1d0) = func_ov245_020d3d14;
    *(Callback *)(self + 0x1dc) = func_ov245_020d3bec;
    {
        u16 hw = *(u16 *)(self + 0x60);
        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x74) << 0x18) >> 0x10);
    }
    *(int *)(self + 0x70) = 0x1800;
    VecSetP_((VecP_ *)(self + 0x64), 0, *(int *)(self + 0x70), 0);
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(pool, 0x13));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    *(int *)(self + 0x3b0) = func_0203bee8(*(int *)(self + 0x384), 3, data_ov245_020d7234);
    *(int *)(self + 0x3a4) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov245_020d723c);
    *(int *)(self + 0x3a8) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov245_020d7244);
    *(int *)(self + 0x3ac) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov245_020d724c);
    item = *(int *)(self + 0x3b8) = func_0203b898(func_ov107_020c9440(pool, 0x1e));
    func_ov107_020c9074(self, item);
    *(int *)(item + 0x5c) |= 2;
    item = *(int *)(self + 0x3c0) = func_0203b898(func_ov107_020c9440(pool, 0x1f));
    func_ov107_020c9074(self, item);
    *(int *)(item + 0x5c) |= 2;
    req.pos = data_02041dc8;
    req.axis = data_02042264;
    req.rate = 0x3000;
    req.value = 0x1800;
    *(int **)(self + 0x388) = func_01fffca8((void *)(self + 0x22c), 0x10, 0x64);
    **(int **)(self + 0x388) = func_ov107_020c3210(&req);
    ((struct w8 *)(*(int *)(self + 0x388) + 8))->lo |= 2;
    for (i = 0; i < 4; i++) {
        req.value = i == 3 ? 0x1800 : 0xc00;
        slot = func_01fffca8((void *)(self + 0x144), 4, 0x64);
        ((struct Ov245Self *)self)->shapes[i] = *slot = func_ov107_020c3210(&req);
    }
    *(int *)(self + 0x39c) = 0;
}
