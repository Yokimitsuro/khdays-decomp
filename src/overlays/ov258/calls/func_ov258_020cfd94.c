/* Constructor of the ov258 thrown item: installs its brain (020cfed8), update (020cfef4) and spawn
 * (020cffb0) callbacks, sets bits 5 and 6 of the +0x60 high byte and bits 2-4 of +0x1ae, a tiny
 * radius (3), the body at the origin with no speed; model 0x28 of the owner's +0x390 set becomes the
 * +0x384 rig (subscribed to +0x9c) and a 13.9-long upright capsule of radius 0.7 is registered in the
 * +0x144 pool (+0x388). */
typedef unsigned short u16;
typedef void (*Callback)(void);
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 pos; Vec3 axis; int length; int radius; } Capsule;

extern void func_ov258_020cfed8(void);
extern void func_ov258_020cfef4(void);
extern void func_ov258_020cffb0(void);
extern void *func_ov107_020c9440(int set, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern int *func_01fffca8(void *pool, int count, int size);
extern int func_ov107_020c3210(const Capsule *capsule);
extern const Vec3 data_02041dc8;
extern const Vec3 data_02042258;

void func_ov258_020cfd94(char *self)
{
    Capsule body;
    Vec3 origin;
    int set = *(int *)(self + 0x390);
    int *slot;

    *(Callback *)(self + 8) = func_ov258_020cfed8;
    *(Callback *)(self + 0xc) = func_ov258_020cfef4;
    *(Callback *)(self + 0x30) = func_ov258_020cffb0;
    {
        u16 hw = *(u16 *)(self + 0x60);

        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x40) << 0x18) >> 0x10);
    }
    *(int *)(self + 0x70) = 3;
    origin = data_02041dc8;
    *(Vec3 *)(self + 0x64) = origin;
    *(int *)(self + 0x54) = 0;
    *(int *)(self + 0x58) = 0;
    *(u16 *)(self + 0x1ae) |= 0xc;
    {
        u16 hw = *(u16 *)(self + 0x60);

        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x20) << 0x18) >> 0x10);
    }
    *(u16 *)(self + 0x1ae) |= 0x10;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(set, 0x28));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    body.pos = origin;
    body.axis = data_02042258;
    body.length = 0xde00;
    body.radius = 0xb40;
    slot = func_01fffca8(self + 0x144, 4, 100);
    *(int *)(self + 0x388) = *slot = func_ov107_020c3210(&body);
}
