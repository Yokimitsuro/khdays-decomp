extern int func_02023c00(void);
extern void func_ov002_02051fc8(int a, int b);
extern int func_02020a9c(void);
extern void func_ov035_020b3adc(int a);
extern void func_ov022_0209fab4(int a);
extern int data_ov035_020b4ca0;
void func_ov035_020b3264(void) {
    int obj = func_02023c00();
    func_ov002_02051fc8(obj + 0x2c50, obj + 0x910);
    if (func_02020a9c() != 0x2a)
        func_ov035_020b3adc(obj);
    func_ov022_0209fab4(obj);
    data_ov035_020b4ca0 = 0;
}
