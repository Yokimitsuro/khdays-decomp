extern int NNSi_FndGetCurrentRootHeap();extern void func_ov102_020bae54();extern void func_ov022_0209fab4();extern int data_ov102_020bb920;
void func_ov102_020ba7fc(int p) {
    int r = NNSi_FndGetCurrentRootHeap(p);
    func_ov102_020bae54(r);
    func_ov022_0209fab4(r);
    *(int *)&data_ov102_020bb920 = 0;
}
