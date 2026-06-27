extern void *NNSi_FndGetCurrentRootHeap();
extern void func_ov050_020b5a70();
extern void func_ov022_020a4798();
extern void func_ov050_020b60e0();
extern void func_ov022_0209fb24();

void *func_ov050_020b5a34(void *a)
{
    void *r = NNSi_FndGetCurrentRootHeap();
    func_ov050_020b5a70(a);
    func_ov022_020a4798(r, 0x42, 0xcb);
    func_ov050_020b60e0(r);
    return (void *)func_ov022_0209fb24;
}
