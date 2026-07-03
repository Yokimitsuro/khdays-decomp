extern int func_02023c00(void);
extern void func_ov035_020b32a0(int a);
extern int func_02020a9c(void);
extern void func_ov035_020b3a30(int a);
extern void func_ov022_020a4798(int a, int b, int c);
extern void func_ov022_0209fb24(void);
void *func_ov035_020b3234(int param) {
    int obj = func_02023c00();
    func_ov035_020b32a0(param);
    if (func_02020a9c() != 0x2a)
        func_ov035_020b3a30(obj);
    func_ov022_020a4798(obj, 0x47, 0xd3);
    return (void *)func_ov022_0209fb24;
}
