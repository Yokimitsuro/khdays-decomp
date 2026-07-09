extern int data_0204bda0;

int func_02020904(void) {
    int v = *(short *)&data_0204bda0 + 1;
    *(short *)&data_0204bda0 = v;
    return v;
}
