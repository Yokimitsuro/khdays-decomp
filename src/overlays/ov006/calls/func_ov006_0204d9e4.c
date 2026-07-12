/* Clear +0x2c of the ov006 global object. */
extern int data_ov006_020565e4;
void func_ov006_0204d9e4(void) {
    *(int *)(data_ov006_020565e4 + 0x2c) = 0;
}
