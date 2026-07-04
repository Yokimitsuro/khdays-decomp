extern int func_0200d674(int a, void *b, int c);
extern void func_0200dce0(void);
extern void func_0200dcf0(void);
extern int data_02046438[];

int func_0200d6e8(int param_1) {
    int r = func_0200d674(param_1, func_0200dce0, 0);
    data_02046438[0xb] = r;
    if (r == 0) func_0200dcf0();
    return data_02046438[0xb];
}
