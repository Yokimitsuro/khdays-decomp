extern void *NNSi_FndGetCurrentRootHeap();
extern void func_ov089_020baba8();
extern void func_ov022_0209fab4();

void func_ov089_020ba7fc(void)
{
    void *p = NNSi_FndGetCurrentRootHeap();
    func_ov089_020baba8(p);
    func_ov022_0209fab4(p);
}
