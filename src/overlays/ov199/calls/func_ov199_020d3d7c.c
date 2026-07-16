extern void func_ov107_020c2b20();
extern void func_ov107_020c7b70();

void func_ov199_020d3d7c(int arg0, int arg1) {
    int i;
    for (i = 0; i < 3; i++)
        func_ov107_020c2b20(arg1, ((int *)arg0)[i + 230]);
    func_ov107_020c7b70(arg0, arg1);
}
