extern void *NNSi_FndGetCurrentRootHeap();
extern void func_ov071_020b84e8();
extern void func_ov022_0209fab4();

void func_ov071_020b813c(void)
{
    void *p = NNSi_FndGetCurrentRootHeap();
    func_ov071_020b84e8(p);
    func_ov022_0209fab4(p);
}
