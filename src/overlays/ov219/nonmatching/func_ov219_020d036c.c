int func_ov219_020d036c(char *arg) {
    char *inner = **(char ***)(arg + 0x214);
    if (inner[0x1c7] != -1) return 0;
    inner[0x1c7] = 10;
    return 1;
}
