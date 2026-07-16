/* func_ov024_02085c3c -- MobiClip: drop the next decoded frame without emitting it.
 * Used to catch up when playback is behind: bumps the emitted counter and steps the ring
 * index (wrapping at ctx+0xa8). Returns 0 when there is nothing decoded to drop. */
int func_ov024_02085c3c(int ctx) {
    unsigned int emitted = *(unsigned int *)(ctx + 0x9c);
    int idx;

    if (emitted >= *(unsigned int *)(ctx + 0xa0)) {
        return 0;
    }
    *(unsigned int *)(ctx + 0x9c) = emitted + 1;
    idx = *(int *)(ctx + 0xc4) + 1;
    *(int *)(ctx + 0xc4) = idx;
    if (idx == *(int *)(ctx + 0xa8)) {
        *(int *)(ctx + 0xc4) = 0;
    }
    return 1;
}
