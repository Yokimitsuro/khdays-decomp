extern int func_0202da08(void *ptr, void *out, int arg);
extern void func_0202b450(void *ptr, void *src);

void func_0202de3c(int *ptr, int arg) {
    int out[3];

    if (func_0202da08(ptr, out, arg)) {
        func_0202b450((void *)ptr[0], out);
    }
}
