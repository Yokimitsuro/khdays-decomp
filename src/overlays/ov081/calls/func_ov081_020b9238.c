extern void func_ov081_020b8f1c();

void func_ov081_020b9238(int this_, int *arg1) {
    int s = *arg1;
    if (s != 0 && s != 2) return;
    if (s == 0) {
        func_ov081_020b8f1c(this_);
    }
    *arg1 = 1;
}
