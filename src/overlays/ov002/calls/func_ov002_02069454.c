/*
 * Ov002_TickSessionRequest - session per-frame request/sync updater (larger sibling of
 * Ov002_PollSessionReady). Returns 1 when the caller should advance, 0 otherwise.
 *
 * Inactive session -> advance (return 1). Active + ready: if no request is pending
 * (heap+0x8da4 == 0) and the stored source id (heap+0x8d9d) matches the current one
 * (func_01fff974), it submits command 0x12 via Ov002_BuildSessionCommand with the local player
 * index and the tag at heap+0x8da0, stores the handle at heap+0x8da2, and - when the handle is
 * valid - marks the request pending (heap+0x8da4=1), clears the id/flag bytes and bumps the
 * retry counter at heap+0x8da0 (0xffff -> 0, else +1). If a request IS pending it polls
 * func_02031440(handle) and advances when it reports done. Active + not-ready advances when the
 * heap+0x8d9c flag is set. On advance it clears the pending byte and, while still not ready,
 * clears the id/flag bytes and bumps the same counter.
 *
 * THUMB. The heap base is char* so the far fields use [base,off] addressing (offsets derived
 * from the 0x8da2 anchor); the retry counter at heap+0x8da0 is volatile so it is re-loaded on
 * each access and its address re-derived, matching the original (mwcc would otherwise cache both
 * the value and a full pointer across the compare).
 */

typedef unsigned char  u8;
typedef unsigned short u16;

extern int  NNSi_FndGetCurrentRootHeap(void);
extern int  func_02030670(void);
extern int  func_02030694(void);
extern u16  func_01fff974(void);
extern int  func_02030788(void);
extern u16  func_ov002_0206fb84(int kind, void *out);
extern int  func_02031440(int h);

int func_ov002_02069454(void)
{
    char *base = (char *)NNSi_FndGetCurrentRootHeap();
    int result = 0;

    if (func_02030670() == 0) {
        return 1;
    }
    if (func_02030694() != 0) {
        if (*(u8 *)(base + 0x8da4) == 0) {
            if (*(u8 *)(base + 0x8d9d) == func_01fff974()) {
                char stk[4];
                u16 h;
                stk[1] = (char)func_02030788();
                *(short *)(stk + 2) = *(volatile u16 *)(base + 0x8da0);
                h = func_ov002_0206fb84(0x12, stk);
                *(short *)(base + 0x8da2) = h;
                if (*(u16 *)(base + 0x8da2) != 0xffff) {
                    *(u8 *)(base + 0x8da4) = 1;
                    *(u8 *)(base + 0x8d9d) = 0;
                    *(u8 *)(base + 0x8d9c) = 0;
                    if (*(volatile u16 *)(base + 0x8da0) == 0xffff) {
                        *(volatile u16 *)(base + 0x8da0) = 0;
                    } else {
                        *(volatile u16 *)(base + 0x8da0) = *(volatile u16 *)(base + 0x8da0) + 1;
                    }
                }
            }
        } else {
            if (func_02031440(*(u16 *)(base + 0x8da2)) == 0) {
                result = 1;
            }
        }
    } else if (*(u8 *)(base + 0x8d9c) != 0) {
        result = 1;
    }
    if (result != 0) {
        *(u8 *)(base + 0x8da4) = 0;
        if (func_02030694() == 0) {
            *(u8 *)(base + 0x8d9d) = 0;
            *(u8 *)(base + 0x8d9c) = 0;
            if (*(volatile u16 *)(base + 0x8da0) == 0xffff) {
                *(volatile u16 *)(base + 0x8da0) = 0;
            } else {
                *(volatile u16 *)(base + 0x8da0) = *(volatile u16 *)(base + 0x8da0) + 1;
            }
        }
    }
    return result;
}
