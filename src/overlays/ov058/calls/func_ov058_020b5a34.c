extern int func_02023c00(void);
extern void func_ov058_020b5a9c(int a);
extern void func_ov058_020b6530(int a);
extern void func_ov022_020a4798(int a, int b, int c);
extern void func_ov022_0209fb24(void);
void *func_ov058_020b5a34(int param) {
    int obj = func_02023c00();
    func_ov058_020b5a9c(param);
    func_ov058_020b6530(obj);
    func_ov022_020a4798(obj, 0x4d, 0xcd);
    return (void *)func_ov022_0209fb24;
}
