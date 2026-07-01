extern void func_ov180_020d6268(int v);

void func_ov180_020d5fc0(char *p) {
    if (*(int *)(p + 0x50) != 1) return;
    func_ov180_020d6268(*(int *)(p + 0x214));
}
