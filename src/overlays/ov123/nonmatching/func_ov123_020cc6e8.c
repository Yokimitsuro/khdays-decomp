int func_ov123_020cc6e8(char *arg) {
    char *inner = **(char ***)(arg + 0x214);
    if (inner[0x1c7] != -1) return 0;
    inner[0x1c7] = 6;
    return 1;
}
