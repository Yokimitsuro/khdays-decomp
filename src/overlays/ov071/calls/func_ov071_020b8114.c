extern void *NNSi_FndGetCurrentRootHeap();
extern void func_ov071_020b8150();
extern void func_ov022_020a4798();
extern void func_ov071_020b844c();
extern void func_ov022_0209fb24();

void *func_ov071_020b8114(void *a)
{
    void *r = NNSi_FndGetCurrentRootHeap();
    func_ov071_020b8150(a);
    func_ov022_020a4798(r, 0x44, 0xca);
    func_ov071_020b844c(r);
    return (void *)func_ov022_0209fb24;
}
