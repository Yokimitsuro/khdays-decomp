extern void func_0202af3c();
extern void func_0202b4b8();
extern void func_0202b570();
void func_0202bba4(int *param_1, int *param_2, unsigned int *param_3)
{
    func_0202af3c((int)(param_1 + 4), (int)(param_2 + 4), param_3);
    *(unsigned char *)(param_1 + 2) |= 0xb;
    if ((*(unsigned char *)(param_2 + 2) & 0x20) != 0) {
        *(unsigned char *)(param_1 + 2) |= 0x20;
        func_0202b4b8((unsigned int)*(unsigned char *)((char *)param_2 + 10), param_1, param_2);
        return;
    }
    *(unsigned char *)(param_1 + 2) &= ~0x20;
    func_0202b570((unsigned int)*(unsigned char *)((char *)param_2 + 10), param_1, param_2);
}
