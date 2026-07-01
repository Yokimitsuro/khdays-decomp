void func_ov008_02055a1c(int unused, char *obj, unsigned val) {
    *(unsigned *)(obj + 0x20) = (*(unsigned *)(obj + 0x20) & ~1u) | (val & 1);
}
