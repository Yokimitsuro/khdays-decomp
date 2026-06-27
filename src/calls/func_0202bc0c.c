extern int func_0202bc30(void *entry);
extern char *data_0204c208;

int func_0202bc0c(int idx) {
    char *base = data_0204c208 + 0xc4;
    return func_0202bc30((void *)(0x184 * idx + (int)base));
}
