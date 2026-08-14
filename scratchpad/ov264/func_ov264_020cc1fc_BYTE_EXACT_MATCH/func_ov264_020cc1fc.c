typedef unsigned short u16;
typedef struct { int x, y, z; } VecFx32;
typedef struct { void *node; int pad; } Slot;
typedef struct { int w[5]; } KindTable;
typedef struct { int w[6]; } ParamBlock;
typedef struct { VecFx32 v; int w; } SpawnSeed;

extern void *func_ov107_020c9440(void *self, int slot);
extern void *func_0203b898(void *res);
extern void func_0203bfb4(void *list, void *node);
extern void func_0202a388(void *dst, void *a, void *b, int n);
extern void func_0203b9ac(void *obj, void *block);
extern int func_0203bdfc(void *obj, const char *name);
extern void func_0203c7ac(void *obj, int a);
extern void func_ov107_020c92b0(void *self, int a, int b, const VecFx32 *v, int e);
extern void *OS_IsThreadAvailable_0x020c9848(void);
extern void func_ov107_020c9074(void *self, void *obj);
extern void *func_0203c1b0(void *res, int n);
extern void *func_ov264_020ce9fc(void *self);
extern void *func_01fffca8(void *list, int size, int count);
extern void *func_ov107_020c319c(const SpawnSeed *seed);
extern void func_0203355c(int id);

extern KindTable data_ov264_020cebc4;
extern const char data_ov264_020cec2c[];
extern const char data_ov264_020cec38[];
extern const VecFx32 data_02041dc8;

extern void func_ov264_020cbfc8(void);
extern void func_ov264_020cc09c(void);
extern void func_ov264_020cc5c4(void);
extern void func_ov264_020cc61c(void);
extern void func_ov264_020cc6a8(void);
extern void func_ov264_020cca58(void);
extern void func_ov264_020cc8e4(void);
extern void func_ov264_020ccab4(void);
extern void func_ov264_020cc9e0(void);
extern void func_ov264_020ccde8(void);
extern void func_ov264_020cce14(void);
void func_ov264_020cc1fc(char *self)
{
    KindTable kinds;
    ParamBlock params;
    SpawnSeed seed;
    VecFx32 velocity;
    int i;

    kinds = data_ov264_020cebc4;
    params.w[0] = -0x190b;
    params.w[1] = -6;
    params.w[2] = -0x1fc4;
    params.w[3] = params.w[0] + 0x3217;
    params.w[4] = params.w[1] + 0x2cc3;
    params.w[5] = params.w[2] + 0x2597;
    *(void **)(self + 0x8) = (void *)func_ov264_020cc5c4;
    *(void **)(self + 0xc) = (void *)func_ov264_020cc61c;
    *(void **)(self + 0x1c) = (void *)func_ov264_020cc6a8;
    *(void **)(self + 0x30) = (void *)func_ov264_020cca58;
    *(void **)(self + 0x34) = (void *)func_ov264_020cc8e4;
    *(void **)(self + 0x1d0) = (void *)func_ov264_020ccab4;
    *(void **)(self + 0x1dc) = (void *)func_ov264_020cc9e0;
    *(void **)(self + 0x1e0) = (void *)func_ov264_020ccde8;
    *(void **)(self + 0x1e4) = (void *)func_ov264_020cce14;
    *(int *)(self + 0x70) = 0x1400;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0x1400;
    *(int *)(self + 0x6c) = 0;
    *(ParamBlock *)(self + 0x1fc) = params;
    *(char *)(self + 0x1c9) = 1;
    {
        unsigned int v = *(u16 *)(self + 0x60);
        unsigned int low = v & ~0xff00;
        v <<= 16;
        v >>= 24;
        v |= 0x20;
        v <<= 24;
        v >>= 16;
        v |= low;
        *(u16 *)(self + 0x60) = (u16)v;
        *(u16 *)(self + 0x1ae) |= 8;
    }

    {
        void *rig = func_0203b898(func_ov107_020c9440(self, 0));
        *(void **)(self + 0x384) = rig;
        *(void **)((char *)rig + 0x74) = (void *)func_ov264_020cbfc8;
    }
    *(char **)(*(char **)(self + 0x384) + 0x84) = self;
    func_0203bfb4(*(void **)(self + 0x9c), *(void **)(self + 0x384));

    {
    void *anim = func_ov107_020c9440(self, 1);
    func_0202a388(self + 0x388, *(void **)(*(char **)(self + 0x384) + 0x88), anim, 0xc);
    func_0203b9ac(*(void **)(self + 0x384), self + 0x388);
    *(int *)(self + 0x438) = func_0203bdfc(*(void **)(self + 0x384), data_ov264_020cec2c);

    {
        *(void **)(self + 0x420) = func_0203b898(func_ov107_020c9440(self, 0xa));
        *(void **)(*(char **)(self + 0x420) + 0x6c) = (void *)func_ov264_020cc09c;
        *(char **)(*(char **)(self + 0x420) + 0x84) = self;
        func_0203c7ac(*(void **)(self + 0x420), 0);
        *(int *)(self + 0x434) = func_0203bdfc(*(void **)(self + 0x420), data_ov264_020cec38);
    }

    }

    velocity.x = 0;
    velocity.y = 0x1400;
    velocity.z = 0;
    func_ov107_020c92b0(self, 0, 2, &velocity, 0xc00);
    velocity.x = 0;
    velocity.z = 0;
    velocity.y = -0x1400;
    func_ov107_020c92b0(self, 2, 3, &velocity, 0x99a);
    func_ov107_020c92b0(self, 1, 2, 0, 0xccd);

    for (i = 0; i < 5; i++) {
        void *node;
        if (i <= 0) {
            void *os = OS_IsThreadAvailable_0x020c9848();
            unsigned int kind = kinds.w[i] & 0x1ff;
            unsigned int addr = (*(int *)((char *)os + 0x88) + 0x8000) & 0x00fffffc;
            addr = addr << 7;
            addr = addr | 0x80000000;
            node = func_0203b898((void *)(kind | addr));
        } else {
            node = func_0203b898(func_ov107_020c9440(self, kinds.w[i]));
        }
        func_ov107_020c9074(self, (((Slot *)(self + 0x440))[i].node = node));
        *(int *)((char *)((Slot *)(self + 0x440))[i].node + 0x5c) |= 2;
    }

    *(void **)(self + 0x3c4) = func_0203c1b0(func_ov107_020c9440(self, 0xe), 0x22);
    func_ov107_020c9074(self, *(void **)(self + 0x3c4));
    *(int *)(*(char **)(self + 0x3c4) + 0x5c) |= 2;
    *(void **)(self + 0x3c0) = func_ov264_020ce9fc(self);

    seed = *(SpawnSeed *)(self + 0x64);
    seed.v = data_02041dc8;
    *(void **)(self + 0x3ac) = func_01fffca8(self + 0x22c, 0x10, 100);
    **(void ***)(self + 0x3ac) = func_ov107_020c319c(&seed);
    {
        void **slot = (void **)func_01fffca8(self + 0x144, 4, 100);
        void *node = func_ov107_020c319c(&seed);
        *slot = node;
        *(void **)(self + 0x3b0) = node;
    }
    func_0203355c(0x15d);
}