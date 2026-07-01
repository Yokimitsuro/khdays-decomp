extern void func_ov107_020c2b38(void *b, int v);
extern void func_ov107_020c7c1c(void *a, void *b);

void func_ov148_020d017c(char *a, void *b) {
    int i;
    for (i = 0; i < 3; i++) {
        func_ov107_020c2b38(b, *(int *)(a + i * 4 + 0x398));
    }
    func_ov107_020c7c1c(a, b);
}
