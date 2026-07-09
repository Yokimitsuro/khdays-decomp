extern int *NNSi_FndGetCurrentRootHeap(void);
extern int func_02023930(void *data, int arg1);
extern void func_ov008_0204d564(void);
extern void func_ov008_0204eb88(void);
extern int data_ov008_02090db0[];

void (*func_ov008_0204eaac(void))(void)
{
    int *state = NNSi_FndGetCurrentRootHeap();

    state[5] = func_02023930(data_ov008_02090db0, 0);
    func_ov008_0204d564();
    return func_ov008_0204eb88;
}
