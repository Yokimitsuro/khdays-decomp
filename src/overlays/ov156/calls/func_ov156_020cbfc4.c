/* Constructor of the ov156 enemy (and its byte-identical twin): sets bit 8 of the +0 flags,
 * installs the handlers (+8 tick, +0x1c message, +0x30/+0x28/+0x2c/+0x10/+0x34 callbacks, +0x1e0
 * callback, +0x1d0 hit, +0x1dc finish), seeds the +0x64 pose (scale 0xb00, y 0xb00) and bit 4 of
 * +0x1ae; builds the primary item from pool entry 0 (+0x384, subscribed) with two named
 * attachments (+0x398/+0x39c), the four sub-items listed by the overlay's +0xed80 table into a
 * fresh 32-byte slot table (+0x3a0, attached, bit 1), registers four reactions (0/1/2/4 at the
 * +0xed74 lift), two placements on the +0x144 list (+0x390 at the origin with scale 0x500,
 * +0x394 at y 0xb00 with scale 0xb00) and two on the +0x22c list (+0x38c at the origin with
 * scale 0xd33, +0x388 at y 0xb00 with scale 0x266, bit 1 raised on its +8 flags), two held items
 * (cdee4) into an 8-byte table (+0x3a4) and loads sound 0x13d. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef void (*Callback)(void);

struct bf { unsigned int b : 8; };

struct PoolIds {
    int id[4];
};

struct Pose {
    Vec3 pos;
    int scale;
};

struct Ov156SubitemSlot {
    int pItem;
    int pad4;
};

extern void func_ov156_020cc334(void);
extern void func_ov156_020cc3cc(void);
extern void func_ov156_020cc770(void);
extern void func_ov156_020cc568(void);
extern void func_ov156_020cc5a4(void);
extern void func_ov156_020cc5e0(void);
extern void func_ov156_020cc624(void);
extern void func_ov156_020cc994(void);
extern void func_ov156_020cc7bc(void);
extern void func_ov156_020cc37c(void);
extern void *func_ov107_020c9440(int pool, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern int func_0203bee8(int item, int a, const char *name);
extern void *func_0203d15c(int size);
extern void func_ov107_020c9074(char *self, int item);
extern void func_ov107_020c92b0(char *self, int a, int b, Vec3 *lift, int id);
extern int *func_01fffca8(void *list, int stride, int max);
extern int func_ov107_020c319c(struct Pose *pose);
extern int func_ov156_020cdee4(char *self);
extern void func_0203355c(int id);
extern const struct PoolIds data_ov156_020ced80;
extern const Vec3 data_ov156_020ced74;
extern const char data_ov156_020cedec[];
extern const char data_ov156_020cedf4[];
extern const Vec3 data_02041dc8;

void func_ov156_020cbfc4(char *self)
{
    struct PoolIds pools;
    struct Pose pose;
    Vec3 lift;
    Vec3 zero;
    int *p;
    int i;

    pools = data_ov156_020ced80;
    lift = data_ov156_020ced74;
    *(u16 *)self |= 0x100;
    *(Callback *)(self + 0x8) = func_ov156_020cc334;
    *(Callback *)(self + 0x1c) = func_ov156_020cc3cc;
    *(Callback *)(self + 0x30) = func_ov156_020cc770;
    *(Callback *)(self + 0x28) = func_ov156_020cc568;
    *(Callback *)(self + 0x2c) = func_ov156_020cc5a4;
    *(Callback *)(self + 0x10) = func_ov156_020cc5e0;
    *(Callback *)(self + 0x34) = func_ov156_020cc624;
    *(Callback *)(self + 0x1e0) = func_ov156_020cc994;
    *(Callback *)(self + 0x1d0) = func_ov156_020cc7bc;
    *(Callback *)(self + 0x1dc) = func_ov156_020cc37c;
    *(int *)(self + 0x70) = 0xb00;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0xb00;
    *(int *)(self + 0x6c) = 0;
    *(u16 *)(self + 0x100 + 0xae) |= 0x10;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440((int)self, 0));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    *(int *)(self + 0x398) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov156_020cedec);
    *(int *)(self + 0x39c) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov156_020cedf4);
    *(void **)(self + 0x3a0) = func_0203d15c(0x20);
    for (i = 0; i < 4; i++) {
        (*(struct Ov156SubitemSlot **)(self + 0x3a0))[i].pItem =
            func_0203b898(func_ov107_020c9440((int)self, pools.id[i]));
        func_ov107_020c9074(self, (*(struct Ov156SubitemSlot **)(self + 0x3a0))[i].pItem);
        *(int *)((*(struct Ov156SubitemSlot **)(self + 0x3a0))[i].pItem + 0x5c) |= 2;
    }
    func_ov107_020c92b0(self, 0, 1, &lift, 0x3e66);
    func_ov107_020c92b0(self, 1, 1, &lift, 0x1f33);
    func_ov107_020c92b0(self, 2, 1, &lift, 0x1f33);
    func_ov107_020c92b0(self, 4, 1, &lift, 0x1f33);
    zero = data_02041dc8;
    pose.pos = zero;
    pose.scale = 0x500;
    p = func_01fffca8(self + 0x144, 4, 0x64);
    *(int *)(self + 0x390) = *p = func_ov107_020c319c(&pose);
    pose.pos = zero;
    pose.scale = 0xd33;
    *(int **)(self + 0x38c) = func_01fffca8(self + 0x22c, 0x10, 0x64);
    **(int **)(self + 0x38c) = func_ov107_020c319c(&pose);
    pose.pos.x = 0;
    pose.pos.y = 0xb00;
    pose.pos.z = 0;
    pose.scale = 0xb00;
    p = func_01fffca8(self + 0x144, 4, 0x64);
    *(int *)(self + 0x394) = *p = func_ov107_020c319c(&pose);
    pose.pos.x = 0;
    pose.pos.y = 0xb00;
    pose.pos.z = 0;
    pose.scale = 0x266;
    *(int **)(self + 0x388) = func_01fffca8(self + 0x22c, 0x10, 0x64);
    **(int **)(self + 0x388) = func_ov107_020c319c(&pose);
    ((struct bf *)(*(int *)(self + 0x388) + 8))->b |= 2;
    *(void **)(self + 0x3a4) = func_0203d15c(8);
    for (i = 0; i < 2; i++) {
        (*(int **)(self + 0x3a4))[i] = func_ov156_020cdee4(self);
    }
    func_0203355c(0x13d);
}
