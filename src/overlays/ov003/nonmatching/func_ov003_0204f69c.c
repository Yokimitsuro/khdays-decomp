extern int NNSi_FndGetCurrentRootHeap(void);
extern int func_020bd7c4(void);
extern void func_ov003_0204e91c(int a);
extern void func_0201e374(int a);
extern void func_0201e3cc(int a);
extern void func_02020a78(int a, int b);
extern void func_ov003_0204ef68(int a);

int func_ov003_0204f69c(void) {
    int heap = NNSi_FndGetCurrentRootHeap();
    int *pc;
    int c;
    if (*(int *)(heap + 0x1e10) == 0) {
        *(int *)(heap + 0x1e14) = func_020bd7c4();
    }
    func_ov003_0204e91c(heap);
    pc = (int *)(heap + 0x1000);
    c = pc[0x1dd];
    if (c < 0x10) {
        int n = c + 1;
        pc[0x1dd] = n;
        func_0201e374(-n);
        func_0201e3cc(-*(int *)(heap + 0x1774));
    } else {
        func_02020a78(6, 0);
        return -2;
    }
    func_ov003_0204ef68(heap);
    return 0;
}
