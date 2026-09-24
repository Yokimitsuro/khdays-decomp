/* SHA-1 context init: load the five IV words into ctx[0..4] and zero the
 * length/buffer state (ctx[5..7]). */
void func_0200b74c(unsigned int *ctx) {
    ctx[0] = 0x67452301;
    ctx[1] = 0xefcdab89;
    ctx[2] = 0x98badcfe;
    ctx[3] = 0x10325476;
    ctx[4] = 0xc3d2e1f0;
    ctx[5] = 0;
    ctx[6] = 0;
    ctx[7] = 0;
}
