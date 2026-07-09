void func_ov025_020b0888(int arg0) {
    int n = *(int *)(arg0 + 8);
    *(int *)(arg0 + 0xc) = n + *(int *)(n + 8);
}
