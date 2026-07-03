extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov002_02051fc8(int a, int b);
extern void func_ov090_020bc6ac(int a);
extern void func_ov022_0209fab4(int a);
extern int data_ov090_020bcc00;
void func_ov090_020ba808(void) {
    int obj = NNSi_FndGetCurrentRootHeap();
    func_ov002_02051fc8(obj + 0x2c2c, obj + 0x910);
    func_ov002_02051fc8(obj + 0x2c80, obj + 0x910);
    func_ov090_020bc6ac(obj);
    func_ov022_0209fab4(obj);
    data_ov090_020bcc00 = 0;
}
