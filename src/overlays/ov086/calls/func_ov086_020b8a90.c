extern int func_0202a818(void *p, void *b);

void func_ov086_020b8a90(int unused, char *a, void *b) {
    if (*(int *)(a + 0x11c) != 1) return;
    if (func_0202a818(a + 0x120, b) != 0) {
        *(int *)(a + 0x11c) = 0;
    }
}
