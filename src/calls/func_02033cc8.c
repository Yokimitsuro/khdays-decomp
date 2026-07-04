extern int data_0204c234;
extern int func_0201a210();
extern int func_0201a0a8();

int func_02033cc8(void) {
    int r = func_0201a210(data_0204c234 + 0xb44c4);
    if (r < 0) goto ret0;
    if (func_0201a0a8(r) != 0) goto ret1;
ret0:
    return 0;
ret1:
    return 1;
}
