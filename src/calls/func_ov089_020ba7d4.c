extern void *NNSi_FndGetCurrentRootHeap();
extern void func_ov089_020ba810();
extern void func_ov022_020a4798();
extern void func_ov089_020bab0c();
extern void func_ov022_0209fb24();

void *func_ov089_020ba7d4(void *a)
{
    void *r = NNSi_FndGetCurrentRootHeap();
    func_ov089_020ba810(a);
    func_ov022_020a4798(r, 0x44, 0xca);
    func_ov089_020bab0c(r);
    return (void *)func_ov022_0209fb24;
}
