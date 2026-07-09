extern int data_ov025_020b574c;
extern int data_ov025_020b4ab0;

int func_ov025_02085890(void) {
    return *(int *)(*(int *)((char *)&data_ov025_020b4ab0 + *(int *)&data_ov025_020b574c * 8) + 0x10);
}
