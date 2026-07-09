extern int *data_ov022_020b2e60;
extern void func_ov022_02086ec0(int arg0);
void func_ov022_02083fa4(int arg0) {
    if ((*(unsigned short *)data_ov022_020b2e60 & 0x40) != 0) return;
    func_ov022_02086ec0(arg0);
    *(unsigned short *)data_ov022_020b2e60 |= 0x40;
}
