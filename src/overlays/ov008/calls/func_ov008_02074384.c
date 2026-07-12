/* Twin of func_ov008_0206fbc4 for the 0xe-entry table at param_1+0x174. */
extern int func_0201ef9c(void *pool, int count);
extern int data_ov008_02090920;

void func_ov008_02074384(int param_1) {
    int i;
    if (*(int *)(param_1 + 0x174) != 0) return;
    *(int *)(param_1 + 0x174) = func_0201ef9c(&data_ov008_02090920, 0xe);
    for (i = 0; i < *(unsigned char *)(*(int *)(param_1 + 0x174)); i++) {
        int base = *(int *)(param_1 + 0x174);
        ((int *)base)[i + 1] += base;
    }
}
