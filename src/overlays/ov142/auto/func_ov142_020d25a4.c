void func_ov142_020d25a4(char *p) {
    char *r3 = *(char **)(p + 4);
    *(int *)(*(char **)(r3 + 4) + 0x6c) = 0;
    *(int *)(*(char **)(r3 + 4) + 0x84) = 0;
    *(int *)(*(char **)(r3 + 4) + 0x5c) |= 2;
    *(int *)(*(char **)(*(char **)r3 + 0x390) + 4) = 0;
}
