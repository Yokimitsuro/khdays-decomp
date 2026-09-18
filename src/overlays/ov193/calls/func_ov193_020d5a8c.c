/* Constructor of the ov191 enemy (x3: ov191/192/193): installs the handlers (+8 tick, +0xc
 * draw, +0x1c message, +0x30 hit callback, +0x1d0 finish), sets bits 1/2/3/6 of the +0x60 high
 * byte, bit 2 of the +0x1ae flags, clears the +0x54 counter, sets the +0x70 scale to 0x800 and
 * raises bit 2 on the subscriber's +0x5c. Then the model item comes from pool entry 4 (subscribed,
 * its four channels bound with (0, 1), state cleared), the two sub-items from pool entries 5 and 7
 * into a fresh 16-byte slot table (+0x390, attached, bit 1 on their +0x5c), and the +0x388 list
 * node gets a placement built from the actor's +0x64 pose with bit 1 raised on its +8 flags. */
typedef unsigned short u16;
typedef void (*Callback)(void);

struct Ov191SubitemSlot {
    int pItem;
    int pad4;
};

struct bf {
    unsigned b : 8;
};

extern void func_ov193_020d5c60(void);
extern void func_ov193_020d5ca0(void);
extern void func_ov193_020d5cd8(void);
extern void func_ov193_020d5d8c(void);
extern void func_ov193_020d5de8(void);
extern void *func_ov107_020c9440(int pool, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern void func_0203b9fc(int item, int channel, int a, int b);
extern void func_0203c7ac(int item, int a);
extern void *func_0203d15c(int size);
extern void func_ov107_020c9074(char *self, int item);
extern int *func_01fffca8(char *list, int stride, int max);
extern int func_ov107_020c319c(char *pose);
extern const int data_ov193_020d69c4[2];

void func_ov193_020d5a8c(char *self)
{
    int kinds[2];
    u16 hw;
    int i;
    i = 0;
    kinds[0] = data_ov193_020d69c4[0];
    kinds[1] = data_ov193_020d69c4[1];
    *(Callback *)(self + 0x8) = func_ov193_020d5c60;
    *(Callback *)(self + 0xc) = func_ov193_020d5ca0;
    *(Callback *)(self + 0x1c) = func_ov193_020d5cd8;
    *(Callback *)(self + 0x30) = func_ov193_020d5de8;
    *(Callback *)(self + 0x1d0) = func_ov193_020d5d8c;
    hw = *(u16 *)(self + 0x60);
    *(u16 *)(self + 0x60) = (hw & ~0xff00) |
        ((((((unsigned int)hw << 0x10) >> 0x18) | 0x4e) << 0x18) >> 0x10);
    *(u16 *)(self + 0x100 + 0xae) |= 4;
    *(int *)(self + 0x54) = 0;
    *(int *)(self + 0x70) = 0x800;
    *(int *)(*(int *)(self + 0x9c) + 0x5c) |= 4;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(*(int *)(self + 0x38c), 4));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    func_0203b9fc(*(int *)(self + 0x384), 0, 0, 1);
    func_0203b9fc(*(int *)(self + 0x384), 1, 0, 1);
    func_0203b9fc(*(int *)(self + 0x384), 2, 0, 1);
    func_0203b9fc(*(int *)(self + 0x384), 4, 0, 1);
    func_0203c7ac(*(int *)(self + 0x384), 0);
    *(void **)(self + 0x390) = func_0203d15c(0x10);
    for (; i < 2; i++) {
        (*(struct Ov191SubitemSlot **)(self + 0x390))[i].pItem =
            func_0203b898(func_ov107_020c9440(*(int *)(self + 0x38c), kinds[i]));
        func_ov107_020c9074(self, (*(struct Ov191SubitemSlot **)(self + 0x390))[i].pItem);
        *(int *)((*(struct Ov191SubitemSlot **)(self + 0x390))[i].pItem + 0x5c) |= 2;
    }
    *(int **)(self + 0x388) = func_01fffca8(self + 0x22c, 0x10, 0x64);
    **(int **)(self + 0x388) = func_ov107_020c319c(self + 0x64);
    ((struct bf *)(*(int *)(self + 0x388) + 8))->b |= 2;
}
