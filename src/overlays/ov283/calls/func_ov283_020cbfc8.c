/* Constructor of the ov283 enemy. Installs the handlers (+8, +0xc, +0x1c message, +0x28, +0x2c,
 * +0x30, +0x38, +0x1d0 hit filter, +0x1dc), sets kind 2, the +0x64 pose (scale 1.0) and the +0x1fc
 * bounds (-0.93 / 0.006 / -0.52 to 0.93 / 1.77 / 0.32); builds the +0x384 body rig (pose 0,
 * subscribed to +0x9c) with its two hand attachments (xig_h_L / xig_h_R at +0x394 / +0x398), a
 * placement of the pose on the +0x22c pool (+0x388) and on the +0x144 pool (+0x38c); creates the two
 * 020ced9c helpers (+0x39c) and sixteen 020cf21c helpers (+0x3a4), builds the six hidden sub-items of
 * data_ov283_020cfb4c into the +0x3ec pair table, sets the +0x3e8 threshold to 70 % and loads sound
 * 0x17e (with a +0x3e4 partner) or 0x173. */
typedef unsigned char u8;
typedef void (*Callback)(void);
typedef struct { int x, y, z; } Vec3;
typedef struct { int id[6]; } IdTable6;
typedef struct { Vec3 min; Vec3 max; } Bounds;
typedef struct { Vec3 pos; int scale; } Placement;
struct Pair { int res; int handle; };
struct Ov283Parts { char pad[0x39c]; int small[2]; int helpers[16]; char pad3e4[4]; int threshold; struct Pair items[6]; };

extern void func_ov283_020cc224(void);
extern void func_ov283_020cc25c(void);
extern void func_ov283_020cc3ac(void);
extern void func_ov283_020cc2bc(void);
extern void func_ov283_020cc318(void);
extern void func_ov283_020cc634(void);
extern void func_ov283_020cc628(void);
extern void func_ov283_020cc690(void);
extern void func_ov283_020cc374(void);
extern void *func_ov107_020c9440(char *self, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern int func_0203bee8(int item, int kind, void *name);
extern int *func_01fffca8(void *pool, int elementSize, int capacity);
extern int func_ov107_020c319c(const Placement *placement);
extern int func_ov283_020ced9c(char *self);
extern int func_ov283_020cf21c(char *self);
extern void func_ov107_020c9074(char *self, int item);
extern void func_0203355c(int resourceId);
extern IdTable6 data_ov283_020cfb4c;
extern char data_ov283_020cfbec[];
extern char data_ov283_020cfbf4[];

void func_ov283_020cbfc8(char *self)
{
    IdTable6 ids = data_ov283_020cfb4c;
    Bounds bounds;
    int i;
    int *slot;

    bounds.min.x = -0xeea;
    bounds.min.y = 0x17;
    bounds.min.z = -0x858;
    bounds.max.x = bounds.min.x + 0x1dd3;
    bounds.max.y = bounds.min.y + 0x1c27;
    bounds.max.z = bounds.min.z + 0xd64;
    *(Callback *)(self + 0x8) = func_ov283_020cc224;
    *(Callback *)(self + 0x1c) = func_ov283_020cc3ac;
    *(Callback *)(self + 0xc) = func_ov283_020cc25c;
    *(Callback *)(self + 0x30) = func_ov283_020cc634;
    *(Callback *)(self + 0x28) = func_ov283_020cc2bc;
    *(Callback *)(self + 0x2c) = func_ov283_020cc318;
    *(Callback *)(self + 0x38) = func_ov283_020cc628;
    *(Callback *)(self + 0x1d0) = func_ov283_020cc690;
    *(Callback *)(self + 0x1dc) = func_ov283_020cc374;
    *(u8 *)(self + 0x1c9) = 2;
    *(int *)(self + 0x70) = 0x1000;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0x1000;
    *(int *)(self + 0x6c) = 0;
    *(Bounds *)(self + 0x1fc) = bounds;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(self, 0));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    *(int *)(self + 0x394) = func_0203bee8(*(int *)(self + 0x384), 3, data_ov283_020cfbec);
    *(int *)(self + 0x398) = func_0203bee8(*(int *)(self + 0x384), 3, data_ov283_020cfbf4);
    *(int *)(self + 0x388) = (int)func_01fffca8(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x388) = func_ov107_020c319c((Placement *)(self + 0x64));
    slot = func_01fffca8(self + 0x144, 4, 100);
    *(int *)(self + 0x38c) = *slot = func_ov107_020c319c((Placement *)(self + 0x64));
    for (i = 0; i < 2; i++) {
        ((struct Ov283Parts *)self)->small[i] = func_ov283_020ced9c(self);
    }
    for (i = 0; i < 0x10; i++) {
        ((struct Ov283Parts *)self)->helpers[i] = func_ov283_020cf21c(self);
    }
    for (i = 0; i < 6; i++) {
        ((struct Ov283Parts *)self)->items[i].res = func_0203b898(func_ov107_020c9440(self, ids.id[i]));
        func_ov107_020c9074(self, ((struct Ov283Parts *)self)->items[i].res);
        *(int *)(((struct Ov283Parts *)self)->items[i].res + 0x5c) |= 2;
    }
    ((struct Ov283Parts *)self)->threshold = 0x46;
    func_0203355c(*(int *)(self + 0x3e4) != 0 ? 0x17e : 0x173);
}
