/* func_ov024_02085110 -- MobiClip: reset the stream-reader state on the decoder context.
 * Clears the source object slot, the per-stream cursors (ctx[0x16..0x1d]) and the frame
 * cursor (ctx[0x25]), leaving the frame counters alone. */
void func_ov024_02085110(int *ctx) {
    ctx[0] = 0;
    ctx[0x17] = 0;
    ctx[0x18] = 0;
    ctx[0x1a] = 0;
    ctx[0x1b] = 0;
    ctx[0x1c] = 0;
    ctx[0x1d] = 0;
    ctx[0x19] = 0;
    ctx[0x16] = 0;
    ctx[0x25] = 0;
}
