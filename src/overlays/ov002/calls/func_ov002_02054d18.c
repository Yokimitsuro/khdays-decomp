extern void *NNSi_FndGetCurrentRootHeap(void);
extern void *data_ov002_0207f610;
extern void func_ov002_02054d3c(void);

void (*func_ov002_02054d18(void))(void)
{
    data_ov002_0207f610 = NNSi_FndGetCurrentRootHeap();
    return func_ov002_02054d3c;
}
