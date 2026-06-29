extern void func_0202b6e0(void *ptr);

void func_0202c5e4(unsigned char *ptr) {
    unsigned char flags = ptr[8];

    if (flags & 2) {
        ptr[8] = flags & ~0xa;
        func_0202b6e0(ptr);
    }
}
