extern int func_ov002_02079770();

void func_ov002_02079974(int arg0, int arg1) {
    if (*(unsigned char *)arg1 != 1) {
        return;
    }
    *(unsigned char *)(arg0 + 0x1c2) = *(unsigned char *)(arg1 + 4) == 3;
    func_ov002_02079770(arg0, *(unsigned char *)(arg1 + 4));
}
