void func_ov026_020835e0(char *obj, void *arg) {
    void (*fp)(void *) = *(void (**)(void *))(obj + 0x40);
    if (fp) {
        fp(arg);
    }
}
