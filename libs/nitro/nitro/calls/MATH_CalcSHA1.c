/* One-shot SHA-1 over a buffer into a 0x68-byte context on the stack. */
extern void func_0200b74c(void *ctx);
extern void func_0200b79c(void *ctx, const void *data, unsigned int len);
extern void func_0200b8f0(void *ctx, void *digest);

void MATH_CalcSHA1(void *digest, const void *data, unsigned int len) {
    char ctx[0x68];
    func_0200b74c(ctx);
    func_0200b79c(ctx, data, len);
    func_0200b8f0(ctx, digest);
}
