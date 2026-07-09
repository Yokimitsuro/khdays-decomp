extern void *NNSi_FndGetCurrentRootHeap(void);
extern void *data_ov008_02090f14;
extern void func_ov008_02055dbc(void);

void (*func_ov008_02055d98(void))(void)
{
    data_ov008_02090f14 = NNSi_FndGetCurrentRootHeap();
    return func_ov008_02055dbc;
}
