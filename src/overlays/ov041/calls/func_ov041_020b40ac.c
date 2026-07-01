extern int func_0202a818(void *p, void *b);

void func_ov041_020b40ac(int unused, char *a, void *b) {
    if (*(int *)(a + 0x0) != 2) return;
    if (func_0202a818(a + 0x4, b) != 0) {
        *(int *)(a + 0x0) = 0;
    }
}
