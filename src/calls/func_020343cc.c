extern int func_02035070(void *ptr);
extern int func_02035028(void *ptr);

int func_020343cc(int **ptr) {
    unsigned short kind = *(unsigned short *)((char *)ptr[0] + 2);

    if (kind < 0x21) {
        if (kind == 0x16) {
            return func_02035070(ptr);
        }

        return func_02035028(ptr);
    }

    return 0;
}
