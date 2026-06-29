extern int func_020241b0(void *ptr, unsigned short arg1, unsigned short arg2);
extern void (*data_02041e2c[])(int value, int arg1, int arg2);
extern char data_02041dfc;

void func_0202489c(int index, unsigned short *args, int arg1, int arg2) {
    int value = func_020241b0(&data_02041dfc, args[0], args[1]);

    data_02041e2c[index](value, arg1, arg2);
}
