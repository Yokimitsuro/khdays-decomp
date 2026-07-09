extern short func_02030788(void);
extern unsigned int func_ov022_020a35f4(unsigned int *arg0, int arg1);
unsigned int func_ov022_020a0870(unsigned int *arg0, int arg1) {
    unsigned int r = 0;
    if (func_02030788() == 0) {
        r = func_ov022_020a35f4(arg0, arg1);
        arg0[0x118] = r;
    }
    return r;
}
