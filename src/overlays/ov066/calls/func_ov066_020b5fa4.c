extern int data_ov066_020b6b80;
extern void func_ov066_020b6150();
extern void func_ov066_020b61b0();

void func_ov066_020b5fa4(int this_) {
    char *p = (char *)(data_ov066_020b6b80 + 0xc50);
    func_ov066_020b6150(this_, (int)(p + 0x2000), *(short *)(this_ + 0x2aba));
    func_ov066_020b61b0(this_, (int)(p + 0x2000));
}
