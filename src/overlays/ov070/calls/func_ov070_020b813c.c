extern void *NNSi_FndGetCurrentRootHeap();
extern void func_ov070_020b883c();
extern void func_ov022_0209fab4();

void func_ov070_020b813c(void)
{
    void *p = NNSi_FndGetCurrentRootHeap();
    func_ov070_020b883c(p);
    func_ov022_0209fab4(p);
}
