void func_ov008_020558f4(char *obj, void *arg) {
    void (*fp)(void *) = *(void (**)(void *))(obj + 0x40);
    if (fp) {
        fp(arg);
    }
}
