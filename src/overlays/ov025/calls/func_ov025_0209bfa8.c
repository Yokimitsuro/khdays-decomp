extern int func_ov025_02084afc();
extern int data_ov025_020b4f6b;

int func_ov025_0209bfa8(int arg0) {
    func_ov025_02084afc(arg0);
    return *(unsigned char *)((char *)&data_ov025_020b4f6b + arg0 * 0x14);
}
