extern void func_ov042_020b403c();

void func_ov042_020b4358(int this_, int *arg1) {
    int s = *arg1;
    if (s != 0 && s != 2) return;
    if (s == 0) {
        func_ov042_020b403c(this_);
    }
    *arg1 = 1;
}
