extern void func_01ff9f00();
void func_01ffa13c(unsigned int *param_1)
{
    unsigned int f = *param_1;
    if ((f & 4) == 0) {
        if ((f & 2) == 0)
            func_01ff9f00(0x19, param_1 + 10, 0xc);
        else
            func_01ff9f00(0x1c, param_1 + 0x13, 3);
    } else if ((f & 2) == 0) {
        func_01ff9f00(0x1a, param_1 + 10, 9);
    }
    if ((*param_1 & 1) != 0)
        return;
    func_01ff9f00(0x1b, param_1 + 1, 3);
}
