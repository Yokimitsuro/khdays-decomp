/* Constructor of an ov254 helper: installs its handlers (+8, +0x1c message, +0x30 update, +0x1dc),
 * sets bits 1-3 and 6 of the +0x60 high byte and bits 2 and 4 of +0x1ae, zeroes the +0x64 pose
 * with a tiny scale, clears +0x54 / +0x58, builds the +0x384 item (pose 0x41 of the +0x38c pool,
 * subscribed to +0x9c) and the hidden +0x390 item (pose 0x42, registered). */
typedef unsigned short u16;
typedef void (*Callback)(void);
typedef struct { int x, y, z; } Vec3;

extern void *func_ov107_020c9440(int pool, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern void func_ov107_020c9074(char *self, int item);
extern const Vec3 data_02041dc8;
extern void func_ov254_020d1a0c(void);
extern void func_ov254_020d1a30(void);
extern void func_ov254_020d1b30(void);
extern void func_ov254_020d1aa8(void);

void func_ov254_020d1924(char *self)
{
    int pool = *(int *)(self + 0x38c);

    *(Callback *)(self + 0x8) = func_ov254_020d1a0c;
    *(Callback *)(self + 0x1c) = func_ov254_020d1a30;
    *(Callback *)(self + 0x30) = func_ov254_020d1b30;
    *(Callback *)(self + 0x1dc) = func_ov254_020d1aa8;
    {
        u16 hw = *(u16 *)(self + 0x60);
        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x4e) << 0x18) >> 0x10);
    }
    *(u16 *)(self + 0x100 + 0xae) |= 0x14;
    *(Vec3 *)(self + 0x64) = data_02041dc8;
    *(int *)(self + 0x70) = 1;
    *(int *)(self + 0x54) = 0;
    *(int *)(self + 0x58) = 0;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(pool, 0x41));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    *(int *)(self + 0x390) = func_0203b898(func_ov107_020c9440(pool, 0x42));
    func_ov107_020c9074(self, *(int *)(self + 0x390));
    *(int *)(*(int *)(self + 0x390) + 0x5c) |= 2;
}
