/* func_ov024_0208437c -- MobiClip: flush one ring's worth of decoded audio to both channels.
 * Walks as many blocks as func_ov024_020850a4 reports are pending, handing each to
 * func_ov024_020850bc for the left (+4) and right (+8) buffers and then flushing the same two
 * spans out of the data cache -- offsets and lengths are in 16-bit samples, hence the <<1.
 * The ring cursor (+0x1c) advances by the block size (+0x18) and wraps to 0 once it reaches
 * capacity (+0x20 blocks * block size).
 *
 * The block count is a 64-bit unsigned: the ROM widens the loop index with `mov r0,r4,asr #31`
 * and compares the pair (cmp highs / cmpeq lows / bcc). That only comes out of an `int` index
 * compared against an `unsigned long long`, so the types here are load-bearing.
 */
extern unsigned int func_ov024_020850a4(int chan);
extern void func_ov024_020850bc(int chan, int buf);
extern void DC_StoreRange(void *addr, unsigned int len);

void func_ov024_0208437c(int *ring) {
    int i;
    unsigned long long pending;

    pending = func_ov024_020850a4(ring[0]);
    for (i = 0; i < pending; i++) {
        func_ov024_020850bc(ring[0], ring[1] + (ring[7] << 1));
        func_ov024_020850bc(ring[0], ring[2] + (ring[7] << 1));
        DC_StoreRange((void *)(ring[1] + (ring[7] << 1)), ring[6] << 1);
        DC_StoreRange((void *)(ring[2] + (ring[7] << 1)), ring[6] << 1);
        ring[7] = ring[7] + ring[6];
        if (ring[7] == ring[8] * ring[6]) {
            ring[7] = 0;
        }
    }
}
