/* Report whether the +0x8be1 byte of the second ov024 global object is zero. */
extern int data_ov024_02093a20;
int func_ov024_02083334(void) {
    return *(unsigned char *)((&data_ov024_02093a20)[1] + 0x8be1) == 0;
}
