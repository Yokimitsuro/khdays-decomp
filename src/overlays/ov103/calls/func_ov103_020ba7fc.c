extern int NNSi_FndGetCurrentRootHeap();extern void func_ov103_020baf94();extern void func_ov022_0209fab4();extern int data_ov103_020bc120;
void func_ov103_020ba7fc(int p) {
    int r = NNSi_FndGetCurrentRootHeap(p);
    func_ov103_020baf94(r);
    func_ov022_0209fab4(r);
    *(int *)&data_ov103_020bc120 = 0;
}
