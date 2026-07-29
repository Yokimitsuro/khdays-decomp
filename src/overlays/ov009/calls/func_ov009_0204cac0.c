typedef void (*Ov009Callback)(void);

extern void *data_ov009_020563e0;
extern void *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov009_0204dc00(int mode);
extern void func_ov009_020557dc(void);
extern void func_ov009_0204cb4c(void);

Ov009Callback func_ov009_0204cac0(void)
{
    data_ov009_020563e0 = NNSi_FndGetCurrentRootHeap();
    func_ov009_0204dc00(0);
    func_ov009_020557dc();
    return func_ov009_0204cb4c;
}
