/* Issues one request through func_0201f750 for the id pair (n, n + 0x25) against the
 * table 0xb04a0 bytes into the block held by data_0204c234, using a stack byte as the
 * out-parameter, then lets func_0201ef58 consume it. */
extern char *data_0204c234;
extern void func_0201f750(unsigned short a, unsigned short b, int c, unsigned char *d);
extern void func_0201ef58(void);

void func_0203355c(int n) {
    unsigned char flag = 0;
    func_0201f750((unsigned short)n, (unsigned short)(n + 0x25),
                  *(int *)(data_0204c234 + 0xb04a0), &flag);
    func_0201ef58();
}
