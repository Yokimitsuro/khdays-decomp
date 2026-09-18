/* func_ov245_020d5538 -- constructor of the ov245 rider: installs the handlers (+8 tick, +0xc
 * draw, +0x1c message, +0x30 / +0x34 callbacks, +0x1d0 hit, +0x1dc finish), seeds the +0x64
 * pose at scale 0.5, builds the primary item from pool entry 0x26 of the +0x3cc pool (+0x384,
 * subscribed) with four named joints (+0x390..+0x39c), binds pool entry 0x27 as its motion
 * (+0x3a8 track, slot 0xc) and the named motion of entry 0x32 (+0x3a0), registers reactions
 * 1/1 and 2/1 at 1.5, then a fresh 40-byte slot table (+0x3a4) holding five sub-items: the
 * first two from the shared +0x88 model base (kinds from the data_ov245_020d71b0 table), the
 * rest from pool entries listed there, all attached (bit 1 of +0x5c). Two placements at the
 * origin (scale 0.5) go on the +0x22c list (+0x388) and the +0x144 list (+0x38c); sound 0x11a
 * is loaded. */
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 pos; int scale; } Pose;
typedef void (*Callback)(void);
struct PoolIds { int id[5]; };
struct Ov245Slot { int pItem; int pad4; };
struct Ov245Model { char pad[0x88]; int track; };

extern void func_ov245_020d57ec(void);
extern void func_ov245_020d583c(void);
extern void func_ov245_020d58b4(void);
extern void func_ov245_020d5af4(void);
extern void func_ov245_020d5a74(void);
extern void func_ov245_020d5b50(void);
extern void func_ov245_020d59f8(void);
extern void *func_ov107_020c9440(int pool, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern int func_0203bee8(int item, int kind, const char *name);
extern void func_0202a388(void *track, int model, void *resource, int slot);
extern void func_0203b9ac(int item, void *track);
extern int func_ov107_020c9e50(void *item, const char *name);
extern void func_ov107_020c92b0(int self, int a, int b, Vec3 *lift, int id);
extern void *func_0203d15c(int size);
extern void *OS_IsThreadAvailable_0x020c9848(void);
extern void func_ov107_020c9074(int self, int item);
extern int *func_01fffca8(void *list, int stride, int max);
extern int func_ov107_020c319c(void *pose);
extern void func_0203355c(int id);
extern const struct PoolIds data_ov245_020d71b0;
extern const char data_ov245_020d7268[];
extern const char data_ov245_020d7274[];
extern const char data_ov245_020d7284[];
extern const char data_ov245_020d7294[];
extern const char data_ov245_020d729c[];
extern const Vec3 data_02041dc8;

void func_ov245_020d5538(int selfArg) {
    char *self = (char *)selfArg;   /* codegen: the local copy keeps `mov r1,#1` in the call shadow */
    struct PoolIds pools;
    Pose pose;
    int *slot;
    int i;

    pools = data_ov245_020d71b0;
    *(Callback *)(self + 0x8) = func_ov245_020d57ec;
    *(Callback *)(self + 0xc) = func_ov245_020d583c;
    *(Callback *)(self + 0x1c) = func_ov245_020d58b4;
    *(Callback *)(self + 0x30) = func_ov245_020d5af4;
    *(Callback *)(self + 0x34) = func_ov245_020d5a74;
    *(Callback *)(self + 0x1d0) = func_ov245_020d5b50;
    *(Callback *)(self + 0x1dc) = func_ov245_020d59f8;
    *(int *)(self + 0x70) = 0x800;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0x800;
    *(int *)(self + 0x6c) = 0;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(*(int *)(self + 0x3cc), 0x26));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    *(int *)(self + 0x390) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov245_020d7268);
    *(int *)(self + 0x394) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov245_020d7274);
    *(int *)(self + 0x398) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov245_020d7284);
    *(int *)(self + 0x39c) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov245_020d7294);
    func_0202a388((void *)(self + 0x3a8), ((struct Ov245Model *)*(int *)(self + 0x384))->track,
                  func_ov107_020c9440(*(int *)(self + 0x3cc), 0x27), 0xc);
    func_0203b9ac(*(int *)(self + 0x384), (void *)(self + 0x3a8));
    *(int *)(self + 0x3a0) = func_ov107_020c9e50(func_ov107_020c9440(*(int *)(self + 0x3cc), 0x32), data_ov245_020d729c);
    func_ov107_020c92b0(self, 1, 1, 0, 0x1800);
    func_ov107_020c92b0(self, 2, 1, 0, 0x1800);
    *(void **)(self + 0x3a4) = func_0203d15c(0x28);
    for (i = 0; i < 5; i++) {
        void *node;
        if (i < 2) {
            void *os = OS_IsThreadAvailable_0x020c9848();
            unsigned int kind = pools.id[i] & 0x1ff;
            unsigned int addr = (*(int *)((char *)os + 0x88) + 0x8000) & 0x00fffffc;
            addr = addr << 7;
            addr = addr | 0x80000000;
            node = func_0203b898((void *)(kind | addr));
        } else {
            node = func_0203b898(func_ov107_020c9440(*(int *)(self + 0x3cc), pools.id[i]));
        }
        (*(struct Ov245Slot **)(self + 0x3a4))[i].pItem = (int)node;
        func_ov107_020c9074(self, (*(struct Ov245Slot **)(self + 0x3a4))[i].pItem);
        *(int *)((*(struct Ov245Slot **)(self + 0x3a4))[i].pItem + 0x5c) |= 2;
    }
    pose.pos = data_02041dc8;
    pose.scale = 0x800;
    *(int **)(self + 0x388) = func_01fffca8((void *)(self + 0x22c), 0x10, 0x64);
    **(int **)(self + 0x388) = func_ov107_020c319c(&pose);
    slot = func_01fffca8((void *)(self + 0x144), 4, 0x64);
    *(int *)(self + 0x38c) = *slot = func_ov107_020c319c(&pose);
    func_0203355c(0x11a);
}
