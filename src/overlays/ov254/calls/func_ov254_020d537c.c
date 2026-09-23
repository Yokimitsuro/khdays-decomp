/* Constructor of an ov254 helper pair: installs its handlers (+8, +0xc, +0x30 update, +0x1dc),
 * sets bits 1-3, 5 and 6 of the +0x60 high byte and bits 2-4 of +0x1ae, the +0x64 pose (0, 1, 0,
 * tiny scale), builds the two +0x384 / +0x388 items (poses 0x46 / 0x47 of the +0x38c pool), flags
 * them (+0x5c bit 0) and subscribes both to +0x9c. */
typedef unsigned short u16;
typedef void (*Callback)(void);
typedef struct { int x, y, z; } Vec3;
struct Items { char pad[0x384]; int item[2]; };
struct b1 { unsigned int b0 : 1; };

extern void *func_ov107_020c9440(int pool, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern const Vec3 data_02041dc8;
extern void func_ov254_020d5474(void);
extern void func_ov254_020d554c(void);
extern void func_ov254_020d55d8(void);
extern void func_ov254_020d54a4(void);

static inline void SetXYZ(Vec3 *v, int x, int y, int z) {
    v->x = x;
    v->y = y;
    v->z = z;
}

static inline void VecSet(Vec3 *v, int x, int y, int z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

void func_ov254_020d537c(char *self)
{
    int pool = *(int *)(self + 0x38c);
    Vec3 *pose;
    int i;

    *(Callback *)(self + 0x8) = func_ov254_020d5474;
    *(Callback *)(self + 0xc) = func_ov254_020d554c;
    *(Callback *)(self + 0x30) = func_ov254_020d55d8;
    *(Callback *)(self + 0x1dc) = func_ov254_020d54a4;
    {
        u16 hw = *(u16 *)(self + 0x60);
        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x6e) << 0x18) >> 0x10);
    }
    *(u16 *)(self + 0x100 + 0xae) |= 0x1c;
    pose = (Vec3 *)(self + 0x64);
    *pose = data_02041dc8;
    VecSet(pose, 0, *(int *)(self + 0x70) = 1, 0);
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(pool, 0x46));
    *(int *)(self + 0x388) = func_0203b898(func_ov107_020c9440(pool, 0x47));
    for (i = 0; i < 2; i++) {
        ((struct b1 *)(((struct Items *)self)->item[i] + 0x5c))->b0 = 1;
        func_0203bfb4(*(int *)(self + 0x9c), ((struct Items *)self)->item[i]);
    }
}
