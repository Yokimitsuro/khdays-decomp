/* Convert a screen-space pair into the panel's cell coordinates: divide each
 * axis by the cell size at +0x10 and bias by the origin halfwords at +0 and +2,
 * shifted into Q12. */
extern int FX_Inv(int numerator, int denominator);

extern char *data_ov002_0207f638;

void func_ov002_02064cd8(int *out, const int *in) {
    char *ctx = data_ov002_0207f638;

    out[0] = FX_Inv(in[0], *(int *)(ctx + 0x10)) + (*(unsigned short *)ctx << 12);
    out[1] = FX_Inv(in[2], *(int *)(ctx + 0x10)) + (*(unsigned short *)(ctx + 2) << 12);
}
