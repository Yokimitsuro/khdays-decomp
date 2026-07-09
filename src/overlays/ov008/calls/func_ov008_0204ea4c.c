extern void NNSi_FndGetCurrentRootHeap(void);
extern void func_02023930(void *, int);
extern void func_ov008_0204d564(void);
extern void func_ov008_0204ea88(void);
extern char data_ov008_02090dc4;
void *func_ov008_0204ea4c(void)
{
    NNSi_FndGetCurrentRootHeap();
    func_02023930(&data_ov008_02090dc4, 0);
    func_ov008_0204d564();
    return func_ov008_0204ea88;
}
