/* func_ov024_02083590 -- MobiClip: open a stream from a parsed header on the stack.
 * Builds the decoder's header copy in a local (func_ov024_020834b0 derives the active picture
 * size and crop from it) and hands both to func_0202f834 to start the stream. */
extern void func_ov024_020834b0(int ctx, unsigned short *dst, unsigned short *src);
extern void func_0202f834(unsigned int *ctx, int a, unsigned int b, unsigned short *hdr);

void func_ov024_02083590(unsigned int *ctx, int a, unsigned int b, unsigned short *src) {
    unsigned short hdr[8];
    func_ov024_020834b0((int)ctx, hdr, src);
    func_0202f834(ctx, a, b, hdr);
}
