/* Constructor of the ov139 enemy (and its byte-identical twin): installs the handlers (+8 tick,
 * +0xc draw, +0x1c message, +0x30 callback, +0x1d0 hit, +0x1e0 callback, +0x1dc finish), clears
 * +0x1f4 and seeds the +0x64 pose (scale 0x800, y 0x800); builds the primary item from pool
 * entry 0 (+0x384, subscribed), keeps the named motion handle from pool entry 1 (+0x390), the
 * three sub-items listed by the overlay's +0xebfc table into a fresh 24-byte slot table (+0x394,
 * attached, bit 1), registers four reactions (id 0x1800: 0/1 at the +0xec08 lift, 1/1, 2/1 and 4/1 without one) and two
 * placements on the +0x22c/+0x144 lists (+0x388/+0x38c) from the +0x64 pose, then loads sound
 * 0x11f. */
typedef struct { int x, y, z; } Vec3;
typedef void (*Callback)(void);

struct PoolIds {
    int id[3];
};

struct Ov139SubitemSlot {
    int pItem;
    int pad4;
};

extern void func_ov139_020cc1c0(void);
extern void func_ov139_020cc208(void);
extern void func_ov139_020cc2a8(void);
extern void func_ov139_020cc398(void);
extern void func_ov139_020cc3e4(void);
extern void func_ov139_020cc654(void);
extern void func_ov139_020cc278(void);
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
extern const struct PoolIds data_ov139_020cebfc;
extern const Vec3 data_ov139_020cec08;
extern const char data_ov139_020cec8c[];

void func_ov139_020cbfc4(char *self)
{
    struct PoolIds pools;
    Vec3 lift;
    int *p;
    int i;

    pools = data_ov139_020cebfc;
    lift = data_ov139_020cec08;
    *(Callback *)(self + 0x8) = func_ov139_020cc1c0;
    *(Callback *)(self + 0xc) = func_ov139_020cc208;
    *(Callback *)(self + 0x1c) = func_ov139_020cc2a8;
    *(Callback *)(self + 0x30) = func_ov139_020cc398;
    *(Callback *)(self + 0x1d0) = func_ov139_020cc3e4;
    *(Callback *)(self + 0x1e0) = func_ov139_020cc654;
    *(Callback *)(self + 0x1dc) = func_ov139_020cc278;
    *(int *)(self + 0x1f4) = 0;
    *(int *)(self + 0x70) = 0x800;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0x800;
    *(int *)(self + 0x6c) = 0;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440((int)self, 0));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    *(int *)(self + 0x390) = func_ov107_020c9e50(func_ov107_020c9440((int)self, 1), data_ov139_020cec8c);
    *(void **)(self + 0x394) = func_0203d15c(0x18);
    for (i = 0; i < 3; i++) {
        (*(struct Ov139SubitemSlot **)(self + 0x394))[i].pItem =
            func_0203b898(func_ov107_020c9440((int)self, pools.id[i]));
        func_ov107_020c9074(self, (*(struct Ov139SubitemSlot **)(self + 0x394))[i].pItem);
        *(int *)((*(struct Ov139SubitemSlot **)(self + 0x394))[i].pItem + 0x5c) |= 2;
    }
    func_ov107_020c92b0(self, 0, 1, &lift, 0x1800);
    func_ov107_020c92b0(self, 1, 1, 0, 0x1800);
    func_ov107_020c92b0(self, 2, 1, 0, 0x1800);
    func_ov107_020c92b0(self, 4, 1, 0, 0x1800);
    *(int **)(self + 0x388) = func_01fffca8(self + 0x22c, 0x10, 0x64);
    **(int **)(self + 0x388) = func_ov107_020c319c(self + 0x64);
    p = func_01fffca8(self + 0x144, 4, 0x64);
    *(int *)(self + 0x38c) = *p = func_ov107_020c319c(self + 0x64);
    func_0203355c(0x11f);
}
