extern void func_020124d8(int, int);

void func_02032680(int param_1, int param_2, int param_3) {
    char *elem = (char *)(param_1 + 4) + param_2 * 0x8c;
    if (param_2 < 0) {
        return;
    }
    func_020124d8((int)(elem + 0x14), param_3);
}
