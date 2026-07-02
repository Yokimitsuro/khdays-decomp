int func_ov008_0205db98(char *base, int index) {
    int *arr = (int *)(base + 0x1ba4);
    return (arr[index / 32] & (1 << (index % 32))) != 0;
}
