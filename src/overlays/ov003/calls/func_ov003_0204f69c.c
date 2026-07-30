typedef struct {
    unsigned char pad0000[0x1774];
    int nFadeTicks;
    unsigned char pad1778[0x698];
    int nInitGuard;
    int nInitValue;
} Ov003RootContext;

extern Ov003RootContext *NNSi_FndGetCurrentRootHeap(void);
extern int func_ov105_020bd7c4(void);
extern void func_ov003_0204e91c(int a);
extern void func_0201e374(int a);
extern void func_0201e3cc(int a);
extern void func_02020a78(int a, int b);
extern void func_ov003_0204ef68(int a);

int func_ov003_0204f69c(void) {
    Ov003RootContext *root = NNSi_FndGetCurrentRootHeap();

    if (root->nInitGuard == 0) {
        root->nInitValue = func_ov105_020bd7c4();
    }
    func_ov003_0204e91c((int)root);

    if (root->nFadeTicks < 0x10) {
        int n = root->nFadeTicks + 1;

        root->nFadeTicks = n;
        func_0201e374(-n);
        func_0201e3cc(-root->nFadeTicks);
    } else {
        func_02020a78(6, 0);
        return -2;
    }
    func_ov003_0204ef68((int)root);
    return 0;
}
