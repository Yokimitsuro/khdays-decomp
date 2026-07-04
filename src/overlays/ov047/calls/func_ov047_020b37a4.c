extern int data_ov047_020b4380;
extern void func_ov047_020b3950();
extern void func_ov047_020b39b0();

void func_ov047_020b37a4(int this_) {
    char *p = (char *)(data_ov047_020b4380 + 0xc50);
    func_ov047_020b3950(this_, (int)(p + 0x2000), *(short *)(this_ + 0x2aba));
    func_ov047_020b39b0(this_, (int)(p + 0x2000));
}
