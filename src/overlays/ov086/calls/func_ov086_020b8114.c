extern int func_02023c00(void);
extern void func_ov086_020b815c(int a);
extern void func_ov086_020b8814(int a);
extern void func_ov022_020a4798(int a, int b, int c);
extern void func_ov022_0209fb24(void);
void *func_ov086_020b8114(int param) {
    int obj = func_02023c00();
    func_ov086_020b815c(param);
    func_ov086_020b8814(obj);
    func_ov022_020a4798(obj, 0x53, 0xd5);
    return (void *)func_ov022_0209fb24;
}
