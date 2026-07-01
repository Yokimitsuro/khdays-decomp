extern void func_ov107_020c2b20(void *b, int v);
extern void func_ov107_020c7b70(void *a, void *b);

void func_ov152_020d3df0(char *a, void *b) {
    int i;
    for (i = 0; i < 3; i++) {
        int *base = *(int **)(a + 0x3c8);
        func_ov107_020c2b20(b, base[i]);
    }
    func_ov107_020c7b70(a, b);
}
