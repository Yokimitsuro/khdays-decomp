extern void func_02010a94();
extern void func_02010af0();
void func_02010bcc(int param_1, int param_2, int param_3)
{
    unsigned int r;
    if (param_2 == 0)
        param_2 = 1;
    r = (param_2 + 3) & 0xfffffffc;
    if (param_3 >= 0)
        func_02010a94((void *)(param_1 + 0x24), r, param_3);
    else
        func_02010af0((void *)(param_1 + 0x24), r, -param_3);
}
