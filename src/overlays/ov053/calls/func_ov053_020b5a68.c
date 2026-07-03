extern int func_02023c00(void);
extern void func_ov002_02051fc8(int a, int b);
extern void func_ov053_020b790c(int a);
extern void func_ov022_0209fab4(int a);
extern int data_ov053_020b7e60;
void func_ov053_020b5a68(void) {
    int obj = func_02023c00();
    func_ov002_02051fc8(obj + 0x2c2c, obj + 0x910);
    func_ov002_02051fc8(obj + 0x2c80, obj + 0x910);
    func_ov053_020b790c(obj);
    func_ov022_0209fab4(obj);
    data_ov053_020b7e60 = 0;
}
