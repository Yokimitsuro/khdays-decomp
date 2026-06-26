struct Elem {
    char pad[0x84];
    int a;
    int b;
};

void func_020326f0(char *base, int i, int va, int vb) {
    if (i < 0) return;
    {
        struct Elem *e = (struct Elem *)(base + 4 + i * 0x8c);
        e->a = va;
        e->b = vb;
    }
}
