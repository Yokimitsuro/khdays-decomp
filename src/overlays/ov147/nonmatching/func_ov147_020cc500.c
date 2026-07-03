extern void func_ov107_020c2b20(void *b, int v);
extern void func_ov107_020c7b70(void *a, void *b);

void func_ov147_020cc500(char *a, void *b) {
    int i;
    for (i = 0; i < 3; i++) {
        func_ov107_020c2b20(b, *(int *)(a + i * 4 + 0x398));
    }
    func_ov107_020c7b70(a, b);
}
