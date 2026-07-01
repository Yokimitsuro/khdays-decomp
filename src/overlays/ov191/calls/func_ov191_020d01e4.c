extern void func_ov107_020c2b38(void *b, int v);
extern void func_ov107_020c7c1c(void *a, void *b);

void func_ov191_020d01e4(char *a, void *b) {
    int i;
    for (i = 0; i < 4; i++) {
        int *base = *(int **)(a + 0x3a4);
        func_ov107_020c2b38(b, base[i]);
    }
    func_ov107_020c7c1c(a, b);
}
