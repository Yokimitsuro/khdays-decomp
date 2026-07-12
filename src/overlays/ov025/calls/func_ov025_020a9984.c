/* Twin of func_ov008_0206fbc4 for the 0xe-entry table at param_1+0x174. */
extern int func_0201ef9c(void *pool, int count);
extern int data_ov025_020b5404;

void func_ov025_020a9984(int param_1) {
    int i;
    if (*(int *)(param_1 + 0x174) != 0) return;
    *(int *)(param_1 + 0x174) = func_0201ef9c(&data_ov025_020b5404, 0xe);
    for (i = 0; i < *(unsigned char *)(*(int *)(param_1 + 0x174)); i++) {
        int base = *(int *)(param_1 + 0x174);
        ((int *)base)[i + 1] += base;
    }
}
