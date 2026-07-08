extern void func_0203d194();
void func_01fffc5c(int *param_1)
{
    int *puVar1 = (int *)param_1[4];
    int *puVar2;
    if (puVar1 == param_1)
        return;
    do {
        puVar2 = (int *)*puVar1;
        puVar2[1] = puVar1[1];
        *(int *)puVar1[1] = *puVar1;
        func_0203d194((int)puVar1);
        param_1[8] = param_1[8] - 1;
        puVar1 = puVar2;
    } while (puVar2 != param_1);
}
