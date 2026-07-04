extern int data_ov085_020b9260;
extern void func_ov085_020b8830();
extern void func_ov085_020b8890();

void func_ov085_020b8684(int this_) {
    char *p = (char *)(data_ov085_020b9260 + 0xc50);
    func_ov085_020b8830(this_, (int)(p + 0x2000), *(short *)(this_ + 0x2aba));
    func_ov085_020b8890(this_, (int)(p + 0x2000));
}
