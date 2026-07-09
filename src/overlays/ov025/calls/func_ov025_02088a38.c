extern void func_0203281c();

void func_ov025_02088a38(int arg0, int arg1, unsigned int arg2) {
    int i = 0;
    do {
        int v = ((int *)arg1)[i + 5];
        if (v != -1) func_0203281c(arg0, v, arg2);
        i++;
    } while (i < 2);
}
