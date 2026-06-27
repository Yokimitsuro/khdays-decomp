extern void *NNSi_FndGetCurrentRootHeap();
extern void func_ov033_020b3270();
extern void func_ov022_020a4798();
extern void func_ov033_020b356c();
extern void func_ov022_0209fb24();

void *func_ov033_020b3234(void *a)
{
    void *r = NNSi_FndGetCurrentRootHeap();
    func_ov033_020b3270(a);
    func_ov022_020a4798(r, 0x44, 0xca);
    func_ov033_020b356c(r);
    return (void *)func_ov022_0209fb24;
}
