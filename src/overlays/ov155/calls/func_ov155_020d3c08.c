extern void func_ov107_020c2b20(void *a, int v);
extern void func_ov107_020c7b70(void *a, void *b);

void func_ov155_020d3c08(char *a, void *b) {
    func_ov107_020c2b20(b, *(int *)(a + 0x398));
    func_ov107_020c7b70(a, b);
}
