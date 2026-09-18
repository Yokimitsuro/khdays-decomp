/* func_ov245_020d4810 -- stop: if bit 1 of +0x40 is set and a +0xc callback is installed it is
 * told 0, the +0x384 item's motion is halted (020c7ac), the +0x3a0 vector is reset to zero and,
 * in state 1, the +0x214 slot is closed by 020d4dec. */
typedef struct { int x, y, z; } Vec3;
struct Flags40 { int bit0 : 1, bit1 : 1; };

extern void func_0203c7ac(int item, int a);
extern void func_ov245_020d4dec(int slot);
extern const Vec3 data_02041dc8;

void func_ov245_020d4810(int self) {
    if (((struct Flags40 *)(self + 0x40))->bit1 && *(void (**)(int, int))(self + 0xc) != 0) {
        (*(void (**)(int, int))(self + 0xc))(self, 0);
    }
    func_0203c7ac(*(int *)(self + 0x384), 0);
    *(Vec3 *)(self + 0x3a0) = data_02041dc8;
    if (*(int *)(self + 0x50) == 1) {
        func_ov245_020d4dec(*(int *)(self + 0x214));
    }
}
