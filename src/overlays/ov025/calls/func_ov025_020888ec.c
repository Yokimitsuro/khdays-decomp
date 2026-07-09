extern void func_020326a8();

void func_ov025_020888ec(int arg0, int arg1) {
    int i = 0;
    do {
        int v = ((int *)arg1)[i + 5];
        if (v != -1) func_020326a8(arg0, v);
        i++;
    } while (i < 2);
}
