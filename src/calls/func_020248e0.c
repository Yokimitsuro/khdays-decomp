extern int func_020241b0(void *ptr, unsigned short arg1, unsigned short arg2);
extern void (*data_02041eac[])(int value, int arg1, int arg2);
extern char data_02041de4;

void func_020248e0(int index, unsigned short *args, int arg1, int arg2) {
    int value = func_020241b0(&data_02041de4, args[0], args[1]);

    data_02041eac[index](value, arg1, arg2);
}
