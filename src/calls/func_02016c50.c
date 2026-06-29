extern void func_02016978(void *ptr, int index, int arg);

void func_02016c50(unsigned char *ptr, int arg) {
    unsigned int index;

    for (index = 0; index < ptr[0x18]; index++) {
        func_02016978(ptr, index, arg);
    }
}
