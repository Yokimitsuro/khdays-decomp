extern void func_ov028_0208aa54(unsigned char *table);
extern unsigned char func_ov028_0208aa08(unsigned int *ctx);

int func_ov028_0208aa78(unsigned int *ctx, unsigned char *src, unsigned char *dst, unsigned int len) {
    unsigned char table[256];
    unsigned int i;
    unsigned char k;
    if ((len & 3) != 0) return -1;
    func_ov028_0208aa54(table);
    i = 0;
    while (i < len) {
        unsigned char *s = src + i;
        unsigned char *d = dst + i;
        unsigned char t;
        k = func_ov028_0208aa08(ctx);
        t = src[i];
        t ^= k;
        dst[i] = t;
        k = func_ov028_0208aa08(ctx);
        t = s[1];
        t ^= k;
        d[1] = t;
        d[2] = table[s[2]];
        d[3] = s[3];
        i += 4;
    }
    return 0;
}
