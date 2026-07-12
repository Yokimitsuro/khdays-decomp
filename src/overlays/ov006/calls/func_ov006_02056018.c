/* Store a u16 at +0x95c2 of the ov006 global object. */
extern int data_ov006_02056664;
void func_ov006_02056018(int param_1) {
    *(short *)(data_ov006_02056664 + 0x95c2) = param_1;
}
