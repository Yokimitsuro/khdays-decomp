/* NONMATCHING: parameter-spill tie, byte-exact structure. With four params and
 * nine callee-saved registers in play, the original spills out1 (param_3) to the
 * stack and keeps out2 in sb; mwcc spills out2 (param_4) and keeps out1 instead,
 * so the param moves and the flag-setting `movs` land on different registers.
 * The 8-word const-table stack copy (ldm/stm), the 4-iteration mask loop and the
 * out-param writes all reproduce. Semantics exact. */
extern int func_020358f4(int kind, unsigned int a);
extern unsigned int data_ov022_020b26b0;

struct Pair020a22f0 { unsigned int arg, shift; };
struct Tbl020a22f0 { struct Pair020a22f0 p[4]; };

int func_ov022_020a22f0(int obj, int cond, unsigned int *out1, unsigned char *out2) {
    struct Tbl020a22f0 tbl = *(struct Tbl020a22f0 *)&data_ov022_020b26b0;
    int amt = 0;
    unsigned int mask = 0;
    if (cond != 0) {
        int i = 0;
        do {
            if (func_020358f4(*(unsigned char *)(obj + 9), tbl.p[i].arg) != 0) {
                amt = 0xa000;
                mask |= 1 << (tbl.p[i].shift & 0xff);
            }
            i = i + 1;
        } while (i < 4);
    }
    if (out1 != 0 && mask != 0) *out1 = mask;
    if (out2 != 0) *out2 = (char)(amt >> 0xc);
    return mask != 0;
}
