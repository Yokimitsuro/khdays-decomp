extern char *NNSi_FndGetCurrentRootHeap(void);
extern void func_02020a78(int, int);

int func_ov007_0204d31c(void)
{
    char *p = NNSi_FndGetCurrentRootHeap();
    int r1 = *(int *)(p + 0x5000 + 0xac0);
    func_02020a78(5, r1);
    return ~1;
}
