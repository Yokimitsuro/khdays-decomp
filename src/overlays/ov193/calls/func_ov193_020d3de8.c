extern void func_ov107_020c2b20(void *b, int v);
extern void func_ov107_020c7b70(void *a, void *b);

void func_ov193_020d3de8(char *a, void *b) {
    int i;
    for (i = 0; i < 4; i++) {
        int *base = *(int **)(a + 0x3a4);
        func_ov107_020c2b20(b, base[i]);
    }
    func_ov107_020c7b70(a, b);
}
