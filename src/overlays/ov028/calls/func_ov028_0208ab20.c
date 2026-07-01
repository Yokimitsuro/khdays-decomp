struct Rc4 {
    int i;
    int j;
    unsigned char s[256];
};

extern void func_ov028_0208a994(struct Rc4 *ctx, unsigned char *key, int keylen);
extern int func_ov028_0208aa78();

int func_ov028_0208ab20(unsigned char *key, void *a, void *b, int c) {
    struct Rc4 ctx;
    int r;

    func_ov028_0208a994(&ctx, key, 0x10);
    r = func_ov028_0208aa78(&ctx, a, b, c);
    return (r == -1) ? -1 : 0;
}
