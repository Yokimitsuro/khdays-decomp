typedef void (*func_0202fb58_cb)(void *ptr, int word0, int arg1, int arg2, int arg3, int arg4);

void func_0202fb58(int *ptr, int arg1, int arg2, int arg3, int arg4) {
    func_0202fb58_cb cb = **(func_0202fb58_cb **)(ptr + 6);

    cb(ptr + 1, ptr[0], arg1, arg2, arg3, arg4);
}
