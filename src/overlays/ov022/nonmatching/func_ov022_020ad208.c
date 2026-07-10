/*
 * NONMATCHING (p5/p6 register-coloring tie, size-exact byte-diff @0x25). This
 * 6-arg stack marshal is otherwise fully matched: sub-struct aggregate copy for
 * the 3-word block (ldm/stm), a single chained `if (param_2==1)` block so the
 * cmp flags are reused across the addeq/ldrbeq/cmpeq predication, register
 * locals p5/p6 to avoid spilling the stack params, and `buf.b13 |= 2` to reuse
 * the known-zero (andne r2,#0xff / orrne #2) instead of a bare mov #2. The only
 * divergence: mwcc puts param_6 in r1 / param_5 in r0, the original the reverse
 * (param_6=r0, param_5=r1). Tried decl-order and store-order swaps. Byte-equiv.
 */
extern void func_ov022_0209246c(int a, int b, void *c);

struct words3_020ad208 {
    unsigned int a;
    unsigned int b;
    unsigned int c;
};

struct marshal_020ad208 {
    unsigned char b0;
    unsigned char pad1[3];
    struct words3_020ad208 w;
    short h10;
    short h12;
    unsigned char b14;
    unsigned char b13;
    unsigned char pad2[6];
};

void func_ov022_020ad208(int param_1, int param_2, struct words3_020ad208 *param_3, int param_4,
                         unsigned int param_5, int param_6) {
    struct marshal_020ad208 buf;
    int p6 = param_6;
    unsigned int p5 = param_5;
    buf.b0 = *(unsigned char *)(param_1 + 9);
    buf.w = *param_3;
    buf.h10 = (short)param_4;
    buf.b14 = (unsigned char)p6;
    buf.b13 = 0;
    buf.h12 = (short)p5;
    if (param_2 == 1) {
        p6 = param_1 + 0x2000;
        p5 = *(unsigned char *)(p6 + 0x6c4);
        if (p5 == 1 && (*(unsigned int *)(p6 + 0x6bc) & 0x20) != 0) {
            buf.b13 |= 2;
        }
    }
    func_ov022_0209246c(param_1 + 0x2648, param_2, &buf);
}
