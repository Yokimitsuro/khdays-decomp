extern int data_0204c208;

void func_0202b5f8(int arg0, int *arg1) {
    int base = data_0204c208;
    int head = *(int *)(base + arg0 * 4 + 0xa4);
    if (head != 0) {
        *arg1 = head;
        *(int **)(head + 4) = arg1;
    }
    *(int **)(base + arg0 * 4 + 0xa4) = arg1;
    *(char *)((int)arg1 + 10) = (char)arg0;
}
