extern int *func_02012844(void *ptr);

void func_0201285c(void *ptr, int value1, int value2) {
    int *out = func_02012844(ptr);

    out[9] = -1;
    out[10] = value1;
    out[11] = value2;
}
