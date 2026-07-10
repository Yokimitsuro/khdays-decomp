extern int NNSi_FndGetCurrentRootHeap(void);
extern int func_ov022_02083f0c(void);
extern void func_ov022_020852c0(int arg0);
extern int func_ov022_020848ec(void);
void func_ov022_02085280(void) {
    int h = NNSi_FndGetCurrentRootHeap();
    func_ov022_02083f0c();
    if ((*(unsigned int *)(h + 4) & 2) != 0) {
        func_ov022_020852c0(1);
        return;
    }
    if (!func_ov022_020848ec()) return;
    func_ov022_020852c0(1);
}
