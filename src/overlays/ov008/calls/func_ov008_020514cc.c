extern int data_ov008_02090f0c[];
extern char data_ov008_02090064[];

void func_ov008_020514cc(int arg0)
{
    int index = data_ov008_02090f0c[1];

    if (index != -1) {
        ((void (*)(int))*(int *)(*(char **)(data_ov008_02090064 + index * 8) + 8))(arg0);
    }
}
