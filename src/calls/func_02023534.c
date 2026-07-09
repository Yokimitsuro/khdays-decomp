extern int data_0204be08;

int func_02023534(void) {
    int p = *(int *)((char *)&data_0204be08 + 4);
    if (p == 0) return 0;
    return *(int *)(p + 0xdc);
}
