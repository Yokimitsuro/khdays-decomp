/* func_ov245_020d27e4 -- hit reaction (variant with three forwarded arguments): notifies the
 * owner (020c5c54), tells the +0xc callback 0 when bit 1 of +0x40 is set, halts the +0x384
 * item's motion and, in state 1, passes the arguments on to the +0x214 slot (020d2c78). */
struct Flags40 { int bit0 : 1, bit1 : 1; };

extern void func_ov107_020c5c54(int self, int a);
extern void func_0203c7ac(int item, int a);
extern void func_ov245_020d2c78(int slot, int b, int c, int d);

void func_ov245_020d27e4(int self, int a, int b, int c, int d) {
    func_ov107_020c5c54(self, a);
    if (((struct Flags40 *)(self + 0x40))->bit1 && *(void (**)(int, int))(self + 0xc) != 0) {
        (*(void (**)(int, int))(self + 0xc))(self, 0);
    }
    func_0203c7ac(*(int *)(self + 0x384), 0);
    if (*(int *)(self + 0x50) == 1) {
        func_ov245_020d2c78(*(int *)(self + 0x214), b, c, d);
    }
}
