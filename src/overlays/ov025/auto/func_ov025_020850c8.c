extern int data_ov025_020b574c;

void func_ov025_020850c8(void) {
    if (data_ov025_020b574c != -1) {
        data_ov025_020b574c = -1;
    }
    if (*(int *)((char *)&data_ov025_020b574c + 4) != -1) {
        *(int *)((char *)&data_ov025_020b574c + 4) = -1;
    }
}
