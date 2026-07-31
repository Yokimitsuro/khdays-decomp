/*
 * Ov002_PollSessionReady - readiness gate used by Ov002_TryAdvancePhase. Returns 1 when the
 * phase may proceed, 0 while it must wait.
 *
 * Clears heap+0x8da8, then: if the session is inactive (func_02030670) the phase may proceed
 * (return 1). If the session is active and ready (func_02030694), sets bit0 of the status byte
 * at heap+0x8d9d and proceeds. If active but not ready, it submits a request via
 * func_ov002_0206fb84(0x12, {idx, tag}) - where idx is the low byte of the local player index
 * (func_02030788) and tag is the halfword at heap+0x8da0 - stores the returned handle at
 * heap+0x8da2, and returns 0 (keep waiting) while that handle is still 0xffff (unallocated),
 * else 1.
 *
 * THUMB. The tag read at heap+0x8da0 is an unsigned halfword (ldrh); the 4-byte request record
 * is built on the stack with only bytes +1 (idx) and the +2 halfword (tag) set.
 */

typedef unsigned char  u8;
typedef unsigned short u16;

extern int  NNSi_FndGetCurrentRootHeap(void);
extern int  func_02030670(void);
extern int  func_02030694(void);
extern int  func_02030788(void);
extern u16  func_ov002_0206fb84(int kind, void *out);

int func_ov002_020693e0(void)
{
    int base = NNSi_FndGetCurrentRootHeap();

    *(int *)(base + 0x8da8) = 0;
    if (func_02030670() == 0) {
        return 1;
    }
    if (func_02030694() != 0) {
        *(u8 *)(base + 0x8d9d) |= 1;
    } else {
        char stk[4];
        u16 v;
        stk[1] = (char)func_02030788();
        *(short *)(stk + 2) = *(u16 *)(base + 0x8da0);
        v = func_ov002_0206fb84(0x12, stk);
        *(short *)(base + 0x8da2) = v;
        if (*(u16 *)(base + 0x8da2) == 0xffff) {
            return 0;
        }
    }
    return 1;
}
