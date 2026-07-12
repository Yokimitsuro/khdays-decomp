/*
 * Remap a code value. Values in [0x1e, 0x2d] are looked up in the 13-entry signed
 * byte table at param_2+8: return the index of the entry matching (value-0x1e), or
 * -1 if a -1 sentinel is reached first. Values >= 0x2e are shifted down by 0x13;
 * anything else passes through unchanged.
 */
int func_ov002_02052270(int param_1, int param_2, int param_3) {
    if (param_3 >= 0x1e && param_3 < 0x2e) {
        int i;
        int target = param_3 - 0x1e;
        param_3 = -1;
        i = 0;
        do {
            int v = *(signed char *)(param_2 + i + 8);
            if (target == v) {
                param_3 = i;
                break;
            }
            if (v == param_3) {
                break;
            }
            i = i + 1;
        } while (i < 0xd);
    } else if (param_3 >= 0x2e) {
        param_3 = param_3 - 0x13;
    }
    return param_3;
}
