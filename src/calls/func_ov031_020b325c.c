extern void *NNSi_FndGetCurrentRootHeap();
extern void func_ov031_020b395c();
extern void func_ov022_0209fab4();

void func_ov031_020b325c(void)
{
    void *p = NNSi_FndGetCurrentRootHeap();
    func_ov031_020b395c(p);
    func_ov022_0209fab4(p);
}
