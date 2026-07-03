extern int NNSi_FndGetCurrentRootHeap();extern void func_ov096_020baf08();extern void func_ov022_0209fab4();extern int data_ov096_020bc0c0;
void func_ov096_020ba7fc(int p) {
    int r = NNSi_FndGetCurrentRootHeap(p);
    func_ov096_020baf08(r);
    func_ov022_0209fab4(r);
    *(int *)&data_ov096_020bc0c0 = 0;
}
