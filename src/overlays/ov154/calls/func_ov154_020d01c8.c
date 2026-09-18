/* Constructor of the ov153 enemy (x3: ov153/154/155): installs the handlers (+8 tick, +0xc
 * draw, +0x1c message, +0x30 hit callback, +0x1d0 finish), sets bits 1/2/3/6 of the +0x60 high
 * byte, bit 2 of the +0x1ae flags, clears the +0x54 counter, sets the +0x70 scale to 0xa00 and
 * raises bit 2 on the subscriber's +0x5c. The model item comes from pool entry 4 (scaled to
 * 1.25 at its +4 placement, subscribed, its four channels bound with (0, 1), state cleared), the
 * two sub-items from the pool entries of the local table into a fresh 16-byte slot table
 * (+0x390, attached, bit 1 on their +0x5c), and the +0x388 list node gets a placement built from
 * the actor's +0x64 pose with bit 1 raised on its +8 flags (cf. func_ov191_020d1e4c). */
typedef unsigned short u16;
typedef void (*Callback)(void);

struct Ov153SubitemSlot {
    int pItem;
    int pad4;
};

struct bf {
    unsigned b : 8;
};

extern void func_ov154_020d03a8(void);
extern void func_ov154_020d03e8(void);
extern void func_ov154_020d0420(void);
extern void func_ov154_020d04d4(void);
extern void func_ov154_020d05fc(void);
extern void *func_ov107_020c9440(int pool, int index);
extern int func_0203b898(void *item);
extern void func_0203ca9c(void *placement, int scale);
extern int func_0203bfb4(int subscriber, int item);
extern void func_0203b9fc(int item, int channel, int a, int b);
extern void func_0203c7ac(int item, int a);
extern void *func_0203d15c(int size);
extern void func_ov107_020c9074(char *self, int item);
extern int *func_01fffca8(char *list, int stride, int max);
extern int func_ov107_020c319c(char *pose);
extern const int data_ov154_020d1c60[2];

void func_ov154_020d01c8(char *self)
{
    int kinds[2];
    u16 hw;
    int i;
    kinds[0] = data_ov154_020d1c60[0];
    kinds[1] = data_ov154_020d1c60[1];
    *(Callback *)(self + 0x8) = func_ov154_020d03a8;
    *(Callback *)(self + 0xc) = func_ov154_020d03e8;
    *(Callback *)(self + 0x1c) = func_ov154_020d0420;
    *(Callback *)(self + 0x30) = func_ov154_020d05fc;
    *(Callback *)(self + 0x1d0) = func_ov154_020d04d4;
    hw = *(u16 *)(self + 0x60);
    *(u16 *)(self + 0x60) = (hw & ~0xff00) |
        ((((((unsigned int)hw << 0x10) >> 0x18) | 0x4e) << 0x18) >> 0x10);
    *(u16 *)(self + 0x100 + 0xae) |= 4;
    *(int *)(*(int *)(self + 0x9c) + 0x5c) |= 4;
    *(int *)(self + 0x54) = 0;
    *(int *)(self + 0x70) = 0xa00;
    i = 0;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(*(int *)(self + 0x38c), 4));
    func_0203ca9c((void *)(*(int *)(self + 0x384) + 4), 0x1400);
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    func_0203b9fc(*(int *)(self + 0x384), 0, 0, 1);
    func_0203b9fc(*(int *)(self + 0x384), 1, 0, 1);
    func_0203b9fc(*(int *)(self + 0x384), 2, 0, 1);
    func_0203b9fc(*(int *)(self + 0x384), 4, 0, 1);
    func_0203c7ac(*(int *)(self + 0x384), 0);
    *(void **)(self + 0x390) = func_0203d15c(0x10);
    for (; i < 2; i++) {
        (*(struct Ov153SubitemSlot **)(self + 0x390))[i].pItem =
            func_0203b898(func_ov107_020c9440(*(int *)(self + 0x38c), kinds[i]));
        func_ov107_020c9074(self, (*(struct Ov153SubitemSlot **)(self + 0x390))[i].pItem);
        *(int *)((*(struct Ov153SubitemSlot **)(self + 0x390))[i].pItem + 0x5c) |= 2;
    }
    *(int **)(self + 0x388) = func_01fffca8(self + 0x22c, 0x10, 0x64);
    **(int **)(self + 0x388) = func_ov107_020c319c(self + 0x64);
    ((struct bf *)(*(int *)(self + 0x388) + 8))->b |= 2;
}
