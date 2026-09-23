/* Build the ov218 actor: its brain (020ce224), update (020ce25c), message (020ce2bc), spawn (020ce430),
 * teardown (020ce36c), damage (020ce3fc) and animation (020ce3a8) callbacks are installed, bit 6 of
 * the +0x60 high byte and bits 2/9 of +0x1ae are set, the body gets a 0.375 radius sphere (+0x64)
 * and the scene's +0x5c bit 2 is set; the pose is scaled 1.3, model 3 of the +0x390 set becomes the
 * +0x384 rig (subscribed to the +0x9c scene) and the two data_ov218_020cf314 models go into the
 * +0x39c pairs, attached (020c9074) and hidden. Two collision cylinders from the sphere are registered
 * in the +0x22c (16) and +0x144 (4) pools; the second is kept in +0x38c. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { u8 a, b; } Pair2;
struct EffectPair { int res; int handle; };
struct Ov218Models { char pad[0x39c]; struct EffectPair pair[2]; };

extern u8 data_ov218_020cf314[];
extern void func_ov218_020ce224(void);
extern void func_ov218_020ce25c(void);
extern void func_ov218_020ce2bc(void);
extern void func_ov218_020ce430(void);
extern void func_ov218_020ce36c(void);
extern void func_ov218_020ce3fc(void);
extern void func_ov218_020ce3a8(void);
extern void func_0203ca9c(void *srt, int scale);
extern void *func_ov107_020c9440(int set, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern void func_ov107_020c9074(char *self, int model);
extern int *func_01fffca8(void *pool, int count, int size);
extern int func_ov107_020c319c(void *sphere);

static inline void VecSet(Vec3 *v, int x, int y, int z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

void func_ov218_020ce07c(char *self)
{
    u8 ids[2];
    int set;
    int model;
    int i;
    int *cyl;

    ids[1] = data_ov218_020cf314[1];
    ids[0] = data_ov218_020cf314[0];
    set = *(int *)(self + 0x390);
    *(void **)(self + 8) = func_ov218_020ce224;
    *(void **)(self + 0xc) = func_ov218_020ce25c;
    *(void **)(self + 0x1c) = func_ov218_020ce2bc;
    *(void **)(self + 0x30) = func_ov218_020ce430;
    *(void **)(self + 0x34) = func_ov218_020ce36c;
    *(void **)(self + 0x1d0) = func_ov218_020ce3fc;
    *(void **)(self + 0x1dc) = func_ov218_020ce3a8;
    {
        u16 hw = *(u16 *)(self + 0x60);
        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x40) << 0x18) >> 0x10);
    }
    *(u16 *)(self + 0x1ae) |= 0x204;
    *(int *)(self + 0x70) = 0x600;
    *(int *)(self + 0x54) = 0;
    *(int *)(self + 0x58) = 0;
    *(int *)(*(int *)(self + 0x9c) + 0x5c) |= 4;
    VecSet((Vec3 *)(self + 0x64), 0, *(int *)(self + 0x70), 0);
    func_0203ca9c(self + 0xa0, 0x14cd);
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(set, 3));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    for (i = 0; i < 2; i++) {
        model = ((struct Ov218Models *)self)->pair[i].res = func_0203b898(func_ov107_020c9440(set, ids[i]));
        func_ov107_020c9074(self, model);
        *(int *)(model + 0x5c) |= 2;
    }
    *(int **)(self + 0x388) = func_01fffca8(self + 0x22c, 0x10, 0x64);
    **(int **)(self + 0x388) = func_ov107_020c319c(self + 0x64);
    cyl = func_01fffca8(self + 0x144, 4, 0x64);
    *(int *)(self + 0x38c) = *cyl = func_ov107_020c319c(self + 0x64);
}
