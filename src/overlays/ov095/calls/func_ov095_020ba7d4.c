extern int func_02023c00(void);
extern void func_ov095_020ba83c(int a);
extern void func_ov095_020bb2d0(int a);
extern void func_ov022_020a4798(int a, int b, int c);
extern void func_ov022_0209fb24(void);
void *func_ov095_020ba7d4(int param) {
    int obj = func_02023c00();
    func_ov095_020ba83c(param);
    func_ov095_020bb2d0(obj);
    func_ov022_020a4798(obj, 0x4d, 0xcd);
    return (void *)func_ov022_0209fb24;
}
