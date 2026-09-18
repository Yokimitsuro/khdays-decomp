/* Constructor of the ov250 enemy (and its byte-identical twin): installs the handlers (+8 tick,
 * +0xc draw, +0x20/+0x1c message callbacks, +0x30/+0x34 callbacks, +0x1e0 callback, +0x1d0 hit,
 * +0x1dc finish), copies the overlay's bounding box into +0x1fc, seeds the +0x64 pose (scale
 * 0x2120, y 0x2120) and bits 3/4 of +0x1ae; builds the primary item from pool entry 0 (+0x384,
 * its +4 block configured with 0x80, subscribed) with three named attachments (+0x39c/+0x3a0/
 * +0x3a4), keeps the named motion handle from pool entry 1 (+0x390), the three sub-items listed
 * by the overlay's +0x2890 table into a fresh 24-byte slot table (+0x398, attached, bit 1),
 * registers reaction 2/2 (id 0x2120) and two placements on the +0x22c/+0x144 lists (+0x388/
 * +0x38c) from the pose at the origin, then loads sound 0x159. */
typedef struct { int x, y, z; } Vec3;
typedef void (*Callback)(void);

struct PoolIds {
    int id[3];
};

struct Box {
    int xmin, ymin, zmin;
    int xmax, ymax, zmax;
};

struct Pose {
    Vec3 pos;
    int scale;
};

struct Ov250SubitemSlot {
    int pItem;
    int pad4;
};

extern void func_ov251_020d3aa4(void);
extern void func_ov251_020d3aec(void);
extern void func_ov251_020d3b40(void);
extern void func_ov251_020d3ba4(void);
extern void func_ov251_020d3d30(void);
extern void func_ov251_020d3cc8(void);
extern void func_ov251_020d3fd4(void);
extern void func_ov251_020d3d7c(void);
extern void func_ov251_020d3b10(void);
extern void *func_ov107_020c9440(int pool, int index);
extern int func_0203b898(void *item);
extern void func_0203ca14(void *block, int a, int b, int c);
extern int func_0203bfb4(int subscriber, int item);
extern int func_0203bee8(int item, int a, const char *name);
extern int func_ov107_020c9e50(void *item, const char *name);
extern void *func_0203d15c(int size);
extern void func_ov107_020c9074(char *self, int item);
extern void func_ov107_020c92b0(char *self, int a, int b, void *lift, int id);
extern int *func_01fffca8(void *list, int stride, int max);
extern int func_ov107_020c319c(struct Pose *pose);
extern void func_0203355c(int id);
extern const struct PoolIds data_ov251_020d64d0;
extern const struct Box data_ov251_020d64dc;
extern const char data_ov251_020d654c[];
extern const char data_ov251_020d6554[];
extern const char data_ov251_020d6564[];
extern const char data_ov251_020d6574[];
extern const Vec3 data_02041dc8;

void func_ov251_020d3844(char *self)
{
    struct PoolIds pools;
    struct Pose pose;
    int *p;
    int i;

    pools = data_ov251_020d64d0;
    *(Callback *)(self + 0x8) = func_ov251_020d3aa4;
    *(Callback *)(self + 0xc) = func_ov251_020d3aec;
    *(Callback *)(self + 0x20) = func_ov251_020d3b40;
    *(Callback *)(self + 0x1c) = func_ov251_020d3ba4;
    *(Callback *)(self + 0x30) = func_ov251_020d3d30;
    *(Callback *)(self + 0x34) = func_ov251_020d3cc8;
    *(Callback *)(self + 0x1e0) = func_ov251_020d3fd4;
    *(Callback *)(self + 0x1d0) = func_ov251_020d3d7c;
    *(Callback *)(self + 0x1dc) = func_ov251_020d3b10;
    *(struct Box *)(self + 0x1fc) = data_ov251_020d64dc;
    *(int *)(self + 0x70) = 0x2120;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0x2120;
    *(int *)(self + 0x6c) = 0;
    *(unsigned short *)(self + 0x100 + 0xae) |= 0x18;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440((int)self, 0));
    func_0203ca14((void *)(*(int *)(self + 0x384) + 4), 0, 0x80, 0);
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    *(int *)(self + 0x39c) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov251_020d654c);
    *(int *)(self + 0x3a0) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov251_020d6554);
    *(int *)(self + 0x3a4) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov251_020d6564);
    pose = *(struct Pose *)(self + 0x64);
    pose.pos = data_02041dc8;
    *(int *)(self + 0x390) = func_ov107_020c9e50(func_ov107_020c9440((int)self, 1), data_ov251_020d6574);
    *(void **)(self + 0x398) = func_0203d15c(0x18);
    for (i = 0; i < 3; i++) {
        (*(struct Ov250SubitemSlot **)(self + 0x398))[i].pItem =
            func_0203b898(func_ov107_020c9440((int)self, pools.id[i]));
        func_ov107_020c9074(self, (*(struct Ov250SubitemSlot **)(self + 0x398))[i].pItem);
        *(int *)((*(struct Ov250SubitemSlot **)(self + 0x398))[i].pItem + 0x5c) |= 2;
    }
    func_ov107_020c92b0(self, 2, 2, 0, 0x2120);
    *(int **)(self + 0x388) = func_01fffca8(self + 0x22c, 0x10, 0x64);
    **(int **)(self + 0x388) = func_ov107_020c319c(&pose);
    p = func_01fffca8(self + 0x144, 4, 0x64);
    *(int *)(self + 0x38c) = *p = func_ov107_020c319c(&pose);
    func_0203355c(0x159);
}
