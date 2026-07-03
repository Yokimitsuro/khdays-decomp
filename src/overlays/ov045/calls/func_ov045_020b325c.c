extern int func_02023c00(void);
extern void func_0202a7dc(int a);
extern void func_ov045_020b4178(int a);
extern void func_ov022_0209fab4(int a);
extern int data_ov045_020b4c20;
void func_ov045_020b325c(void) {
    int obj = func_02023c00();
    if (*(int *)(obj + 0x2c2c) != 0) {
        func_0202a7dc(obj + 0x2c30);
        *(int *)(obj + 0x2c2c) = 0;
    }
    func_ov045_020b4178(obj);
    func_ov022_0209fab4(obj);
    data_ov045_020b4c20 = 0;
}
