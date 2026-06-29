extern void *func_0202c0a4(int index);

void *func_0202c37c(unsigned char *ptr, int index) {
    if (*(unsigned char **)(ptr + 4) == ptr + 0x10) {
        if (index == 0xff) {
            return 0;
        }
        return func_0202c0a4(index);
    }

    ptr = *(unsigned char **)ptr;
    if (index == 0xff) {
        return 0;
    }

    return *(unsigned char **)(ptr + 0xac) + index * 0x14;
}
