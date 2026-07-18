extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_0202a440(int a);
extern void NNSi_FndFreeFromDefaultHeap(int a);
extern void func_ov002_02051fc8(int a, int b);
extern void func_ov044_020b4868(int a);
extern void func_ov022_0209fab4(int a);
extern unsigned char data_0204c240;
extern int data_ov044_020b5620;

void func_ov044_020b32b4(void) {
    int base = NNSi_FndGetCurrentRootHeap();
    if ((data_0204c240 & 4) == 0) {
        func_0202a440(base + 0x2c2c);
        NNSi_FndFreeFromDefaultHeap(*(int *)(base + 0x2c50));
    }
    func_ov002_02051fc8(base + 0x2c54, base + 0x910);
    func_ov044_020b4868(base + 0x2ca8);
    func_ov022_0209fab4(base);
    data_ov044_020b5620 = 0;
}
