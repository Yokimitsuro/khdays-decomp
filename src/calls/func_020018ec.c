extern int data_0204430c;

int func_020018ec(void) {
    int v = *(int *)((char *)&data_0204430c + 0x20) + 1;
    *(int *)((char *)&data_0204430c + 0x20) = v;
    return v;
}
