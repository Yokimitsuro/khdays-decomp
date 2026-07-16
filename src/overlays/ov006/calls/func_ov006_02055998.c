/* func_ov006_02055998 -- store param_2 into the Mission Mode-screen word array at ctx+0x9524[param_1]
 * (param_1 in 0..3). Returns 0 if the context is not up or the index is out of range, else 1. */
extern int data_ov006_02056664;   /* -> Mission Mode-screen context */

int func_ov006_02055998(int param_1, int param_2) {
    if (data_ov006_02056664 == 0) {
        return 0;
    }
    if (param_1 < 0 || param_1 >= 4) {
        return 0;
    }
    *(int *)(data_ov006_02056664 + param_1 * 4 + 0x9524) = param_2;
    return 1;
}
