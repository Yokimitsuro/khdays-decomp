extern int data_ov003_0204f9a0;

void func_ov003_0204e4b8(int arg0, int arg1) {
    int idx = arg0 * 0x108;
    *(int *)(data_ov003_0204f9a0 + 0x2b8 + idx) += arg1;
    *(int *)(data_ov003_0204f9a0 + 0x2f8 + 0x800 + idx) += arg1;
    *(int *)(data_ov003_0204f9a0 + 0x318 + 0xc00 + idx) += arg1;
}
