extern int data_ov002_0207fa14;
extern int func_01fffde0(int arg0);
extern int func_ov022_020acbf0(int arg0);

int func_ov002_02074440(int arg0) {
    if (*(signed char *)(*(int *)&data_ov002_0207fa14 + 0x96) >= 0) {
        return 0;
    }
    return func_ov022_020acbf0(func_01fffde0(arg0));
}
