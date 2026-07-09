extern void func_ov022_02089584(int arg0, int arg1);
extern void func_ov022_02092438(int arg0, int arg1);
void func_ov022_0209ccb0(int arg0, int arg1) {
    if (*(int *)(arg0 + 0x7b8) != 0) func_ov022_02089584(*(int *)(arg0 + 0x7b8), arg1);
    if (*(int *)(arg0 + 0x7c8) != 0) func_ov022_02089584(*(int *)(arg0 + 0x7c8), arg1);
    func_ov022_02092438(arg0 + 0x2648, arg1);
}
