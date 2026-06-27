extern void *NNSi_FndGetCurrentRootHeap();
extern void func_ov088_020baefc();
extern void func_ov022_0209fab4();

void func_ov088_020ba7fc(void)
{
    void *p = NNSi_FndGetCurrentRootHeap();
    func_ov088_020baefc(p);
    func_ov022_0209fab4(p);
}
