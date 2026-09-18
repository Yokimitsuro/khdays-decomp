/* Constructor of the ov204 enemy (and its byte-identical twin ov205; variant of the ov139/140
 * constructor): installs the handlers (+8 tick, +0xc draw, +0x1c message, +0x30 callback,
 * +0x1d0 hit, +0x1e0 callback, +0x1dc finish), clears +0x1f4 and seeds the +0x64 pose (scale
 * 0x1000, y 0x1000); builds the primary item from pool entry 0 (+0x384, subscribed), keeps the
 * named motion handle from pool entry 1 (+0x390), the seven sub-items listed by the overlay's
 * 0x020d35e0 table into a fresh 56-byte slot table (+0x394, attached, bit 1), registers four
 * reactions (id 0x3000: 0/1 at the 0x020d35c4 lift, 1/1, 2/1 and 4/1 without one) and two
 * placements on the +0x22c/+0x144 lists (+0x388/+0x38c) from the +0x64 pose, then loads sound
 * 0x132. */
typedef struct { int x, y, z; } Vec3;
typedef void (*Callback)(void);

struct PoolIds {
    int id[7];
};

struct Ov139SubitemSlot {
    int pItem;
    int pad4;
};

extern void func_ov204_020cfe08(void);
extern void func_ov204_020cfe50(void);
extern void func_ov204_020cfef0(void);
extern void func_ov204_020d0100(void);
extern void func_ov204_020d014c(void);
extern void func_ov204_020d03b4(void);
extern void func_ov204_020cfec0(void);
extern void *func_ov107_020c9440(int pool, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern int func_ov107_020c9e50(void *item, const char *name);
extern void *func_0203d15c(int size);
extern void func_ov107_020c9074(char *self, int item);
extern void func_ov107_020c92b0(char *self, int a, int b, Vec3 *lift, int id);
extern int *func_01fffca8(void *list, int stride, int max);
extern int func_ov107_020c319c(char *pose);
extern void func_0203355c(int id);
extern const struct PoolIds data_ov204_020d35e0;
extern const Vec3 data_ov204_020d35c4;
extern const char data_ov204_020d36ac[];

void func_ov204_020cfc04(char *self)
{
    struct PoolIds pools;
    Vec3 lift;
    int *p;
    int i;

    pools = data_ov204_020d35e0;
    lift = data_ov204_020d35c4;
    *(Callback *)(self + 0x8) = func_ov204_020cfe08;
    *(Callback *)(self + 0xc) = func_ov204_020cfe50;
    *(Callback *)(self + 0x1c) = func_ov204_020cfef0;
    *(Callback *)(self + 0x30) = func_ov204_020d0100;
    *(Callback *)(self + 0x1d0) = func_ov204_020d014c;
    *(Callback *)(self + 0x1e0) = func_ov204_020d03b4;
    *(Callback *)(self + 0x1dc) = func_ov204_020cfec0;
    *(int *)(self + 0x1f4) = 0;
    *(int *)(self + 0x70) = 0x1000;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0x1000;
    *(int *)(self + 0x6c) = 0;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440((int)self, 0));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    *(int *)(self + 0x390) = func_ov107_020c9e50(func_ov107_020c9440((int)self, 1), data_ov204_020d36ac);
    *(void **)(self + 0x394) = func_0203d15c(0x38);
    for (i = 0; i < 7; i++) {
        (*(struct Ov139SubitemSlot **)(self + 0x394))[i].pItem =
            func_0203b898(func_ov107_020c9440((int)self, pools.id[i]));
        func_ov107_020c9074(self, (*(struct Ov139SubitemSlot **)(self + 0x394))[i].pItem);
        *(int *)((*(struct Ov139SubitemSlot **)(self + 0x394))[i].pItem + 0x5c) |= 2;
    }
    func_ov107_020c92b0(self, 0, 1, &lift, 0x3000);
    func_ov107_020c92b0(self, 1, 1, 0, 0x3000);
    func_ov107_020c92b0(self, 2, 1, 0, 0x3000);
    func_ov107_020c92b0(self, 4, 1, 0, 0x3000);
    *(int **)(self + 0x388) = func_01fffca8(self + 0x22c, 0x10, 0x64);
    **(int **)(self + 0x388) = func_ov107_020c319c(self + 0x64);
    p = func_01fffca8(self + 0x144, 4, 0x64);
    *(int *)(self + 0x38c) = *p = func_ov107_020c319c(self + 0x64);
    func_0203355c(0x132);
}
