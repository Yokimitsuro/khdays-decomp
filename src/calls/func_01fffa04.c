extern int func_01fff99c();
extern void func_01fffa60();
extern int data_0204c22c;
void func_01fffa04(int param_1)
{
    int v;
    if (data_0204c22c == 0)
        return;
    if (*(unsigned short *)(param_1 + 2) != 0)
        return;
    if (*(unsigned short **)(param_1 + 0xc) == 0)
        return;
    v = func_01fff99c(((unsigned int)**(unsigned short **)(param_1 + 0xc) << 0x1a) >> 0x1b);
    func_01fffa60(*(int *)(param_1 + 0xc), (unsigned int)*(unsigned short *)(param_1 + 0x10), v, 1);
}
