extern int *NNSi_FndGetCurrentRootHeap(void);
extern void func_02031240(void);

void (*func_02031228(int value))(void)
{
    *NNSi_FndGetCurrentRootHeap() = value;
    return func_02031240;
}
