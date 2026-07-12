/* Report whether the u16 at the second ov024 global object equals 2. */
extern int data_ov024_02093a20;
int func_ov024_020832a4(void) {
    return *(unsigned short *)((&data_ov024_02093a20)[1]) == 2;
}
