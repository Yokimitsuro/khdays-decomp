/* func_ov245_020d1e50 -- constructor of the ov245 actor variant: installs the handlers (+8 tick,
 * +0xc draw, +0x28 / +0x2c / +0x30 / +0x34 callbacks, +0x1c message, +0x24 hook, +0x1dc finish),
 * raises bits 2-6 of the +0x60 high byte, sets the +0x70 scale to 2.0, builds the primary item
 * from pool entry 0x15 of the +0x3c8 pool (+0x384, subscribed to +0x9c) and its "tag_00" joint
 * (+0x3b8), a shape on the +0x144 list (+0x388) from a request at the origin along
 * data_02042258 with rate 7.0 / value 2.0, ten +0x390 slots from 020d284c, and clears +0x38c. */
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 pos; Vec3 axis; int rate; int value; } ShapeRequest;
typedef void (*Callback)(void);
typedef unsigned short u16;
struct Ov245Self { char pad[0x390]; int slots[10]; };

extern void func_ov245_020d1fb4(void);
extern void func_ov245_020d1fd0(void);
extern void func_ov245_020d2010(void);
extern void func_ov245_020d204c(void);
extern void func_ov245_020d2154(void);
extern void func_ov245_020d20c0(void);
extern void func_ov245_020cc8a4(void);
extern void func_ov245_020cc8ec(void);
extern void func_ov245_020d2088(void);
extern void *func_ov107_020c9440(int pool, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern int func_0203bee8(int item, int kind, const char *name);
extern int *func_01fffca8(void *list, int stride, int max);
extern int func_ov107_020c3210(ShapeRequest *req);
extern int func_ov245_020d284c(int self);
extern const char data_ov245_020d722c[];
extern const Vec3 data_02041dc8;
extern const Vec3 data_02042258;

void func_ov245_020d1e50(int self) {
    int pool = *(int *)(self + 0x3c8);
    ShapeRequest req;
    int *slot;
    int i;

    *(Callback *)(self + 0x8) = func_ov245_020d1fb4;
    *(Callback *)(self + 0xc) = func_ov245_020d1fd0;
    *(Callback *)(self + 0x28) = func_ov245_020d2010;
    *(Callback *)(self + 0x2c) = func_ov245_020d204c;
    *(Callback *)(self + 0x30) = func_ov245_020d2154;
    *(Callback *)(self + 0x34) = func_ov245_020d20c0;
    *(Callback *)(self + 0x1c) = func_ov245_020cc8a4;
    *(Callback *)(self + 0x24) = func_ov245_020cc8ec;
    *(Callback *)(self + 0x1dc) = func_ov245_020d2088;
    {
        u16 hw = *(u16 *)(self + 0x60);
        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x7c) << 0x18) >> 0x10);
    }
    *(int *)(self + 0x70) = 0x2000;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(pool, 0x15));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    *(int *)(self + 0x3b8) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov245_020d722c);
    req.pos = data_02041dc8;
    req.axis = data_02042258;
    req.rate = 0x7000;
    req.value = 0x2000;
    slot = func_01fffca8((void *)(self + 0x144), 4, 0x64);
    *(int *)(self + 0x388) = *slot = func_ov107_020c3210(&req);
    for (i = 0; i < 10; i++) {
        ((struct Ov245Self *)self)->slots[i] = func_ov245_020d284c(self);
    }
    *(int *)(self + 0x38c) = 0;
}
