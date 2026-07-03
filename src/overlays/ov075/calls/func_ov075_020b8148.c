extern int func_02023c00(void);
extern void func_ov075_020b989c(int a);
extern void func_ov002_02051fc8(int a, int b);
extern void func_ov075_020b87c4(int a);
extern void func_ov075_020b9b14(int a);
extern void func_ov022_0209fab4(int a);
extern int data_ov075_020b9e20;
void func_ov075_020b8148(void) {
    int obj = func_02023c00();
    func_ov075_020b989c(obj);
    func_ov002_02051fc8(obj + 0x2c2c, obj + 0x910);
    func_ov075_020b87c4(obj);
    func_ov075_020b9b14(obj);
    func_ov022_0209fab4(obj);
    data_ov075_020b9e20 = 0;
}
