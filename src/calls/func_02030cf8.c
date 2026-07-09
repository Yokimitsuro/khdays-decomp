extern int data_0204c22c;

void func_02030cf8(int index, int value) {
    int base = *(int *)&data_0204c22c;
    *(int *)(base + index * 4 + 0xc) = value;
}
