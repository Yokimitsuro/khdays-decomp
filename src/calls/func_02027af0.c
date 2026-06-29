typedef void (*func_02027af0_cb)(void *ptr);

void func_02027af0(int *ptr) {
    if (ptr[4] != 0) {
        ((func_02027af0_cb)ptr[4])(ptr);
    }

    ptr[2] |= 0x20;
}
