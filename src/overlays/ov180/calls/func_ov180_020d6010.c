/* Constructor of the ov178 enemy (x3: ov178/179/180): installs the six handlers (+8 tick,
 * +0xc draw, +0x1c message, +0x30/+0x34 hit callbacks, +0x1dc finish), sets bits 1/2/3/6 of the
 * +0x60 high byte, bit 2 of the +0x1ae flags, the +0x70 latch, clears the two +0x54/+0x58
 * counters, raises bit 2 on the subscriber's +0x5c, then builds the model item from table
 * entry 3 of the +0x388 pool, subscribes it and clears its state. */
typedef unsigned short u16;
typedef void (*Callback)(void);

extern void func_ov180_020d60e4(void);
extern void func_ov180_020d6100(void);
extern void func_ov180_020d6128(void);
extern void func_ov180_020d6274(void);
extern void func_ov180_020d6230(void);
extern void func_ov180_020d6198(void);
extern void *func_ov107_020c9440(int pool, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern void func_0203c7ac(int item, int a);

void func_ov180_020d6010(char *self)
{
    u16 hw;
    int pool = *(int *)(self + 0x388);
    *(Callback *)(self + 0x8) = func_ov180_020d60e4;
    *(Callback *)(self + 0xc) = func_ov180_020d6100;
    *(Callback *)(self + 0x1c) = func_ov180_020d6128;
    *(Callback *)(self + 0x30) = func_ov180_020d6274;
    *(Callback *)(self + 0x34) = func_ov180_020d6230;
    *(Callback *)(self + 0x1dc) = func_ov180_020d6198;
    hw = *(u16 *)(self + 0x60);
    *(u16 *)(self + 0x60) = (hw & ~0xff00) |
        ((((((unsigned int)hw << 0x10) >> 0x18) | 0x4e) << 0x18) >> 0x10);
    *(u16 *)(self + 0x100 + 0xae) |= 4;
    *(int *)(self + 0x70) = 1;
    *(int *)(self + 0x54) = 0;
    *(int *)(self + 0x58) = 0;
    *(int *)(*(int *)(self + 0x9c) + 0x5c) |= 4;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(pool, 3));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    func_0203c7ac(*(int *)(self + 0x384), 0);
}
