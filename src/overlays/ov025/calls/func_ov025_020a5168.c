/* Lazily allocate the 0xe-entry table at param_1+0x58, then relocate each entry's
 * stored offset at +4 to an absolute pointer by adding the table base. */
extern int func_0201ef9c(void *pool, int count);
extern int data_ov025_020b5350;

void func_ov025_020a5168(int param_1) {
    int i;
    if (*(int *)(param_1 + 0x58) != 0) return;
    *(int *)(param_1 + 0x58) = func_0201ef9c(&data_ov025_020b5350, 0xe);
    for (i = 0; i < *(unsigned char *)(*(int *)(param_1 + 0x58)); i++) {
        int base = *(int *)(param_1 + 0x58);
        ((int *)base)[i + 1] += base;
    }
}
