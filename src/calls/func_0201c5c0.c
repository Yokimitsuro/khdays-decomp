extern unsigned char *func_0201b3e8(int arg);
extern int func_0201c734(void *ptr, unsigned char arg1, unsigned short arg2, unsigned char arg3, void *arg4, int arg5);

int func_0201c5c0(void *ptr, int arg) {
    unsigned char *entry = func_0201b3e8(arg);

    if (entry == 0) {
        return 0;
    }

    return func_0201c734(ptr, entry[9], *(unsigned short *)(entry + 4), entry[8], entry, arg);
}
