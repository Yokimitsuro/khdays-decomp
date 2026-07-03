extern int func_02023c00(void);
extern void func_ov101_020ba830(int a);
extern void func_ov101_020baf14(int a);
extern void func_ov022_020a4798(int a, int b, int c);
extern void func_ov022_0209fb24(void);
void *func_ov101_020ba7d4(int param) {
    int obj = func_02023c00();
    func_ov101_020ba830(param);
    func_ov101_020baf14(obj);
    func_ov022_020a4798(obj, 0x48, 0xd6);
    return (void *)func_ov022_0209fb24;
}
