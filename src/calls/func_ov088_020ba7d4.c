extern void *NNSi_FndGetCurrentRootHeap();
extern void func_ov088_020ba810();
extern void func_ov022_020a4798();
extern void func_ov088_020bae80();
extern void func_ov022_0209fb24();

void *func_ov088_020ba7d4(void *a)
{
    void *r = NNSi_FndGetCurrentRootHeap();
    func_ov088_020ba810(a);
    func_ov022_020a4798(r, 0x42, 0xcb);
    func_ov088_020bae80(r);
    return (void *)func_ov022_0209fb24;
}
