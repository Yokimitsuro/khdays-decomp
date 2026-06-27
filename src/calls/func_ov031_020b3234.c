extern void *NNSi_FndGetCurrentRootHeap();
extern void func_ov031_020b3270();
extern void func_ov022_020a4798();
extern void func_ov031_020b38e0();
extern void func_ov022_0209fb24();

void *func_ov031_020b3234(void *a)
{
    void *r = NNSi_FndGetCurrentRootHeap();
    func_ov031_020b3270(a);
    func_ov022_020a4798(r, 0x42, 0xcb);
    func_ov031_020b38e0(r);
    return (void *)func_ov022_0209fb24;
}
