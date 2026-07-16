/* func_ov008_02081708 -- store param_2 into the screen's word array at ctx+0x9524[param_1]
 * (param_1 in 0..3). Returns 0 if the context is not up or the index is out of range, else 1.
 *
 * PROVENANCE: byte-identical twin of func_ov006_02055998, propagated from it. The rep's
 * "Mission Mode-screen" wording is ov006's scene identity and is not asserted here. */
extern int data_ov008_02090fa4;   /* -> screen context */

int func_ov008_02081708(int param_1, int param_2) {
    if (data_ov008_02090fa4 == 0) {
        return 0;
    }
    if (param_1 < 0 || param_1 >= 4) {
        return 0;
    }
    *(int *)(data_ov008_02090fa4 + param_1 * 4 + 0x9524) = param_2;
    return 1;
}
