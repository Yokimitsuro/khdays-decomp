extern void func_01fff774(unsigned short *arg0, int arg1, int arg2);
void func_ov022_02097038(int arg0, int arg1) {
    func_01fff774((unsigned short *)(*(int *)(arg0 + 0x20) + 4), 0, arg1);
    *(int *)(arg0 + 0x7b0) = arg1;
}
