extern void func_ov022_020a4490(int self, int cue, int situation);
extern void func_0202accc(int a, int b, int c, short d);
extern void func_01fff774(int a, int b, int c);
extern int data_ov059_020b7320;

void func_ov059_020b63cc(int self, int obj) {
    int idx = 0;
    if (*(int *)(*(int *)&data_ov059_020b7320 + 0x2000 + 0xc50) != 0) {
        idx = 1;
        func_ov022_020a4490(self, 0xce, 2);
    } else {
        func_ov022_020a4490(self, 0xce, 3);
    }
    *(int *)(obj + 0x124) = 1;
    func_0202accc(obj + 0x128, 0, obj + 0x208, idx);
    func_0202accc(obj + 0x128, 2, obj + 0x208, idx);
    func_01fff774(obj + 0x128, 0, 0);
    func_01fff774(obj + 0x128, 2, 0);
}
