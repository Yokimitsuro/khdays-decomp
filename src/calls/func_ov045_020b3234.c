extern void *NNSi_FndGetCurrentRootHeap();
extern void func_ov045_020b3298();
extern void func_ov045_020b4130();
extern void func_ov022_020a4798();
extern void func_ov022_0209fb24();

void *func_ov045_020b3234(void *a)
{
    void *r = NNSi_FndGetCurrentRootHeap();
    func_ov045_020b3298(a);
    func_ov045_020b4130(r);
    func_ov022_020a4798(r, 0x4a, 0xc9);
    return (void *)func_ov022_0209fb24;
}
