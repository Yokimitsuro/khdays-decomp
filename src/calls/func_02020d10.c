extern unsigned short func_02030788();

int func_02020d10(int arg0, int arg1) {
    int r = arg1;
    if (arg1 == -1) r = **(int **)(arg0 + 0x128);
    if (arg1 <= -3) {
        int t = (unsigned short)func_02030788();
        r = t + (-3 - arg1);
        if (r >= 4) r -= 4;
    }
    return r;
}
