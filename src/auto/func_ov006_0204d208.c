struct A {
    char pad[0x40];
    void (*fn)(void *);
};

void func_ov006_0204d208(struct A *a, void *b, int c) {
    if (c != 0 && a->fn != 0) {
        a->fn(b);
    }
    *(int *)((char *)b + 0x14) = 0;
}
