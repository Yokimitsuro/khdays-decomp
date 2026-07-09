extern void func_ov107_020c2b20();
extern void func_ov107_020c7b70();

void func_ov299_020d3960(int arg0, int arg1) {
    int i;
    for (i = 0; i < 3; i++)
        func_ov107_020c2b20(arg1, ((int *)arg0)[i + 225]);
    func_ov107_020c7b70(arg0, arg1);
}
