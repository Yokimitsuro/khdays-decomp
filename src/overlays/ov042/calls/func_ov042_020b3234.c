extern int func_02023c00(void);
extern void func_ov042_020b327c(int a);
extern void func_ov022_020a4798(int a, int b, int c);
extern void func_ov042_020b3d34(int a);
extern void func_ov022_0209fb24(void);
void *func_ov042_020b3234(int param) {
    int obj = func_02023c00();
    func_ov042_020b327c(param);
    func_ov022_020a4798(obj, 0x4e, 0xc7);
    func_ov042_020b3d34(obj);
    return (void *)func_ov022_0209fb24;
}
