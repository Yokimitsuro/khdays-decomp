extern int data_02042418[];

void func_02011134(int param_1) {
    int i = 0;
    int j = 0;
    int *dst = data_02042418;
    do {
        dst[0] = ((int *)param_1)[j];
        i++;
        dst[1] = ((int *)param_1)[j + 1];
        j += 2;
        dst += 6;
    } while (i < 5);
}
