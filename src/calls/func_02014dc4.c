extern int func_02014d50(void *ptr, int arg);

void func_02014dc4(int *ptr, int arg) {
    if (func_02014d50(ptr + 2, arg) != 0 ||
        func_02014d50(ptr + 4, arg) != 0 ||
        func_02014d50(ptr + 6, arg) != 0) {
        ptr[0] |= 0x10;
    }
}
