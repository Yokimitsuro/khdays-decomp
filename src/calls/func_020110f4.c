extern int data_02042418[];

void func_020110f4(int param_1) {
    int i = 0;
    int *src = data_02042418;
    int j = 0;
    do {
        i++;
        ((int *)param_1)[j] = src[0];
        ((int *)param_1)[j + 1] = src[1];
        src += 6;
        j += 2;
    } while (i < 5);
}
