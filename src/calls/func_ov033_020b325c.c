extern void *NNSi_FndGetCurrentRootHeap();
extern void func_ov033_020b3608();
extern void func_ov022_0209fab4();

void func_ov033_020b325c(void)
{
    void *p = NNSi_FndGetCurrentRootHeap();
    func_ov033_020b3608(p);
    func_ov022_0209fab4(p);
}
