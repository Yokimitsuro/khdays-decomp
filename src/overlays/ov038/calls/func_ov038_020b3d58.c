extern int func_0202a818(void *p, void *b);

void func_ov038_020b3d58(int unused, char *a, void *b) {
    if (*(int *)(a + 0xc) != 1) return;
    if (func_0202a818(a + 0x10, b) != 0) {
        *(int *)(a + 0xc) = 0;
    }
}
