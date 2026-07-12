/* If the ov006 global object exists, store a byte at +0x950c and return 1; else 0. */
extern int data_ov006_02056664;
int func_ov006_02055b0c(int param_1) {
    if (data_ov006_02056664 == 0) return 0;
    *(signed char *)(data_ov006_02056664 + 0x950c) = param_1;
    return 1;
}
