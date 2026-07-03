extern int func_02023c00(void);
extern void func_ov060_020b5a90(int a);
extern void func_ov060_020b5f6c(int a);
extern void func_ov022_020a4798(int a, int b, int c);
extern void func_ov022_0209fb24(void);
void *func_ov060_020b5a34(int param) {
    int obj = func_02023c00();
    func_ov060_020b5a90(param);
    func_ov060_020b5f6c(obj);
    func_ov022_020a4798(obj, 0x54, 0xd7);
    return (void *)func_ov022_0209fb24;
}
