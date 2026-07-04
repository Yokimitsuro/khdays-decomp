extern void func_0202926c();
extern char data_02042928[];

int func_02029344(int this_, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6) {
    func_0202926c(this_, arg1, arg2, arg3);
    *(unsigned char *)(this_ + 0x21) = 3;
    *(char **)(this_ + 0x1c) = data_02042928;
    *(int *)(this_ + 0x38) = arg3;
    *(int *)(this_ + 0x3c) = arg4;
    *(int *)(this_ + 0x40) = arg5;
    *(int *)(this_ + 0x44) = arg6;
    return 1;
}
