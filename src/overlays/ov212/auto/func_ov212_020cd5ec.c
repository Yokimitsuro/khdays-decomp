void func_ov212_020cd5ec(char *obj, int arg) {
    if (arg) {
        *(int *)(obj + 0x44) = 0;
    }
    *(int *)(obj + 0x70) = arg ? 4 : 2;
}
