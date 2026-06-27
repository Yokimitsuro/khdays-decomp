extern void *NNSi_FndGetCurrentRootHeap();
extern void func_ov051_020b5a70();
extern void func_ov022_020a4798();
extern void func_ov051_020b5d6c();
extern void func_ov022_0209fb24();

void *func_ov051_020b5a34(void *a)
{
    void *r = NNSi_FndGetCurrentRootHeap();
    func_ov051_020b5a70(a);
    func_ov022_020a4798(r, 0x44, 0xca);
    func_ov051_020b5d6c(r);
    return (void *)func_ov022_0209fb24;
}
