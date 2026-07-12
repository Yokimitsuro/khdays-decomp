/* Stage a request record at (*(global+4))+0x188 {param_1, count=0, param_2}, flag
 * the queue busy at +0xa8, and kick func_ov002_020646e0. */
extern void func_ov002_020646e0(int a, int b);
extern int data_ov002_0207f62c;

void func_ov002_02063638(int param_1, int param_2) {
    int base = *(int *)((char *)&data_ov002_0207f62c + 4);
    *(int *)(base + 0x188) = param_1;
    *(int *)(base + 0x190) = param_2;
    *(int *)(base + 0x18c) = 0;
    *(int *)(base + 0xa8) = 1;
    func_ov002_020646e0(param_1, param_2);
}
