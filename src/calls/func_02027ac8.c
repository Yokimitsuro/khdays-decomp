typedef void (*func_02027ac8_cb)(void *ptr);

void func_02027ac8(int *ptr) {
    if (ptr[3] != 0) {
        ((func_02027ac8_cb)ptr[3])(ptr);
    }

    ptr[0]++;
}
