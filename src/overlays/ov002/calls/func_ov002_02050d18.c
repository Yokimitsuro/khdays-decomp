extern int func_ov002_02050d38();

int func_ov002_02050d18(int arg0, int arg1) {
    *(int *)(arg0 + 0x2c) = arg1;
    func_ov002_02050d38(arg0, 0);
    return 1;
}
