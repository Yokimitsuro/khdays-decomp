extern int func_01fffca8();
extern int *func_0203d15c();
extern int data_02042ad8;
int func_0203c5c0(int param_1, unsigned int param_2, unsigned int param_3,
                  int param_4, int param_5, int *param_6)
{
    int *e = (int *)func_01fffca8(param_1, 0x28, param_2);
    int id;
    *e = param_1;
    e[1] = (int)func_0203d15c(param_3);
    e[5] = param_4;
    e[6] = param_5;
    e[9] = 0;
    id = data_02042ad8;
    data_02042ad8 = id + 1;
    e[7] = id;
    if (param_6 != 0)
        *param_6 = e[1];
    return e[7];
}
