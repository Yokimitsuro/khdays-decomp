int func_ov028_0208aa54(unsigned char *s) {
    int i;
    for (i = 0; i < 0x100; i++) {
        s[i] = (i & 0xff) ^ 1;
    }
    return 0;
}
