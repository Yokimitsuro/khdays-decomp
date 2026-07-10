/* NONMATCHING: register-coloring tie. The loaded byte u lands in lr vs r0 in the
 * original, cascading through the 2D bit-set address math. Structure ~identical.
 * Semantics: if global data_ov022_020b2eb8 set, set bit (u&7) in the byte at
 * global+0x2b0 + ((u>>2)&7)*3 + ((u>>6)&3); then LoadGlobalPtrField70. */
extern int data_ov022_020b2eb8;
extern void func_02030e50(void);
void func_ov022_020b0e64(unsigned char *arg0) {
    int g = data_ov022_020b2eb8;
    unsigned int u;
    int row;
    if (g == 0) return;
    u = *arg0;
    row = g + 0x2b0 + ((u << 0x1a) >> 0x1d) * 3;
    *(unsigned char *)(row + ((u << 0x18) >> 0x1e)) |= 1 << (u & 7);
    func_02030e50();
}
