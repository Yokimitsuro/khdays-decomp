extern int data_ov025_020b5740;

void func_ov025_02082b84(void) {
    int p = *(int *)&data_ov025_020b5740;
    *(int *)p = *(int *)p & ~1 | 2;
}
