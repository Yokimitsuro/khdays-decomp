int func_ov192_020d2448(char *arg) {
    char *inner = **(char ***)(arg + 0x214);
    if (inner[0x1c7] != -1) return 0;
    inner[0x1c7] = 7;
    return 1;
}
