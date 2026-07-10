extern int data_0204c230;

void func_01fffbf4(int p) {
    int a, v;
    if (*(int *)&data_0204c230 == 0) return;
    a = *(int *)(p + 0x20);
    v = *(int *)(p + 0x14);
    if (*(int *)(a + 4) == v) *(int *)a = 0;
}
