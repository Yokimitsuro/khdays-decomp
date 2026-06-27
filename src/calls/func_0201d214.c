extern void func_0201aa18(void *);

void func_0201d214(void *obj) {
    int n = *(int *)((char *)obj + 0x120);
    if (n == 0) return;
    n -= 1;
    *(int *)((char *)obj + 0x120) = n;
    if (n != 0) return;
    func_0201aa18(obj);
}
