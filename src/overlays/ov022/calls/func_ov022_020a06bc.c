extern void func_ov022_0209c9fc(int obj);

struct Bits020a06bc { unsigned char b0 : 1; unsigned char b1 : 1; unsigned char b2 : 1; };

void func_ov022_020a06bc(int obj) {
    if ((*(unsigned long long *)obj & 0x200LL) != 0) return;
    if (((struct Bits020a06bc *)(obj + 0x694))->b2 &&
        ((struct Bits020a06bc *)(obj + 0x694))->b0)
        func_ov022_0209c9fc(obj);
    *(unsigned char *)(obj + 0x694) &= ~4;
}
