extern int data_ov011_0205e960;

int func_ov011_0205dc4c(void) {
    int *p = *(int **)((char *)&data_ov011_0205e960 + 4);
    int r = 1;
    if (p != 0 && *(int *)((char *)p + 4) != 5) r = 0;
    return r != 0;
}
