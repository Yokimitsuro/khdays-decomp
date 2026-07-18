/* NONMATCHING -- 300 vs 296 B. Head of a 5-member family (296 B).
 *
 * The message layout, the 14-byte template copy, the three 3-byte packings and the block
 * order are all right. What is left: mwcc spends EIGHT callee-saved registers
 * (r3..sl) where the ROM spends two (r3, r4), which is the 4 B.
 *
 * SOLVED here -- do NOT rediscover:
 *  - the flags word is read then truncated: `(unsigned short)*flags`, hence the
 *    lsl#16/lsr#16 before the two `tst`s.
 *  - the body must be written as the POSITIVE case (`if (bit0 && bit4) { …; return 1; }
 *    return 0;`) so the failure path branches to the end, as the ROM does. The
 *    early-return form emits the return-0 block inline near the top.
 *  - declaration order `m` before `v` puts the message buffer at sp+0xc, the ROM layout.
 *  - the indirect call takes THREE arguments (obj, &m, 0xe); Ghidra shows seven.
 *  - the template copy is a whole-struct assignment from data_ov149_020d077c; mwcc emits
 *    the ROM's 3-iteration ldrh/ldrh/strh/strh loop plus one trailing halfword for it.
 *
 * Ruled out for the register pressure: interleaving each `v.<field> = w[i]` with its own
 * packing group (that is 12 B LONGER, 308). The ROM loads each word once, packs it, and
 * stores it to the stack copy afterwards, all in scratch registers -- reproducing that
 * scheduling without the spills is the open part. */
struct Msg { unsigned short h[7]; };
struct vec { int x, y, z; };
extern struct Msg data_ov149_020d077c;

int func_ov149_020cfad8(int self, int a, unsigned int *flags, int d) {
    int *node = *(int **)(self + 0x214);
    struct Msg m;
    struct vec v;
    unsigned char *p;
    void (*cb)(int, struct Msg *, int);

    if (((unsigned short)*flags & 1) != 0 && ((unsigned short)*flags & 0x10) != 0) {
    m = data_ov149_020d077c;
    p = (unsigned char *)&m;
    v = *(struct vec *)node[1];
    p[5]  = (unsigned char)(((unsigned int)v.x >> 0x10 & 0x7f) | ((unsigned int)v.x >> 0x18 & 0x80));
    p[6]  = (unsigned char)((unsigned int)v.x >> 8);
    p[7]  = (unsigned char)v.x;
    p[8]  = (unsigned char)(((unsigned int)v.y >> 0x10 & 0x7f) | ((unsigned int)v.y >> 0x18 & 0x80));
    p[9]  = (unsigned char)((unsigned int)v.y >> 8);
    p[10] = (unsigned char)v.y;
    p[11] = (unsigned char)(((unsigned int)v.z >> 0x10 & 0x7f) | ((unsigned int)v.z >> 0x18 & 0x80));
    p[12] = (unsigned char)((unsigned int)v.z >> 8);
    p[13] = (unsigned char)v.z;
    cb = *(void (**)(int, struct Msg *, int))(*node + 0x24);
    if (cb != 0) {
        cb(*node, &m, 0xe);
    }
    *(signed char *)(*node + 0x1c7) = 0;
    return 1;
    }
    return 0;
}
