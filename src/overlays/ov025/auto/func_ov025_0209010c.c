int func_ov025_0209010c(char *base, int index) {
    int *arr = (int *)(base + 0x1ba4);
    return (arr[index / 32] & (1 << (index % 32))) != 0;
}
