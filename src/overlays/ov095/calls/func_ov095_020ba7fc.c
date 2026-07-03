extern int func_02023c00(void);
extern void func_ov095_020bb3dc(int a);
extern void func_ov002_02051fc8(int a, int b);
extern void func_ov022_0209fab4(int a);
extern int data_ov095_020bcba0;
void func_ov095_020ba7fc(void) {
    int obj = func_02023c00();
    func_ov095_020bb3dc(obj);
    func_ov002_02051fc8(obj + 0x2c2c, obj + 0x910);
    func_ov002_02051fc8(obj + 0x2c80, obj + 0x910);
    func_ov022_0209fab4(obj);
    data_ov095_020bcba0 = 0;
}
