extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov022_020863b4(int arg0);
extern void func_ov022_02086058(int arg0);

void func_ov022_020840c8(void) {
    int h = NNSi_FndGetCurrentRootHeap();
    func_ov022_020863b4(h + 0x3c);
    func_ov022_02086058(h + 0xe8);
}
