/* Advance an animation stream position by `delta` (the accumulator is *obj->stream
 * at +8). If the position reached the current segment's end (limit<<12, where limit
 * is the 16-bit field at stream[2]+4), either restart the segment and flag it
 * complete (+0xc = 1), or — when a repeat counter (+0x54) is still non-zero —
 * rewind the accumulator to 0 and decrement that counter (clamped at -1). If the
 * position is still short of the end, just clear the completion flag. */
void func_0202e400(int obj, int delta) {
    int *p;
    unsigned int limit;
    **(int **)(obj + 8) += delta;
    p = *(int **)(obj + 8);
    limit = *(unsigned short *)(p[2] + 4);
    if (*p >= (int)(limit << 12)) {
        if (*(int *)(obj + 0x54) == 0) {
            *p = limit << 12;
            *(int *)(obj + 0xc) = 1;
        } else {
            int c;
            *p = 0;
            c = *(int *)(obj + 0x54) - 1;
            *(int *)(obj + 0x54) = c;
            if (c < 0) *(int *)(obj + 0x54) = -1;
        }
    } else {
        *(int *)(obj + 0xc) = 0;
    }
}
