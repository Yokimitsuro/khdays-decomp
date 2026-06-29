extern int func_020135e8(void *ptr, unsigned int value);

int func_020136d4(void *ptr, unsigned int value) {
    unsigned char *node = *(unsigned char **)(*(unsigned char **)ptr + 0x10);

    while (node != 0) {
        if (*(unsigned short *)node <= value && value <= *(unsigned short *)(node + 2)) {
            return func_020135e8(node, value);
        }
        node = *(unsigned char **)(node + 8);
    }

    return 0xffff;
}
