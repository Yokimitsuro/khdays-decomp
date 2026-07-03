int func_ov240_020ce594(char *arg) {
    char *inner = **(char ***)(arg + 0x214);
    if (inner[0x1c7] != -1) return 0;
    inner[0x1c7] = 10;
    return 1;
}
