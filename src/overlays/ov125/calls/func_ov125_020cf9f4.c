extern int func_01ffa724();

int func_ov125_020cf9f4(char *a, int b, int *c) {
    char *s = *(char **)(a + 0x214);
    unsigned short v = (unsigned short)*c;
    if (v & 1) {
        if (*(int *)(s + 0x1c) != 0) {
            return 0;
        }
        func_01ffa724(-0x1000, s + 0xc, s + 0xc);
        *(int *)(s + 0x1c) = 1;
        *(int *)(s + 0x18) = 0;
        return 1;
    }
    return 0;
}
