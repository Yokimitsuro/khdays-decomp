extern void func_01fff774(unsigned short *arg0, int arg1, int arg2);
void func_ov022_02094b40(int arg0) {
    *(int *)(arg0 + 8) = 1;
    func_01fff774((unsigned short *)(arg0 + 0x21c), 0, 0);
    func_01fff774((unsigned short *)(arg0 + 0x21c), 2, 0);
}
