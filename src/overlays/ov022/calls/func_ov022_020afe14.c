/* func_ov022_020afe14 -- relocate one animation record's six offset fields into absolute
 * pointers and hand the two halves of it to the shared setup routine.
 * The record is base + 4 + kind * 0x34, where kind is the byte at obj+0x18; each of its
 * first six words is stored as an offset from `base` and is rebased in place.
 *
 * `base` is a char *, not an int: the ROM's `adds rd, base, rd` keeps the base as Rn,
 * and mwcc canonicalises the commutative integer add the other way round. Pointer
 * arithmetic is not commutative in its IR, which is what pins the operand order. */
extern void func_ov022_020afe88(int *base, int flag, unsigned short *a, int *b, short *c, int d);

void func_ov022_020afe14(int obj, char *param2) {
    unsigned char *f = (unsigned char *)(obj + 8);
    int *p = (int *)(param2 + 4 + f[0x10] * 0x34);
    p[0] = (int)(param2 + p[0]);
    p[1] = (int)(param2 + p[1]);
    p[2] = (int)(param2 + p[2]);
    p[3] = (int)(param2 + p[3]);
    p[4] = (int)(param2 + p[4]);
    p[5] = (int)(param2 + p[5]);
    func_ov022_020afe88((int *)(obj + 0x28), *(unsigned char *)(obj + 4),
                        (unsigned short *)(p + 6), p, (short *)(p + 9), f[0x11]);
    func_ov022_020afe88((int *)(obj + 0x58), *(unsigned char *)(obj + 4),
                        (unsigned short *)((int)p + 0x1e), p + 3, (short *)(p + 0xb), f[0x12]);
}
