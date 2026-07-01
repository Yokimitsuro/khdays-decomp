extern void func_ov022_02089584(void *p);

void func_ov072_020b855c(char *base) {
    void *p = *(void **)(base + 0x2c2c);
    if (p == 0) return;
    func_ov022_02089584(p);
}
