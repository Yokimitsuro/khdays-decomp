extern int data_ov102_020bb920;
extern void func_ov102_020baef0();
extern void func_ov102_020baf50();

void func_ov102_020bad44(int this_) {
    char *p = (char *)(data_ov102_020bb920 + 0xc50);
    func_ov102_020baef0(this_, (int)(p + 0x2000), *(short *)(this_ + 0x2aba));
    func_ov102_020baf50(this_, (int)(p + 0x2000));
}
