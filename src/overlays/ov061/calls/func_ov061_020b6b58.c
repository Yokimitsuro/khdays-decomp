extern void func_ov061_020b683c();

void func_ov061_020b6b58(int this_, int *arg1) {
    int s = *arg1;
    if (s != 0 && s != 2) return;
    if (s == 0) {
        func_ov061_020b683c(this_);
    }
    *arg1 = 1;
}
