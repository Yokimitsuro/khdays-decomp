extern void func_ov107_020c2b38(void *a, int v);
extern void func_ov107_020c7c1c(void *a, void *b);

void func_ov160_020cc5a0(char *a, void *b) {
    func_ov107_020c2b38(b, *(int *)(a + 0x3a4));
    func_ov107_020c7c1c(a, b);
}
