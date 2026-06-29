extern int data_02042978;
extern int data_0204297c;
extern int func_02023930(void *ptr, int value);

void func_020305d8(void) {
    if (data_02042978 == -1) {
        data_02042978 = func_02023930(&data_0204297c, 0);
    }
}
