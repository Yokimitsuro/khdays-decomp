extern int func_ov008_0205b670(int index);
extern int func_ov008_0205b650(int node);
extern void func_ov008_0206ff24(int obj, int slot, int node);

void func_ov008_0207126c(int param_1) {
    int node;
    int i;
    int base;
    if (*(int *)(param_1 + 0x68) != 0) {
        return;
    }
    base = *(int *)(param_1 + 0xc) / 32;
    node = func_ov008_0205b670(base);
    i = 0;
    do {
        if (node == 0) {
            break;
        }
        if (*(int *)(param_1 + 0x7c) != 0 && base + i > (int)*(unsigned short *)(param_1 + 0x6e)) {
            break;
        }
        func_ov008_0206ff24(param_1, i, node);
        node = func_ov008_0205b650(node);
        i++;
    } while (i < 6);
    *(int *)(param_1 + 0x48) = 1;
}
