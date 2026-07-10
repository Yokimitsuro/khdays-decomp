extern int *data_ov022_020b2e60;
extern unsigned short func_01fffe14(void);
extern int func_ov022_020886d0(unsigned int arg0);
int func_ov022_02083e08(void) {
    int r = 1;
    unsigned short f = *(unsigned short *)data_ov022_020b2e60;
    if ((f & 0x10) || (f & 8) || (f & 2)) r = 0;
    if (func_ov022_020886d0(func_01fffe14()) != 0) r = 0;
    return r;
}
