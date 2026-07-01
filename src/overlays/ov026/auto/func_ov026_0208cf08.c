void func_ov026_0208cf08(char *obj, char *src) {
    *(int *)obj = 1;
    *(int *)(obj + 0xc) = (int)src;
    *(int *)(obj + 4) = *(int *)(src + 0x14);
    *(int *)(obj + 8) = *(int *)(src + 0x88);
}
