extern void func_ov107_020c2b20(int obj, int arg1);
extern void func_ov107_020c7b70(int obj, int arg1);

void func_ov283_020cc2bc(int *list, int target) {
    int i;
    for (i = 0; i < 2; i++)
        func_ov107_020c2b20(target, list[i + 0xe7]);
    for (i = 0; i < 16; i++)
        func_ov107_020c2b20(target, list[i + 0xe9]);
    func_ov107_020c7b70((int)list, target);
}
