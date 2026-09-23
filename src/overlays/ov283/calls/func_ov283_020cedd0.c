/* Build the ov283 helper: its brain (020ceee8), update (020cef04) and spawn (020cef4c) callbacks are
 * installed, bits 1-3 and 6 of the +0x60 high byte and bits 2/4 of +0x1ae are set, the body is a
 * 0.125 sphere at the origin with no speed, model 1 of the +0x388 set becomes the +0x384 rig
 * (subscribed to the scene) and a 1.0-long upright capsule of that radius is registered in the
 * +0x144 pool (+0x38c). */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 pos; Vec3 axis; int length; int radius; } Capsule;

extern void func_ov283_020ceee8(void);
extern void func_ov283_020cef04(void);
extern void func_ov283_020cef4c(void);
extern void *func_ov107_020c9440(int set, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern int *func_01fffca8(void *pool, int count, int size);
extern int func_ov107_020c3210(const Capsule *capsule);
extern const Vec3 data_02041dc8;
extern const Vec3 data_02042258;

void func_ov283_020cedd0(char *self)
{
    Vec3 origin;
    Capsule body;
    int set = *(int *)(self + 0x388);
    int *cyl;

    *(void **)(self + 8) = func_ov283_020ceee8;
    *(void **)(self + 0xc) = func_ov283_020cef04;
    *(void **)(self + 0x30) = func_ov283_020cef4c;
    {
        u16 hw = *(u16 *)(self + 0x60);
        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x4e) << 0x18) >> 0x10);
    }
    *(u16 *)(self + 0x1ae) |= 0x14;
    *(int *)(self + 0x70) = 0x200;
    origin = data_02041dc8;
    *(Vec3 *)(self + 0x64) = origin;
    *(int *)(self + 0x54) = 0;
    *(int *)(self + 0x58) = 0;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(set, 1));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    body.pos = origin;
    body.axis = data_02042258;
    body.length = 0x1000;
    body.radius = *(int *)(self + 0x70);
    cyl = func_01fffca8(self + 0x144, 4, 0x64);
    *(int *)(self + 0x38c) = *cyl = func_ov107_020c3210(&body);
}
