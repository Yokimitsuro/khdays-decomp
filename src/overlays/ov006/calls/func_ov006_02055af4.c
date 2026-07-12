/* Store a byte at +0x9520 of the ov006 global object. */
extern int data_ov006_02056664;
void func_ov006_02055af4(int param_1) {
    *(signed char *)(data_ov006_02056664 + 0x9520) = param_1;
}
