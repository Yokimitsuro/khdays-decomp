extern void func_0202926c();
extern char data_02042940[];

int func_020292a4(int this_, int arg1, int arg2, int arg3, int arg4) {
    func_0202926c(this_, arg1, arg2, arg3);
    *(unsigned char *)(this_ + 0x21) = 1;
    *(char **)(this_ + 0x1c) = data_02042940;
    *(int *)(this_ + 0x38) = arg3;
    *(int *)(this_ + 0x3c) = arg4;
    return 1;
}
