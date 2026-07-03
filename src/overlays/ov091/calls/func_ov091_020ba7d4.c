extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov091_020ba840(int a);
extern int func_02020a9c(void);
extern void func_ov091_020bafd0(int a);
extern void func_ov022_020a4798(int a, int b, int c);
extern void func_ov022_0209fb24(void);
void *func_ov091_020ba7d4(int param) {
    int obj = NNSi_FndGetCurrentRootHeap();
    func_ov091_020ba840(param);
    if (func_02020a9c() != 0x2a)
        func_ov091_020bafd0(obj);
    func_ov022_020a4798(obj, 0x47, 0xd3);
    return (void *)func_ov022_0209fb24;
}
