extern int func_ov028_0208ab20(int key, int data, int out, int nbytes);
extern void func_02002778(unsigned int addr, int size);
extern void func_020027b4(unsigned int addr, int size);

void func_ov028_0208a8ac(unsigned int *ctx) {
    unsigned char key[16];
    int i;
    unsigned int marker;
    unsigned char *p;
    unsigned int w;
    marker = ctx[1];
    i = 0;
    p = key;
    do {
        unsigned char b = (unsigned char)(marker >> ((i % 4) * 8));
        *p = b;
        if (i % 15 == 0) *p = *p ^ 0xff;
        i++;
        p++;
    } while (i < 0x10);
    w = *ctx;
    while (w != marker) {
        ctx = ctx - 1;
        w = *ctx;
    }
    w = ctx[1];
    i = 0;
    while (marker != w) {
        i++;
        w = ctx[i + 1];
    }
    if (i != 0) func_ov028_0208ab20((int)key, (int)(ctx + 1), (int)(ctx + 1), i << 2);
    func_02002778((unsigned int)(ctx + 1), i << 2);
    func_020027b4((unsigned int)(ctx + 1), i << 2);
}
