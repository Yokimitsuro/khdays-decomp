extern void *func_02012b6c(void *ptr, int arg);
extern int func_0201292c(void *ptr, int arg2, int arg3);
extern int func_02012a5c(void *ptr, int arg2, int arg3);

int func_02012de4(void *ptr, int arg1, int arg2, int arg3) {
    if (arg1 != 0) {
        return func_0201292c(func_02012b6c(ptr, arg1), arg2, arg3);
    }

    return func_02012a5c(ptr, arg2, arg3);
}
