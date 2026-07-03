extern int func_02023c00(void);
extern void func_ov002_02051fc8(int a, int b);
extern void func_ov060_020b6040(int a);
extern void func_ov022_0209fab4(int a);
extern int data_ov060_020b7500;
void func_ov060_020b5a5c(void) {
    int obj = func_02023c00();
    func_ov002_02051fc8(obj + 0x2c30, obj + 0x910);
    func_ov060_020b6040(obj);
    func_ov022_0209fab4(obj);
    data_ov060_020b7500 = 0;
}
