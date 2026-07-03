extern int func_02023c00(void);
extern void func_ov073_020b818c(int a);
extern void func_ov022_020a4798(int a, int b, int c);
extern void func_ov073_020b9f94(int a);
extern void func_ov022_0209fb24(void);
void *func_ov073_020b8114(int param) {
    int obj = func_02023c00();
    *(int *)(obj + 0x2e1c) = 0;
    func_ov073_020b818c(param);
    func_ov022_020a4798(obj, 0x45, 0xc6);
    func_ov073_020b9f94(obj);
    return (void *)func_ov022_0209fb24;
}
