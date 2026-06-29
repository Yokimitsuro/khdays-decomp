extern void func_0202b5f8(void *arg, void *ptr);

void func_0202c5b8(unsigned char *ptr, void *arg) {
    unsigned char flags = ptr[8];

    if ((flags & 2) == 0) {
        ptr[8] = flags | 0xa;
        func_0202b5f8(arg, ptr);
    }
}
