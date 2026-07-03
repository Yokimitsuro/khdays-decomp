extern int func_02023c00(void);
extern void func_ov036_020b32a4(int a);
extern void func_ov036_020b497c(int a);
extern void func_ov036_020b4b9c(int a);
extern void func_ov036_020b389c(int a);
extern void func_ov022_020a4798(int a, int b, int c);
extern void func_ov022_0209fb24(void);
void *func_ov036_020b3234(int param) {
    int obj = func_02023c00();
    func_ov036_020b32a4(param);
    func_ov036_020b497c(obj);
    func_ov036_020b4b9c(obj);
    func_ov036_020b389c(obj);
    func_ov022_020a4798(obj, 0x4c, 0xcc);
    return (void *)func_ov022_0209fb24;
}
