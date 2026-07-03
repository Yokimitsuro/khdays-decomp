extern int func_02023c00(void);
extern void func_ov002_02051fc8(int a, int b);
extern void func_ov084_020b88f4(int a);
extern void func_ov022_0209fab4(int a);
extern int data_ov084_020b9a20;
void func_ov084_020b813c(void) {
    int obj = func_02023c00();
    func_ov002_02051fc8(obj + 0x2c2c, obj + 0x910);
    func_ov084_020b88f4(obj);
    func_ov022_0209fab4(obj);
    data_ov084_020b9a20 = 0;
}
