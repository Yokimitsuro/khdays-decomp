/* Store a byte at +0x95ad of the ov006 global object. */
extern int data_ov006_02056664;
void func_ov006_02056000(int param_1) {
    *(signed char *)(data_ov006_02056664 + 0x95ad) = param_1;
}
