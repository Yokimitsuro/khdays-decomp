extern int func_02023c00(void);
extern void func_ov098_020ba81c(int a);
extern void func_ov022_020a4798(int a, int b, int c);
extern void func_ov098_020bb2d4(int a);
extern void func_ov022_0209fb24(void);
void *func_ov098_020ba7d4(int param) {
    int obj = func_02023c00();
    func_ov098_020ba81c(param);
    func_ov022_020a4798(obj, 0x4e, 0xc7);
    func_ov098_020bb2d4(obj);
    return (void *)func_ov022_0209fb24;
}
