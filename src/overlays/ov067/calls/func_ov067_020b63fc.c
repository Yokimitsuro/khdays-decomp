extern int func_ov022_020a4490(int self, int cue, int situation);
extern void func_0202accc(int a, int b, int c, short d);
extern void func_01fff774(int a, int b, int c);

void func_ov067_020b63fc(int self, int *node) {
    int sit = 0;
    int idx = 0;
    if (node[0] != 0) {
        sit = 1;
        idx = 2;
    }
    *(int *)((char *)node + 0x370) = func_ov022_020a4490(self, 0xd5, sit);
    func_0202accc((int)node + 0xc, 0, node[0x45], idx);
    func_0202accc((int)node + 0xc, 2, node[0x45], idx);
    func_0202accc((int)node + 0xc, 1, node[0x45], idx);
    func_01fff774((int)node + 0xc, 0, 0);
    func_01fff774((int)node + 0xc, 2, 0);
    func_01fff774((int)node + 0xc, 1, 0);
    node[2] = 1;
    *(int *)((char *)node + 0x118) = 0;
}
