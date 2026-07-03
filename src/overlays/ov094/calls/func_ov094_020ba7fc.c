extern int NNSi_FndGetCurrentRootHeap();extern void func_ov094_020baed0();extern void func_ov022_0209fab4();extern int data_ov094_020bc240;
void func_ov094_020ba7fc(int p) {
    int r = NNSi_FndGetCurrentRootHeap(p);
    func_ov094_020baed0(r);
    func_ov022_0209fab4(r);
    *(int *)&data_ov094_020bc240 = 0;
}
