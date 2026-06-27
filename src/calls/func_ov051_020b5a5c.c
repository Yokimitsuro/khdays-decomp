extern void *NNSi_FndGetCurrentRootHeap();
extern void func_ov051_020b5e08();
extern void func_ov022_0209fab4();

void func_ov051_020b5a5c(void)
{
    void *p = NNSi_FndGetCurrentRootHeap();
    func_ov051_020b5e08(p);
    func_ov022_0209fab4(p);
}
