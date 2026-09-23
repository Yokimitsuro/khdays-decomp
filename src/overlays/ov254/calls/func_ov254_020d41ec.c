/* Constructor of an ov254 helper: installs its handlers (+8, +0x1c message, +0x30 update, +0x1dc),
 * sets bits 1-3, 5 and 6 of the +0x60 high byte and bit 2 of +0x1ae, a tiny scale, clears +0x54 /
 * +0x58, marks the +0x9c parent, builds the +0x384 item (pose 0x4a of the +0x38c pool, subscribed
 * and re-initialised) and the hidden +0x390 item (pose 0x4b, registered). */
typedef unsigned short u16;
typedef void (*Callback)(void);

extern void *func_ov107_020c9440(int pool, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern void func_0203c7ac(int item, int a);
extern void func_ov107_020c9074(char *self, int item);
extern void func_ov254_020d42dc(void);
extern void func_ov254_020d4300(void);
extern void func_ov254_020d45e0(void);
extern void func_ov254_020d4378(void);

void func_ov254_020d41ec(char *self)
{
    int pool = *(int *)(self + 0x38c);

    *(Callback *)(self + 0x8) = func_ov254_020d42dc;
    *(Callback *)(self + 0x1c) = func_ov254_020d4300;
    *(Callback *)(self + 0x30) = func_ov254_020d45e0;
    *(Callback *)(self + 0x1dc) = func_ov254_020d4378;
    {
        u16 hw = *(u16 *)(self + 0x60);
        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x6e) << 0x18) >> 0x10);
    }
    *(u16 *)(self + 0x100 + 0xae) |= 4;
    *(int *)(self + 0x70) = 1;
    *(int *)(self + 0x54) = 0;
    *(int *)(self + 0x58) = 0;
    *(int *)(*(int *)(self + 0x9c) + 0x5c) |= 4;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(pool, 0x4a));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    func_0203c7ac(*(int *)(self + 0x384), 0);
    *(int *)(self + 0x390) = func_0203b898(func_ov107_020c9440(pool, 0x4b));
    func_ov107_020c9074(self, *(int *)(self + 0x390));
    *(int *)(*(int *)(self + 0x390) + 0x5c) |= 2;
}
