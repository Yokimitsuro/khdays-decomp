extern int func_02023c00(void);
extern void func_ov065_020b5a90(int a);
extern void func_ov065_020b6174(int a);
extern void func_ov022_020a4798(int a, int b, int c);
extern void func_ov022_0209fb24(void);
void *func_ov065_020b5a34(int param) {
    int obj = func_02023c00();
    func_ov065_020b5a90(param);
    func_ov065_020b6174(obj);
    func_ov022_020a4798(obj, 0x48, 0xd6);
    return (void *)func_ov022_0209fb24;
}
