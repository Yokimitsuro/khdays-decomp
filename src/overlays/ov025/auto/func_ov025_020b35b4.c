void func_ov025_020b35b4(char *obj) {
    if (*(void **)obj) {
        (*(void (**)(void *))(obj + 8))(obj);
    }
}
