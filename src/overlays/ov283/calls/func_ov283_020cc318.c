extern void func_ov107_020c2b38(int obj, int arg1);
extern void func_ov107_020c7c1c(int obj, int arg1);

void func_ov283_020cc318(int *list, int target) {
    int i;
    for (i = 0; i < 2; i++)
        func_ov107_020c2b38(target, list[i + 0xe7]);
    for (i = 0; i < 16; i++)
        func_ov107_020c2b38(target, list[i + 0xe9]);
    func_ov107_020c7c1c((int)list, target);
}
