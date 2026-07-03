extern int func_02023c00(void);
extern void func_ov096_020ba81c(int a);
extern void func_ov096_020bae08(int a);
extern void func_ov022_020a4798(int a, int b, int c);
extern void func_ov022_0209fb24(void);
void *func_ov096_020ba7d4(int param) {
    int obj = func_02023c00();
    func_ov096_020ba81c(param);
    func_ov096_020bae08(obj);
    func_ov022_020a4798(obj, 0x4b, 0xce);
    return (void *)func_ov022_0209fb24;
}
