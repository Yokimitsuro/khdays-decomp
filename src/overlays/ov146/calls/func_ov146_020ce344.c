/* Build the ov146 actor: its brain (020ce514), update (020ce538), spawn (020ce7e0), teardown
 * (020ce608), knock-back (020ce6e4) and animation (020ce564) callbacks are installed, bits 2-3 of the
 * +0x60 high byte clear and bit 1 is set, +0x1ae bit 2 clears and +0x1b0 gains 0x888; the body is 1.0 x
 * 0.5 with a 0.75 radius (+0x64 sphere lifted by it). Model 0xb of the +0x3b4 set becomes the +0x384
 * rig, subscribed to the +0x9c scene, its data_ov146_020cf534 sub-part goes to +0x3b8, the rig pose
 * resets and record 0xc binds to the +0x388 slot. Two collision cylinders from the +0x64 sphere at the
 * origin are registered in the +0x22c (16) and +0x144 (4) pools; the second is kept in +0x3b0. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 center; int nRadius; } Sphere;
typedef struct { char data[0x24]; } AnimSlot;

extern void func_ov146_020ce514(void);
extern void func_ov146_020ce538(void);
extern void func_ov146_020ce7e0(void);
extern void func_ov146_020ce608(void);
extern void func_ov146_020ce6e4(void);
extern void func_ov146_020ce564(void);
extern void *func_ov107_020c9440(int set, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern int func_0203bee8(int rig, int kind, void *desc);
extern void func_0203c7ac(int rig, int a);
extern void func_0202a388(AnimSlot *slot, int bank, void *record, int d);
extern void func_0203b9ac(int rig, AnimSlot *slot);
extern int *func_01fffca8(void *pool, int count, int size);
extern int func_ov107_020c319c(Sphere *sphere);
extern char data_ov146_020cf534[];
extern const Vec3 data_02041dc8;

static inline void VecSet(Vec3 *v, int x, int y, int z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

void func_ov146_020ce344(char *self)
{
    int set = *(int *)(self + 0x3b4);
    Sphere body;
    int *cyl;

    *(void **)(self + 8) = func_ov146_020ce514;
    *(void **)(self + 0xc) = func_ov146_020ce538;
    *(void **)(self + 0x30) = func_ov146_020ce7e0;
    *(void **)(self + 0x34) = func_ov146_020ce608;
    *(void **)(self + 0x1d0) = func_ov146_020ce6e4;
    *(void **)(self + 0x1dc) = func_ov146_020ce564;
    {
        u16 hw = *(u16 *)(self + 0x60);
        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(u16)((((unsigned int)hw << 0x10) >> 0x18) & ~0xc) << 0x18) >> 0x10);
    }
    {
        u16 hw = *(u16 *)(self + 0x60);
        /* the clear is written once more and overwritten at once: a dead store that uses up the
         * scheduler's budget, so the rest of the block keeps the ROM's order */
        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(u16)((((unsigned int)hw << 0x10) >> 0x18) & ~0xc) << 0x18) >> 0x10);
        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 2) << 0x18) >> 0x10);
    }
    *(u16 *)(self + 0x1ae) &= ~4;
    *(u16 *)(self + 0x1b0) |= 0x888;
    *(int *)(self + 0x70) = 0xc00;
    *(int *)(self + 0x54) = 0x1000;
    *(int *)(self + 0x58) = 0x800;
    VecSet((Vec3 *)(self + 0x64), 0, *(int *)(self + 0x70), 0);
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(set, 0xb));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    *(int *)(self + 0x3b8) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov146_020cf534);
    func_0203c7ac(*(int *)(self + 0x384), 0);
    func_0202a388((AnimSlot *)(self + 0x388), *(int *)(*(int *)(self + 0x384) + 0x88), func_ov107_020c9440(set, 0xc), 0xc);
    func_0203b9ac(*(int *)(self + 0x384), (AnimSlot *)(self + 0x388));
    body = *(Sphere *)(self + 0x64);
    body.center = data_02041dc8;
    *(int **)(self + 0x3ac) = func_01fffca8(self + 0x22c, 0x10, 0x64);
    **(int **)(self + 0x3ac) = func_ov107_020c319c(&body);
    cyl = func_01fffca8(self + 0x144, 4, 0x64);
    *(int *)(self + 0x3b0) = *cyl = func_ov107_020c319c(&body);
}
