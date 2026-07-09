int func_ov022_0208a96c(int arg0) {
    int base = *(int *)(arg0 + 0x58);
    switch (*(int *)(arg0 + 0x14)) {
    case 0x17:
        return base + 0x2688;
    case 0x18:
        return base + 0x2694;
    case 0x19:
        return base + 0x26a0;
    }
    return arg0;
}
