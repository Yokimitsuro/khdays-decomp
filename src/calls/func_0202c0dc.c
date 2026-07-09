extern int func_0202bfa0();
extern unsigned char *func_02028df0();
void func_0202c0dc(int param_1, unsigned char *param_2, int *param_3)
{
    int t = func_0202bfa0(param_1);
    int i = 0;
    if ((int)*(unsigned short *)(t + 2) <= 0)
        return;
    while (1) {
        int e = ((int *)*(int *)(t + 4))[i];
        if (e != 0) {
            unsigned char *found = func_02028df0(e, param_2);
            if (found != 0) {
                *(int *)(found + 0xc) = *param_3;
                return;
            }
        }
        i++;
        if ((int)(unsigned int)*(unsigned short *)(t + 2) <= i)
            return;
    }
}
