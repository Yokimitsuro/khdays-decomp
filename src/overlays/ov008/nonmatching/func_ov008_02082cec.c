/* PROVEN TIE (leaf register allocation). Comparison logic and the (u16)(edge-org)
 * masking match byte-for-byte, but the ROM uses lr as the result scratch and
 * pushes {r3,lr} (returning via pop pc), while mwcc build 139 keeps this leaf's
 * result in ip and needs no push (one fewer register). Kept here so the ov008
 * blob stays byte-exact. */
extern int data_ov008_02090fac;

int func_ov008_02082cec(unsigned char *param_1) {
    int g = *(int *)&data_ov008_02090fac;
    int result = 0;
    if ((unsigned)param_1[2] > (unsigned short)(*(unsigned short *)(g + 0xc120) - param_1[0])) {
        if ((unsigned)param_1[3] > (unsigned short)(*(unsigned short *)(g + 0xc122) - param_1[1])) {
            result = 1;
        }
    }
    return result;
}
