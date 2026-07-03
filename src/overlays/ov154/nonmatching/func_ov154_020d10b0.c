int func_ov154_020d10b0(char *arg) {
    char *inner = **(char ***)(arg + 0x214);
    if (inner[0x1c7] != -1) return 0;
    inner[0x1c7] = 4;
    return 1;
}
