/* Set the +0x8be1 byte of the second ov024 global object to 1. */
extern int data_ov024_02093a20;
void func_ov024_02083318(void) {
    *(signed char *)((&data_ov024_02093a20)[1] + 0x8be1) = 1;
}
