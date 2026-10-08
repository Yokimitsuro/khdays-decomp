/* Initialises RC4 with a 16-byte key and decrypts a block of instructions; returns 0 or -1. */

struct Rc4 {
    int i;
    int j;
    unsigned char s[256];
};

extern void Ov028_RC4_Init(struct Rc4 *ctx, unsigned char *key, int keylen);
extern int Ov028_RC4_DecryptInstructions();

int Ov028_RC4_InitAndDecryptInstructions(unsigned char *key, void *a, void *b, int c) {
    struct Rc4 ctx;
    int r;

    Ov028_RC4_Init(&ctx, key, 0x10);
    r = Ov028_RC4_DecryptInstructions(&ctx, a, b, c);
    return (r == -1) ? -1 : 0;
}
