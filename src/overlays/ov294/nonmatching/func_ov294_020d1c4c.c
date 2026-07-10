/* Equivalent, readable C (semantically complete, verified vs Ghidra decompile).
 * NOT byte-exact YET: two iterations took it 58->53 diffs; ~64B short. The
 * remaining work is a multi-detail bitfield/byte-truncation grind:
 *   - the u16 flags (lo) landing in r1 not r2 (register permutation cascade);
 *   - the facing-bit toggle keeps an extra `and #0xff` after `add #1` (the
 *     (bit0+1) result is byte-truncated before `&1` — likely an unsigned char
 *     intermediate) that mwcc drops here;
 *   - the result arg needs a (unsigned short) cast (lsl#0x10;lsr#0x10) before
 *     the call, which mwcc elides for the small 0/1/2/3 value from this source.
 * RESUME: model the toggle in an unsigned char and cast the 3rd call arg u16.
 * The asm stub keeps the blob byte-exact. */
extern int func_ov107_020c89e8(int obj, int src);
extern void func_ov107_020c5af8(int obj, int id, int mode, int node);

/* Tick the object's hit/stagger timer (+0x21a): subtract the delta computed by
 * 020c89e8 (clamped to +0x218), set sub-state 3 when it drains, then flip the
 * node's facing bit (+0xc) and fire the reaction handler (id 0x171). */
int func_ov294_020d1c4c(int param_1, int param_2, unsigned int *param_3) {
    int *node = *(int **)(param_1 + 0x214);

    if (*(short *)(param_1 + 0x21a) <= 0) {
        return 0;
    }
    {
        int taken = func_ov107_020c89e8(param_1, (int)param_3);
        int delta;
        int rem;
        unsigned int f;

        param_3[10] = taken;
        delta = *(short *)(param_1 + 0x21a) - taken;
        if (delta < 0) {
            rem = 0;
        } else {
            rem = *(short *)(param_1 + 0x218);
            if (delta <= rem) {
                rem = delta;
            }
        }
        *(short *)(param_1 + 0x21a) = (short)rem;
        if (*(short *)(param_1 + 0x21a) == 0) {
            *(unsigned char *)(*node + 0x1c7) = 3;
        }
        if ((int)param_3[10] > 0) {
            unsigned short lo;
            f = *param_3;
            lo = (unsigned short)f;
            if ((lo & 8) == 0 || (lo & 0x80) == 0 || (f >> 0x10) != 0x80) {
                unsigned char bv = *(unsigned char *)((char *)node + 0xc);
                unsigned int bit0 = (unsigned int)(bv << 0x1f) >> 0x1f;
                unsigned int nb = (bit0 + 1) & 1;
                unsigned char nbyte = bv & 0xfe | nb;
                unsigned int newbit = (unsigned int)((nbyte & 0xff) << 0x1f) >> 0x1f;
                if ((lo & 0x22) == 0) {
                    *(unsigned char *)((char *)node + 0xc) = nbyte;
                    func_ov107_020c5af8(param_1, 0x171, (newbit & 1) ? 0 : 1, node[1]);
                } else {
                    *(unsigned char *)((char *)node + 0xc) = nbyte;
                    func_ov107_020c5af8(param_1, 0x171, (newbit & 1) ? 2 : 3, node[1]);
                }
            }
        }
    }
    return 1;
}
