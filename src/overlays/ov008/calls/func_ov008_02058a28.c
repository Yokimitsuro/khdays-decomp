/*
 * Ov008_Menu_AdvanceIntoPanel - one-shot handler that advances the current menu
 * context into sub-scene 8 (a detail panel) when the entry conditions are met.
 *
 * Gated on bit 7 of the context status halfword at +0x5c6 being clear (the "not
 * yet advanced" latch). While clear it runs the per-frame menu setup steps
 * (func_ov008_020574c0 / func_ov008_02057f58 / func_ov008_020579a8), then, only
 * if all of the following hold, performs the advance:
 *   - game flag 0x200c is set;
 *   - bit 4 of the shared context (*data_ov008_02090f1c) status halfword is clear;
 *   - the cursor lookup func_ov008_0204ecd8(0) returns a record whose byte[3] == 8.
 * The advance primes sub-scene 8 from the cursor, stamps the sub-struct, sets the
 * 0x80 latch bit so it fires once, and points the target slot at duration 300.
 * The teardown/refresh at ctx+0x98 (func_ov008_0205a684) always runs.
 *
 * The +0x5c6 bit tests use the (x << N) >> 31 shift form (bit 7 for N=24, bit 4
 * for N=27), matching the ROM's lsl/lsr pair rather than a tst mask.
 */

extern void func_ov008_020574c0(void);
extern void func_ov008_02057f58(void);
extern void func_ov008_020579a8(int obj);
extern int func_02023588(int flag);
extern int func_ov008_0204ecd8(int slot);
extern void func_ov008_0205714c(int arg);
extern void func_02033fb4(int a, int b);
extern void func_ov008_02050970(int slot, unsigned int dur);
extern void func_ov008_0205a684(int obj);
extern int data_ov008_02090f1c;

void func_ov008_02058a28(int param_1, int param_2, int param_3, int param_4)
{
    int r;

    if ((((unsigned int)*(unsigned short *)(param_1 + 0x5c6) << 0x18) >> 0x1f) == 0) {
        func_ov008_020574c0();
        func_ov008_02057f58();
        func_ov008_020579a8(param_1);
        if (func_02023588(0x200c) != 0 &&
            (((unsigned int)*(unsigned short *)(data_ov008_02090f1c + 0x5c6) << 0x1b) >> 0x1f) == 0 &&
            (r = func_ov008_0204ecd8(0)) != 0 &&
            *(unsigned char *)(r + 3) == 8) {
            func_ov008_0205714c(8);
            func_02033fb4(1, 4);
            *(unsigned short *)(param_1 + 0x5c6) |= 0x80;
            func_ov008_02050970(-1, 300);
        }
    }
    func_ov008_0205a684(param_1 + 0x98);
}
