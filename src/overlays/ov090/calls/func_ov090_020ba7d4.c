extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov090_020ba84c(int a);
extern void func_ov022_020a4798(int a, int b, int c);
extern void func_ov090_020bc654(int a);
extern void func_ov022_0209fb24(void);
void *func_ov090_020ba7d4(int param) {
    int obj = NNSi_FndGetCurrentRootHeap();
    *(int *)(obj + 0x2e1c) = 0;
    func_ov090_020ba84c(param);
    func_ov022_020a4798(obj, 0x45, 0xc6);
    func_ov090_020bc654(obj);
    return (void *)func_ov022_0209fb24;
}
