extern int func_ov025_0208dbdc(int index);
extern int func_ov025_0208dbbc(int node);
extern void func_ov025_020a54c8(int obj, int slot, int node);

void func_ov025_020a6750(int param_1) {
    int node;
    int i;
    int base;
    if (*(int *)(param_1 + 0x68) != 0) {
        return;
    }
    base = *(int *)(param_1 + 0xc) / 32;
    node = func_ov025_0208dbdc(base);
    i = 0;
    do {
        if (node == 0) {
            break;
        }
        if (*(int *)(param_1 + 0x7c) != 0 && base + i > (int)*(unsigned short *)(param_1 + 0x6e)) {
            break;
        }
        func_ov025_020a54c8(param_1, i, node);
        node = func_ov025_0208dbbc(node);
        i++;
    } while (i < 6);
    *(int *)(param_1 + 0x48) = 1;
}
