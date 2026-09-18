/* Constructor of the ov151 enemy (and its byte-identical twin): installs the handlers (+8 tick,
 * +0xc draw, +0x1c message, +0x30/+0x28/+0x2c/+0x34 callbacks, +0x1d0 hit, +0x1dc finish) and
 * seeds the +0x64 pose (scale 0xc00, y 0xc00); builds the primary item from pool entry 0
 * (+0x384, subscribed) with two named attachments (+0x394 kind 3, +0x398 kind 1 whose +0x14
 * point is kept in +0x2cc), keeps the named motion handle from pool entry 1 (+0x3cc), the five
 * sub-items listed by the overlay's +0xebe0 table into a fresh 40-byte slot table (+0x390,
 * attached, bit 1), registers four reactions (0/1/2/4, id 0x2999) and two placements on the
 * +0x22c/+0x144 lists (+0x388/+0x38c) from the pose at the origin with scale 0xc00, then three
 * summoned pets (cc994) into a 12-byte table (+0x3c8) and loads sound 0x14f. */
typedef struct { int x, y, z; } Vec3;
typedef void (*Callback)(void);

struct PoolIds {
    int id[5];
};

struct Pose {
    Vec3 pos;
    int scale;
};

struct Ov151SubitemSlot {
    int pItem;
    int pad4;
};

extern void func_ov151_020cc24c(void);
extern void func_ov151_020cc29c(void);
extern void func_ov151_020cc314(void);
extern void func_ov151_020cd8c4(void);
extern void func_ov151_020cc570(void);
extern void func_ov151_020cc5ac(void);
extern void func_ov151_020cc5e8(void);
extern void func_ov151_020cd910(void);
extern void func_ov151_020cc2e4(void);
extern void *func_ov107_020c9440(int pool, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern int func_0203bee8(int item, int a, const char *name);
extern int func_ov107_020c9e50(void *item, const char *name);
extern void *func_0203d15c(int size);
extern void func_ov107_020c9074(char *self, int item);
extern void func_ov107_020c92b0(char *self, int a, int b, void *lift, int id);
extern int *func_01fffca8(void *list, int stride, int max);
extern int func_ov107_020c319c(struct Pose *pose);
extern int func_ov151_020cc994(char *self);
extern void func_0203355c(int id);
extern const struct PoolIds data_ov151_020cebe0;
extern const char data_ov151_020cec6c[];
extern const char data_ov151_020cec70[];
extern const char data_ov151_020cec78[];
extern const Vec3 data_02041dc8;

void func_ov151_020cbfc4(char *self)
{
    struct PoolIds pools;
    struct Pose pose;
    int *p;
    int i;

    pools = data_ov151_020cebe0;
    *(Callback *)(self + 0x8) = func_ov151_020cc24c;
    *(Callback *)(self + 0xc) = func_ov151_020cc29c;
    *(Callback *)(self + 0x1c) = func_ov151_020cc314;
    *(Callback *)(self + 0x30) = func_ov151_020cd8c4;
    *(Callback *)(self + 0x28) = func_ov151_020cc570;
    *(Callback *)(self + 0x2c) = func_ov151_020cc5ac;
    *(Callback *)(self + 0x34) = func_ov151_020cc5e8;
    *(Callback *)(self + 0x1d0) = func_ov151_020cd910;
    *(Callback *)(self + 0x1dc) = func_ov151_020cc2e4;
    *(int *)(self + 0x70) = 0xc00;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0xc00;
    *(int *)(self + 0x6c) = 0;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440((int)self, 0));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    *(int *)(self + 0x394) = func_0203bee8(*(int *)(self + 0x384), 3, data_ov151_020cec6c);
    *(int *)(self + 0x398) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov151_020cec70);
    *(int *)(self + 0x2cc) = *(int *)(self + 0x398) + 0x14;
    *(int *)(self + 0x3cc) = func_ov107_020c9e50(func_ov107_020c9440((int)self, 1), data_ov151_020cec78);
    *(void **)(self + 0x390) = func_0203d15c(0x28);
    for (i = 0; i < 5; i++) {
        (*(struct Ov151SubitemSlot **)(self + 0x390))[i].pItem =
            func_0203b898(func_ov107_020c9440((int)self, pools.id[i]));
        func_ov107_020c9074(self, (*(struct Ov151SubitemSlot **)(self + 0x390))[i].pItem);
        *(int *)((*(struct Ov151SubitemSlot **)(self + 0x390))[i].pItem + 0x5c) |= 2;
    }
    func_ov107_020c92b0(self, 0, 1, 0, 0x2999);
    func_ov107_020c92b0(self, 1, 1, 0, 0x2999);
    func_ov107_020c92b0(self, 2, 1, 0, 0x2999);
    func_ov107_020c92b0(self, 4, 1, 0, 0x2999);
    pose.pos = data_02041dc8;
    pose.scale = 0xc00;
    *(int **)(self + 0x388) = func_01fffca8(self + 0x22c, 0x10, 0x64);
    **(int **)(self + 0x388) = func_ov107_020c319c(&pose);
    p = func_01fffca8(self + 0x144, 4, 0x64);
    *(int *)(self + 0x38c) = *p = func_ov107_020c319c(&pose);
    *(void **)(self + 0x3c8) = func_0203d15c(0xc);
    for (i = 0; i < 3; i++) {
        (*(int **)(self + 0x3c8))[i] = func_ov151_020cc994(self);
    }
    func_0203355c(0x14f);
}
