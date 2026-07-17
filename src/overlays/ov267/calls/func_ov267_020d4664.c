/* func_ov267_020d4664 -- move the object, notify the owner's callback, latch the ready flag, and
 * forward to the finaliser in state 1.
 *
 * One of a 3-member shape family; the twins live in ov212/ov266 and are byte-identical modulo
 * relocs (matched here, fanned out with dedupprop).
 *
 * Same callback protocol as func_ov212_020d1a94: the gate at +0x40 is a SIGNED 1-bit bitfield at
 * bit 1 (the ROM's `lsl #0x1e ; asrs #0x1f` sign-extends and tests in one), and the callback at
 * +0xc must be read INSIDE the short-circuit -- the ROM's `ldrne` only loads it when the gate is
 * set. See codegen-cracks.md. */

typedef struct {
    int b0 : 1;
    int b1 : 1;
    int rest : 30;
} Bits32;

extern void func_ov107_020c5c54(int obj, int a);
extern void func_0203c7ac(int a, int b);
extern void func_ov267_020d49a8(int a, int b, int c);

void func_ov267_020d4664(int obj, int a, int b, int c) {
    func_ov107_020c5c54(obj, a);
    if (((Bits32 *)(obj + 0x40))->b1 != 0 && *(void (**)(int, int))(obj + 0xc) != 0) {
        (*(void (**)(int, int))(obj + 0xc))(obj, 0);
    }
    func_0203c7ac(*(int *)(obj + 0x384), 0);
    *(int *)(obj + 0x388) = 1;
    if (*(int *)(obj + 0x50) == 1) {
        func_ov267_020d49a8(*(int *)(obj + 0x214), b, c);
    }
}
