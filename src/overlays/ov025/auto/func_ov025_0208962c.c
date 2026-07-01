void func_ov025_0208962c(int unused, char *obj, unsigned val) {
    *(unsigned *)(obj + 0x20) = (*(unsigned *)(obj + 0x20) & ~1u) | (val & 1);
}
