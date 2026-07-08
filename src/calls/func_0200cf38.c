extern int func_0200cd40();
int func_0200cf38(int param_1, int param_2, int param_3, int param_4)
{
    unsigned int v = 0;
    if (param_1 == 0) {
        if (param_2 == 1) v = 6;
        if (param_2 == 0) v = 7;
    } else if (param_1 == 1) {
        if (param_2 == 1) v = 4;
        if (param_2 == 0) v = 5;
    } else if (param_1 == 2) {
        if (param_2 == 1) v = 8;
        if (param_2 == 0) v = 9;
    }
    if (v == 0)
        return 0xffff;
    return func_0200cd40(v, param_3, param_4);
}
