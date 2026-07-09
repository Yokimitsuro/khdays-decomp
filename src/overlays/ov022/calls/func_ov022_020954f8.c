extern void func_ov022_02094b80(int arg0, int arg1);
void func_ov022_020954f8(unsigned int *arg0) {
    if (arg0[1] != 8 && arg0[1] != 6) return;
    *arg0 |= 0x200;
    func_ov022_02094b80((int)arg0, 0);
}
