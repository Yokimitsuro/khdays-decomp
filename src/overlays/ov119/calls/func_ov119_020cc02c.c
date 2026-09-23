/* Constructor of the ov119 enemy (x3 with ov272/ov279). Installs the handlers (+8, +0x1c message,
 * +0x30, +0x34 tick, +0x1d0 hit filter, +0x1dc, +0x1e0), raises bit 6 of the +0x60 high byte, sets
 * the +0x64 pose (scale 0.56), builds the +0x384 rig from pose 0 (subscribed to +0x9c, callback
 * func_ov119_020cbfc4 with the enemy as its +0x84 owner) and resolves its five bones (+0x390 in set
 * 3; +0x398, +0x394, +0x39c, +0x3a0 in set 1); builds the five sub-items of data_ov119_020cf94c
 * into the +0x3a8 pair table (registered, bit 1 of +0x5c), registers actions 0, 1, 2 and 4 with
 * mode 1 (rate 1.13), reserves the +0x22c capsule (+0x388) and one +0x144 capsule (+0x38c, its
 * body at +0x2cc) of length 1.0 and radius 0.56 along +Y, and loads sound 0x121. */
typedef struct { int x, y, z; } VecFx32;
typedef struct { void *node; int pad; } Slot;
typedef struct { int w[5]; } KindTable;
typedef struct { VecFx32 pos; VecFx32 axis; int length; int radius; } Capsule;

extern void *func_ov107_020c9440(void *self, int slot);
extern void *func_0203b898(void *res);
extern void func_0203bfb4(void *list, void *node);
extern int func_0203bee8(void *obj, int set, const char *name);
extern void *func_0203d15c(int size);
extern void func_ov107_020c9074(void *self, void *obj);
extern void func_ov107_020c92b0(void *self, int a, int b, const VecFx32 *v, int e);
extern void *func_01fffca8(void *list, int size, int count);
extern void *func_ov107_020c3210(const Capsule *capsule);
extern void func_0203355c(int id);

extern KindTable data_ov119_020cf94c;
extern const char data_ov119_020cf98c[];
extern const char data_ov119_020cf998[];
extern const char data_ov119_020cf9a4[];
extern const char data_ov119_020cf9b0[];
extern const char data_ov119_020cf9bc[];
extern const VecFx32 data_02041dc8;
extern const VecFx32 data_02042264;

extern void func_ov119_020cc2ec(void);
extern void func_ov119_020cc3a8(void);
extern void func_ov119_020cc534(void);
extern void func_ov119_020cc768(void);
extern void func_ov119_020cc7c4(void);
extern void func_ov119_020cc9d0(void);
extern void func_ov119_020cc32c(void);
extern void func_ov119_020cbfc4(void);

void func_ov119_020cc02c(char *self)
{
    KindTable kinds;
    Capsule cap;
    int i;

    kinds = data_ov119_020cf94c;
    *(void **)(self + 0x8) = (void *)func_ov119_020cc2ec;
    *(void **)(self + 0x1c) = (void *)func_ov119_020cc3a8;
    *(void **)(self + 0x34) = (void *)func_ov119_020cc534;
    *(void **)(self + 0x30) = (void *)func_ov119_020cc768;
    *(void **)(self + 0x1d0) = (void *)func_ov119_020cc7c4;
    *(void **)(self + 0x1e0) = (void *)func_ov119_020cc9d0;
    *(void **)(self + 0x1dc) = (void *)func_ov119_020cc32c;
    {
        unsigned int v = *(unsigned short *)(self + 0x60);
        *(unsigned short *)(self + 0x60) = (unsigned short)((v & ~0xff00) | ((((v << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10));
    }
    *(int *)(self + 0x70) = 0x900;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0x900;
    *(int *)(self + 0x6c) = 0;

    *(void **)(self + 0x384) = func_0203b898(func_ov107_020c9440(self, 0));
    func_0203bfb4(*(void **)(self + 0x9c), *(void **)(self + 0x384));
    *(void **)(*(char **)(self + 0x384) + 0x74) = (void *)func_ov119_020cbfc4;
    *(char **)(*(char **)(self + 0x384) + 0x84) = self;
    *(int *)(self + 0x390) = func_0203bee8(*(void **)(self + 0x384), 3, data_ov119_020cf98c);
    *(int *)(self + 0x398) = func_0203bee8(*(void **)(self + 0x384), 1, data_ov119_020cf998);
    *(int *)(self + 0x394) = func_0203bee8(*(void **)(self + 0x384), 1, data_ov119_020cf9a4);
    *(int *)(self + 0x39c) = func_0203bee8(*(void **)(self + 0x384), 1, data_ov119_020cf9b0);
    *(int *)(self + 0x3a0) = func_0203bee8(*(void **)(self + 0x384), 1, data_ov119_020cf9bc);
    *(void **)(self + 0x3a8) = func_0203d15c(0x28);
    for (i = 0; i < 5; i++) {
        (*(Slot **)(self + 0x3a8))[i].node = func_0203b898(func_ov107_020c9440(self, kinds.w[i]));
        func_ov107_020c9074(self, (*(Slot **)(self + 0x3a8))[i].node);
        *(int *)((char *)(*(Slot **)(self + 0x3a8))[i].node + 0x5c) |= 2;
    }
    func_ov107_020c92b0(self, 0, 1, 0, 0x1200);
    func_ov107_020c92b0(self, 1, 1, 0, 0x1200);
    func_ov107_020c92b0(self, 2, 1, 0, 0x1200);
    func_ov107_020c92b0(self, 4, 1, 0, 0x1200);

    cap.pos = data_02041dc8;
    cap.axis = data_02042264;
    cap.length = 0x1000;
    cap.radius = 0x900;
    *(void **)(self + 0x388) = func_01fffca8(self + 0x22c, 0x10, 100);
    **(void ***)(self + 0x388) = func_ov107_020c3210(&cap);
    {
        void **slot = (void **)func_01fffca8(self + 0x144, 4, 100);
        void *node = func_ov107_020c3210(&cap);
        *slot = node;
        *(void **)(self + 0x38c) = node;
        *(char **)(self + 0x2cc) = (char *)node + 4;
    }
    func_0203355c(0x121);
}
