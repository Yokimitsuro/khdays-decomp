extern int func_0202ba18(void *entry);
extern char *data_0204c208;

int func_0202b9f4(int idx) {
    char *base = data_0204c208 + 0xc4;
    return func_0202ba18((void *)(0x184 * idx + (int)base));
}
