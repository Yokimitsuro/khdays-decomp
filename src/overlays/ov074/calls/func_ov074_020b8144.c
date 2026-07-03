extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov002_02051fc8(int a, int b);
extern int func_02020a9c(void);
extern void func_ov074_020b89bc(int a);
extern void func_ov022_0209fab4(int a);
extern int data_ov074_020b9b80;
void func_ov074_020b8144(void) {
    int obj = NNSi_FndGetCurrentRootHeap();
    func_ov002_02051fc8(obj + 0x2c50, obj + 0x910);
    if (func_02020a9c() != 0x2a)
        func_ov074_020b89bc(obj);
    func_ov022_0209fab4(obj);
    data_ov074_020b9b80 = 0;
}
