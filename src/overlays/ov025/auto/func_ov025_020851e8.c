extern int data_ov025_020b574c;

int func_ov025_020851e8(void) {
    if (*(int *)((char *)&data_ov025_020b574c + 4) != -1) {
        *(int *)((char *)&data_ov025_020b574c + 4) = -1;
    }
    return 1;
}
