/* func_ov245_020d2884 -- constructor of the ov245 hopping actor: installs the handlers (+8 tick,
 * +0xc draw, +0x1c message, +0x30 / +0x34 callbacks, +0x24 hook, +0x1d0 hit), raises bits 1-3
 * and 6 of the +0x60 high byte and bit 2 of +0x1ae, sets the +0x70 scale to 1.0, raises bit 2 of
 * the +0x9c owner's +0x5c, builds the primary item from pool entry 0x1d of the +0x390 pool
 * (+0x384, subscribed, channels 0 and 4 started, motion halted), the three +0x394 slot items
 * from entries 0x1c / 0x1b / 0x25 (attached, bit 1 of +0x5c), and a +0x22c placement (+0x388)
 * from the +0x64 pose with bit 1 of its +8 low byte; +0x38c starts empty. */
typedef void (*Callback)(void);
typedef unsigned short u16;
struct w8 { unsigned int lo : 8, rest : 24; };
struct Ov245Slot { int pItem; int pad4; };
struct Ov245Self { char pad[0x394]; struct Ov245Slot slots[3]; };

extern void func_ov245_020d2a40(void);
extern void func_ov245_020d2a78(void);
extern void func_ov245_020d2ab0(void);
extern void func_ov245_020d2e58(void);
extern void func_ov245_020d2b88(void);
extern void func_ov245_020cc8ec(void);
extern void func_ov245_020d2d08(void);
extern void *func_ov107_020c9440(int pool, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern void func_0203b9fc(int item, int channel, int a, int flag);
extern void func_0203c7ac(int item, int a);
extern void func_ov107_020c9074(int self, int item);
extern int *func_01fffca8(void *list, int stride, int max);
extern int func_ov107_020c319c(void *pose);

struct PoolKinds { unsigned char id[3]; };
extern const struct PoolKinds data_ov245_020d71ac;   /* pool entries of the three slot items */

void func_ov245_020d2884(char *self) {   /* a byte pointer: int arithmetic on self schedules the handler stores differently */
    struct PoolKinds kinds = data_ov245_020d71ac;
    int pool = *(int *)(self + 0x390);
    int i;
    int item;
    const unsigned char *kind;

    *(Callback *)(self + 0x8) = func_ov245_020d2a40;
    *(Callback *)(self + 0xc) = func_ov245_020d2a78;
    *(Callback *)(self + 0x1c) = func_ov245_020d2ab0;
    *(Callback *)(self + 0x30) = func_ov245_020d2e58;
    *(Callback *)(self + 0x34) = func_ov245_020d2b88;
    *(Callback *)(self + 0x24) = func_ov245_020cc8ec;
    *(Callback *)(self + 0x1d0) = func_ov245_020d2d08;
    {
        u16 hw = *(u16 *)(self + 0x60);
        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x4e) << 0x18) >> 0x10);
    }
    *(u16 *)(self + 0x100 + 0xae) |= 4;
    *(int *)(self + 0x70) = 0x1000;
    *(int *)(*(int *)(self + 0x9c) + 0x5c) |= 4;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(pool, 0x1d));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    func_0203b9fc(*(int *)(self + 0x384), 0, 0, 1);
    func_0203b9fc(*(int *)(self + 0x384), 4, 0, 1);
    func_0203c7ac(*(int *)(self + 0x384), 0);
    for (i = 0, kind = kinds.id; i < 3; i++) {
        item = ((struct Ov245Self *)self)->slots[i].pItem = func_0203b898(func_ov107_020c9440(pool, *kind++));
        func_ov107_020c9074(self, item);
        *(int *)(((struct Ov245Self *)self)->slots[i].pItem + 0x5c) |= 2;
    }
    *(int **)(self + 0x388) = func_01fffca8((void *)(self + 0x22c), 0x10, 0x64);
    **(int **)(self + 0x388) = func_ov107_020c319c((void *)(self + 0x64));
    ((struct w8 *)(*(int *)(self + 0x388) + 8))->lo |= 2;
    *(int *)(self + 0x38c) = 0;
}
