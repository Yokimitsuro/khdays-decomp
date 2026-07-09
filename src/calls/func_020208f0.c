extern int data_0204bda0;

int func_020208f0(void) {
    int v = *(short *)&data_0204bda0;
    if (v > 0) {
        v -= 1;
        *(short *)&data_0204bda0 = v;
    }
    return v;
}
