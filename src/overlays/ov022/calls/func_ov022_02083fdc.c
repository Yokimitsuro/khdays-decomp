extern int func_ov022_02083e54(void);
extern int *data_ov022_020b2e60;
int func_ov022_02083fdc(void) {
    if (func_ov022_02083e54() == 0) {
        *(unsigned short *)data_ov022_020b2e60 &= ~0x200;
        return 0;
    }
    *(unsigned short *)data_ov022_020b2e60 |= 0x200;
    return 1;
}
