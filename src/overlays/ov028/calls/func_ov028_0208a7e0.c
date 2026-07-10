extern int func_ov028_0208ab78(int key, int data, int out, int nbytes);
extern void func_02002778(unsigned int addr, int size);
extern void func_020027b4(unsigned int addr, int size);

/* Anti-tamper DECRYPTOR (MATCHED). Rebuilds a 16-byte XOR key from the 4-byte
 * marker at ctx[-1] (byte i%4, inverted at i%15==0), finds the encrypted run
 * length by scanning ctx forward for the marker word, decrypts via 0208ab78,
 * then DC_FlushRange + IC_InvalidateRange so the CPU runs the decrypted code.
 * Declaration order key,i,marker,p,w,n pins i->r0 / marker->r1 / p->r2. */
void func_ov028_0208a7e0(unsigned int *ctx) {
    unsigned char key[16];
    int i;
    unsigned int marker;
    unsigned char *p;
    unsigned int w;
    int n;
    marker = ctx[-1];
    i = 0;
    p = key;
    do {
        unsigned char b = (unsigned char)(marker >> ((i % 4) * 8));
        *p = b;
        if (i % 15 == 0) *p = *p ^ 0xff;
        i++;
        p++;
    } while (i < 0x10);
    n = 0;
    w = *ctx;
    while (marker != w) { n++; w = ctx[n]; }
    if (n != 0) func_ov028_0208ab78((int)key, (int)ctx, (int)ctx, n << 2);
    func_02002778((unsigned int)ctx, n << 2);
    func_020027b4((unsigned int)ctx, n << 2);
}
