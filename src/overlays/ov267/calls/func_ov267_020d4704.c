/* Constructor of the ov266 sub-actor: installs the handlers (+8 tick, +0xc draw veneer, +0x1c
 * message, +0x30 callback, +0x1dc collision-set), flags 0x4e in the +0x60 high byte and bits
 * 0x14 of +0x1ae, sets the +0x70 latch to 0xc00 and clears +0x54/+0x58, raises bit 2 of the
 * +0x9c list's +0x5c word, builds the +0x384 item from pool entry 7 (subscribed to +0x9c, cleared)
 * and the +0x394 item from entry 8 of pool 0x22 (attached, bit 1 of its +0x5c, its +0x88
 * animation's channel 4 bound to the +0xe0 table), then allocates the +0x390 child (020d35fc)
 * and clears +0x388. Codegen: `self` must be a `char *` parameter -- with an `int` the stored
 * +0x394 value is forwarded into the attach call (`mov r1,r0`) and the handler pool loads
 * interleave differently; the ROM reloads +0x394. */
typedef void (*Callback)(void);
typedef unsigned short u16;

extern void func_ov267_020d4830(void);
extern void WM_EndKeySharing_0x020d4854(void);
extern void func_ov267_020d4860(void);
extern void func_ov267_020d4a48(void);
extern void func_ov267_020d4938(void);
extern void *func_ov107_020c9440(int pool, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern void func_0203c7ac(int item, int a);
extern int func_0203c1b0(void *item, int index);
extern void func_ov107_020c9074(int self, int item);
extern void func_0202accc(void *animation, int track, void *table, short mode);
extern int func_ov267_020d541c(int self);

void func_ov267_020d4704(char *self) {
    int pool = *(int *)(self + 0x38c);

    *(Callback *)(self + 0x8) = func_ov267_020d4830;
    *(Callback *)(self + 0xc) = WM_EndKeySharing_0x020d4854;
    *(Callback *)(self + 0x1c) = func_ov267_020d4860;
    *(Callback *)(self + 0x30) = func_ov267_020d4a48;
    *(Callback *)(self + 0x1dc) = func_ov267_020d4938;
    {
        u16 hw = *(u16 *)(self + 0x60);
        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x4e) << 0x18) >> 0x10);
    }
    *(u16 *)(self + 0x100 + 0xae) |= 0x14;
    *(int *)(self + 0x70) = 0xc00;
    *(int *)(self + 0x54) = 0;
    *(int *)(self + 0x58) = 0;
    *(int *)(*(int *)(self + 0x9c) + 0x5c) |= 4;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(pool, 7));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    func_0203c7ac(*(int *)(self + 0x384), 0);
    *(int *)(self + 0x394) = func_0203c1b0(func_ov107_020c9440(pool, 8), 0x22);
    func_ov107_020c9074((int)self, *(int *)(self + 0x394));
    *(int *)(*(int *)(self + 0x394) + 0x5c) |= 2;
    func_0202accc((void *)*(int *)(*(int *)(self + 0x394) + 0x88), 4, (char *)*(int *)(*(int *)(self + 0x394) + 0x88) + 0xe0, 0);
    *(int *)(self + 0x390) = func_ov267_020d541c((int)self);
    *(int *)(self + 0x388) = 0;
}
