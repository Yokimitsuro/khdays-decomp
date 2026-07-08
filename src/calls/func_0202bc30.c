extern void func_0202af3c();
extern void func_0202b3b0();
extern void func_0202b628();
extern void func_0202b684();
void func_0202bc30(int *param_1)
{
    if ((*(unsigned char *)(param_1 + 2) & 2) == 0)
        return;
    if ((*(unsigned char *)(param_1 + 2) & 4) != 0)
        func_0202af3c((int)(param_1 + 4), 0, 0);
    func_0202b3b0((unsigned int *)(param_1 + 3));
    if ((*(unsigned char *)(param_1 + 2) & 0x20) != 0)
        func_0202b628(param_1);
    else
        func_0202b684(param_1);
    *(unsigned char *)(param_1 + 2) &= ~2;
}
