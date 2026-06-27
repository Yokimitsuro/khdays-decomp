extern void *NNSi_FndGetCurrentRootHeap();
extern void func_ov050_020b615c();
extern void func_ov022_0209fab4();

void func_ov050_020b5a5c(void)
{
    void *p = NNSi_FndGetCurrentRootHeap();
    func_ov050_020b615c(p);
    func_ov022_0209fab4(p);
}
