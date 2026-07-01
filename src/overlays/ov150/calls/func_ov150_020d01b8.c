extern void func_ov107_020c2b38(void *a, int v);
extern void func_ov107_020c7c1c(void *a, void *b);

void func_ov150_020d01b8(char *a, void *b) {
    func_ov107_020c2b38(b, *(int *)(a + 0x3c8));
    func_ov107_020c7c1c(a, b);
}
