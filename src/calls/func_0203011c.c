typedef void (*func_0203011c_cb)(void *ptr, int zero, int arg1, int arg2, int arg3, int arg4);

void func_0203011c(int *ptr, int arg1, int arg2, int arg3, int arg4) {
    char *inner = (char *)ptr[6];
    func_0203011c_cb cb = *(func_0203011c_cb *)(*(int *)(inner + 0x1c) + 8);

    cb(inner + 8, 0, arg1, arg2, arg3, arg4);
}
