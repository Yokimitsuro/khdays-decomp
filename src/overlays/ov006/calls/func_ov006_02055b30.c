/* func_ov006_02055b30 -- set the Mission Mode-screen "mode" field (ctx+0x9508) if in range 1..4.
 * Returns 0 if the context is not up or the value is out of range, else 1. */
extern int data_ov006_02056664;   /* -> Mission Mode-screen context */

int func_ov006_02055b30(unsigned int param_1) {
    if (data_ov006_02056664 == 0) {
        return 0;
    }
    if (param_1 != 0 && param_1 <= 4) {
        *(unsigned int *)(data_ov006_02056664 + 0x9508) = param_1;
        return 1;
    }
    return 0;
}
