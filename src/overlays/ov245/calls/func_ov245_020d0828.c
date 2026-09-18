/* func_ov245_020d0828 -- constructor of the ov245 actor: installs the handlers (+8 tick, +0xc
 * draw, +0x1c message, +0x30 / +0x34 callbacks, +0x24 hook, +0x1d0 hit), raises bits 1-3 and 6 of
 * the +0x60 high byte and bit 2 of +0x1ae, sets the +0x70 scale to 0.5, builds the primary item
 * from pool entry 0x11 of the +0x390 pool (+0x384, subscribed to +0x9c), the three +0x394 slot
 * items from entries 0x17..0x19 (attached, bit 1 of +0x5c), and a +0x22c placement (+0x388)
 * from the +0x64 pose with bit 1 of its +8 low byte; +0x38c starts empty. */
typedef void (*Callback)(void);
typedef unsigned short u16;
struct w8 { unsigned int lo : 8, rest : 24; };
struct Ov245Slot { int pItem; int pad4; };
struct Ov245Self { char pad[0x394]; struct Ov245Slot slots[3]; };

extern void func_ov245_020d097c(void);
extern void func_ov245_020d09b4(void);
extern void func_ov245_020d09ec(void);
extern void func_ov245_020d0bf4(void);
extern void func_ov245_020d0abc(void);
extern void func_ov245_020cc8ec(void);
extern void func_ov245_020d0b58(void);
extern void *func_ov107_020c9440(int pool, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern void func_ov107_020c9074(int self, int item);
extern int *func_01fffca8(void *list, int stride, int max);
extern int func_ov107_020c319c(void *pose);

void func_ov245_020d0828(int self) {
    int pool = *(int *)(self + 0x390);
    int i;
    int item;

    *(Callback *)(self + 0x8) = func_ov245_020d097c;
    *(Callback *)(self + 0xc) = func_ov245_020d09b4;
    *(Callback *)(self + 0x1c) = func_ov245_020d09ec;
    *(Callback *)(self + 0x30) = func_ov245_020d0bf4;
    *(Callback *)(self + 0x34) = func_ov245_020d0abc;
    *(Callback *)(self + 0x24) = func_ov245_020cc8ec;
    *(Callback *)(self + 0x1d0) = func_ov245_020d0b58;
    {
        u16 hw = *(u16 *)(self + 0x60);
        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x4e) << 0x18) >> 0x10);
    }
    *(u16 *)(self + 0x100 + 0xae) |= 4;
    *(int *)(self + 0x70) = 0x800;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(pool, 0x11));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    for (i = 0; i < 3; i++) {
        item = ((struct Ov245Self *)self)->slots[i].pItem = func_0203b898(func_ov107_020c9440(pool, i + 0x17));
        func_ov107_020c9074(self, item);
        *(int *)(((struct Ov245Self *)self)->slots[i].pItem + 0x5c) |= 2;
    }
    *(int **)(self + 0x388) = func_01fffca8((void *)(self + 0x22c), 0x10, 0x64);
    **(int **)(self + 0x388) = func_ov107_020c319c((void *)(self + 0x64));
    ((struct w8 *)(*(int *)(self + 0x388) + 8))->lo |= 2;
    *(int *)(self + 0x38c) = 0;
}
