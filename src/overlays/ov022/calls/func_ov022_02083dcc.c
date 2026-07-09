extern int func_ov022_02083f0c(void);
extern int *data_ov022_020b2e60;
void func_ov022_02083dcc(int arg0) {
    unsigned short *p;
    func_ov022_02083f0c();
    p = (unsigned short *)data_ov022_020b2e60;
    if (p != 0) {
        if (arg0 != 0) *p |= 8;
        else *p &= ~8;
    }
}
