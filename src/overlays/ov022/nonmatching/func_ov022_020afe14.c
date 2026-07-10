extern void func_ov022_020afe88(int *base, int flag, unsigned short *a, int *b, short *c, int d);

/* Byte-exact except the six accumulate stores: the original emits `adds rd,r1,rd`
 * (param2 as rn), mwcc canonicalises the commutative add to `adds rd,rd,r1`
 * (the loaded element as rn) regardless of source operand order. */
void func_ov022_020afe14(int obj, int param2) {
    unsigned char *f = (unsigned char *)(obj + 8);
    int *p = (int *)(param2 + 4 + f[0x10] * 0x34);
    p[0] = param2 + p[0];
    p[1] = param2 + p[1];
    p[2] = param2 + p[2];
    p[3] = param2 + p[3];
    p[4] = param2 + p[4];
    p[5] = param2 + p[5];
    func_ov022_020afe88((int *)(obj + 0x28), *(unsigned char *)(obj + 4),
                        (unsigned short *)(p + 6), p, (short *)(p + 9), f[0x11]);
    func_ov022_020afe88((int *)(obj + 0x58), *(unsigned char *)(obj + 4),
                        (unsigned short *)((int)p + 0x1e), p + 3, (short *)(p + 0xb), f[0x12]);
}
