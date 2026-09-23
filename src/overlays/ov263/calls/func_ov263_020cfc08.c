/* Constructor of the ov263 enemy (variant of ov231/ov232's). Installs the handlers (+8,
 * +0xc draw, +0x1c message, +0x28, +0x2c, +0x30, +0x34 update, +0x1d0 hit filter, +0x1dc, +0x1e0),
 * sets the +0x1fc bounds box (+/-2.0 wide, 4.0 tall), the +0x64 pose (scale 1.53) and bit 3 of
 * +0x1ae, builds the +0x384 rig from pose 0 (subscribed to +0x9c, 12-channel animation set 1 bound at
 * +0x394) and resolves its four bones (+0x3cc/+0x3d0 in set 1, +0x3d4/+0x3d8 in set 3); raises bit
 * 6 of the +0x60 high byte, keeps the "move" handle of set 0x11 (+0x388), builds the eight sub-items
 * of data_ov263_020d3674 into the +0x3b8 pair table (registered, bit 1 of +0x5c) and spawns the two
 * +0x38c children (func_ov263_020d2d88, bit 2 of their body's +0x5c). Registers actions 0/2, 1/2
 * and 4/2 lifted 1.5 above the +0xb0 point and 2/3 (all at rate 0.92); reserves the +0x22c
 * placement (+0x3bc) and the three +0x144 handles (+0x3c0: a placement, then two oriented boxes of
 * half-extents 0.5*1.53/0.25/0.5*1.53), and loads sound 0x168. */
typedef unsigned short u16;
typedef struct { int x, y, z; } VecFx32;
typedef struct { void *node; int pad; } Slot;
typedef struct { int w[8]; } KindTable;
typedef struct { int w[6]; } ParamBlock;
typedef struct { VecFx32 pos; int scale; } Placement;
typedef struct { VecFx32 center; VecFx32 ax; VecFx32 ay; VecFx32 az; int extent[3]; } Obb;

extern void *func_ov107_020c9440(void *self, int slot);
extern void *func_0203b898(void *res);
extern void func_0203bfb4(void *list, void *node);
extern void func_0202a388(void *dst, void *a, void *b, int n);
extern void func_0203b9ac(void *obj, void *block);
extern int func_0203bee8(void *obj, int set, const char *name);
extern int func_ov107_020c9e50(void *res, const char *name);
extern void *func_0203d15c(int size);
extern void func_ov107_020c9074(void *self, void *obj);
extern void *func_ov263_020d2d88(void *self);
extern void func_ov107_020c92b0(void *self, int a, int b, const VecFx32 *v, int e);
extern int FX_Inv(int num, int den);
extern void *func_01fffca8(void *list, int size, int count);
extern void *func_ov107_020c319c(const Placement *placement);
extern void *func_ov107_020c32b8(const Obb *box);
extern void func_0203355c(int id);

extern KindTable data_ov263_020d3674;
extern const char data_ov263_020d36cc[];
extern const char data_ov263_020d36d8[];
extern const char data_ov263_020d36e4[];
extern const char data_ov263_020d36f0[];
extern const char data_ov263_020d36fc[];
extern const VecFx32 data_02041dc8;
extern const VecFx32 data_02042270;
extern const VecFx32 data_02042264;
extern const VecFx32 data_02042258;

extern void func_ov263_020d009c(void);
extern void func_ov263_020d00f4(void);
extern void func_ov263_020d019c(void);
extern void func_ov263_020d05c4(void);
extern void func_ov263_020d02d0(void);
extern void func_ov263_020d030c(void);
extern void func_ov263_020d0348(void);
extern void func_ov263_020d09a0(void);
extern void func_ov263_020d0118(void);
extern void func_ov263_020d0d3c(void);

void func_ov263_020cfc08(char *self)
{
    ParamBlock params;
    KindTable kinds;
    Placement place;
    Obb box;
    VecFx32 lift;
    VecFx32 zero;
    signed char i;

    kinds = data_ov263_020d3674;
    params.w[0] = -0x2000;
    params.w[1] = 0;
    params.w[2] = -0x2000;
    params.w[3] = params.w[0] + 0x4000;
    params.w[4] = params.w[1] + 0x4000;
    params.w[5] = params.w[2] + 0x4000;
    *(void **)(self + 0x8) = (void *)func_ov263_020d009c;
    *(void **)(self + 0xc) = (void *)func_ov263_020d00f4;
    *(void **)(self + 0x1c) = (void *)func_ov263_020d019c;
    *(void **)(self + 0x30) = (void *)func_ov263_020d05c4;
    *(void **)(self + 0x28) = (void *)func_ov263_020d02d0;
    *(void **)(self + 0x2c) = (void *)func_ov263_020d030c;
    *(void **)(self + 0x34) = (void *)func_ov263_020d0348;
    *(void **)(self + 0x1d0) = (void *)func_ov263_020d09a0;
    *(void **)(self + 0x1dc) = (void *)func_ov263_020d0118;
    *(ParamBlock *)(self + 0x1fc) = params;
    *(void **)(self + 0x1e0) = (void *)func_ov263_020d0d3c;
    *(int *)(self + 0x70) = 0x189e;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0x189e;
    *(int *)(self + 0x6c) = 0;
    *(u16 *)(self + 0x1ae) |= 8;

    *(void **)(self + 0x384) = func_0203b898(func_ov107_020c9440(self, 0));
    func_0203bfb4(*(void **)(self + 0x9c), *(void **)(self + 0x384));
    {
        void *anim = func_ov107_020c9440(self, 1);
        func_0202a388(self + 0x394, *(void **)(*(char **)(self + 0x384) + 0x88), anim, 0xc);
        func_0203b9ac(*(void **)(self + 0x384), self + 0x394);
    }
    *(int *)(self + 0x3cc) = func_0203bee8(*(void **)(self + 0x384), 1, data_ov263_020d36cc);
    *(int *)(self + 0x3d0) = func_0203bee8(*(void **)(self + 0x384), 1, data_ov263_020d36d8);
    *(int *)(self + 0x3d4) = func_0203bee8(*(void **)(self + 0x384), 3, data_ov263_020d36e4);
    *(int *)(self + 0x3d8) = func_0203bee8(*(void **)(self + 0x384), 3, data_ov263_020d36f0);
    {
        unsigned int v = *(u16 *)(self + 0x60);
        *(u16 *)(self + 0x60) = (u16)((v & ~0xff00) | ((((v << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10));
    }
    *(int *)(self + 0x388) = func_ov107_020c9e50(func_ov107_020c9440(self, 0x11), data_ov263_020d36fc);
    *(void **)(self + 0x3b8) = func_0203d15c(0x40);
    for (i = 0; i < 8; i++) {
        (*(Slot **)(self + 0x3b8))[i].node = func_0203b898(func_ov107_020c9440(self, kinds.w[i]));
        func_ov107_020c9074(self, (*(Slot **)(self + 0x3b8))[i].node);
        *(int *)((char *)(*(Slot **)(self + 0x3b8))[i].node + 0x5c) |= 2;
    }
    for (i = 0; i < 2; i++) {
        ((void **)(self + 0x38c))[i] = func_ov263_020d2d88(self);
        *(int *)(*(int *)((char *)((void **)(self + 0x38c))[i] + 0x9c) + 0x5c) |= 4;
    }
    lift = *(VecFx32 *)(self + 0xb0);
    lift.y += 0x1800;
    func_ov107_020c92b0(self, 0, 2, &lift, 0xebd);
    func_ov107_020c92b0(self, 1, 2, &lift, 0xebd);
    func_ov107_020c92b0(self, 2, 3, 0, 0xebd);
    func_ov107_020c92b0(self, 4, 2, &lift, 0xebd);

    place = *(Placement *)(self + 0x64);
    zero = data_02041dc8;
    place.pos = zero;
    box.center = zero;
    box.ax = data_02042270;
    box.ay = data_02042264;
    box.az = data_02042258;
    box.extent[0] = (int)(((long long)FX_Inv(0x189e, 0x1119) * 0x800 + 0x800) >> 12);
    box.extent[1] = 0x400;
    box.extent[2] = (int)(((long long)FX_Inv(0x189e, 0x1119) * 0x800 + 0x800) >> 12);
    *(void **)(self + 0x3bc) = func_01fffca8(self + 0x22c, 0x10, 100);
    **(void ***)(self + 0x3bc) = func_ov107_020c319c(&place);
    for (i = 0; i < 3; i++) {
        void **slot = (void **)func_01fffca8(self + 0x144, 4, 100);
        void *node = i == 0 ? func_ov107_020c319c(&place) : func_ov107_020c32b8(&box);
        ((void **)(self + 0x3c0))[i] = *slot = node;
    }
    func_0203355c(0x168);
}
