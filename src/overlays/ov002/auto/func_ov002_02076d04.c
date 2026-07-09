int func_ov002_02076d04(int arg0) {
    int (*f)(int) = *(int (**)(int))(*(int *)(arg0 + 8) + 0x34);
    if (f == 0) {
        return 0;
    }
    return f(arg0);
}
