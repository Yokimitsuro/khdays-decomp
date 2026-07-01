void func_ov025_020a970c(char *obj, int v) {
    *(int *)obj = v;
    *(int *)(obj + 0x20) = v;
}
