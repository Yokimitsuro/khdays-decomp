struct Rc4 {
    int i;
    int j;
    unsigned char s[256];
};

extern void func_ov028_0208a994(struct Rc4 *ctx, unsigned char *key, int keylen);
extern int WM_EndKeySharing_0x0208ab14();

int func_ov028_0208ab78(unsigned char *key, void *a, void *b, int c) {
    struct Rc4 ctx;
    int r;

    func_ov028_0208a994(&ctx, key, 0x10);
    r = WM_EndKeySharing_0x0208ab14(&ctx, a, b, c);
    return (r == -1) ? -1 : 0;
}
