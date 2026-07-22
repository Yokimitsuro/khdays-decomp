/* Tears the block held by data_0204c234 down: runs func_02019c20 once, then func_0201a070
 * over the sixteen 0x20-byte entries at +0xb4500 and over the two singles at +0xb44c8 and
 * +0xb44c4, and finally drops the pointer.  Returns 1 (also when nothing was allocated).
 *
 * `i` has to be declared between the two pointers to reproduce the ROM's r4/r5. */
extern char *data_0204c234;
extern void func_02019c20(void);
extern void func_0201a070(void *p);

int func_02032f0c(void) {
    char *base;
    int i;
    char *p;
    base = data_0204c234;
    if (base == 0) {
        return 1;
    }
    func_02019c20();
    i = 0;
    p = base + 0xb4500;
    do {
        func_0201a070(p);
        i = i + 1;
        p = p + 0x20;
    } while (i < 0x10);
    func_0201a070(base + 0xb44c8);
    func_0201a070(base + 0xb44c4);
    data_0204c234 = 0;
    return 1;
}
