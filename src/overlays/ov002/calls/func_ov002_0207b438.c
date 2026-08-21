typedef unsigned short u16;
typedef unsigned char u8;

extern void *func_ov002_0207687c(char *pElement);
extern int func_020339b0(int nSlot, int nId);
extern int func_02033788(int nSlot, int nId);
extern void func_02033d0c(int nId, int nMode, void *pBlock, int nParam);
extern void func_020235a8(int nField);
extern void func_020235bc(int nField);
extern int func_ov022_02083f0c(void);
extern int func_ov022_02083f5c(void);
extern void func_ov022_02086818(int nHandle, int nMode);
extern void func_ov002_0204cee0(int nHandle, int nMode);
extern int func_01fffe14(void);
extern void *func_01fffde0(int nIndex);
extern void func_ov002_0207b078(char *pElement, int nIndex, int bOn);
extern int func_ov022_020882f8(void);
extern void func_ov022_020ad838(void *pEntry, int bOn);
extern int func_ov002_0206aaa0(void);
extern int func_ov002_0206b78c(void);
extern int func_ov002_0207c700(char *pElement, char *pAnim, void *pCtx,
                               int nMode, int nRange, void *pOut);
extern void func_ov002_0207c618(short *pAnim, int nTrack, int nFrame);
extern void func_0202af2c(u16 *pAnim);
extern void func_ov002_0207b698(void);

/* Drive an element through its talk step and say what runs next.
 *
 * The pending bit is dropped on entry and an element that is not active does
 * nothing. An element already finished tears the prompt down and hands back the
 * follow-up handler. Otherwise the prompt is put up if it is not up yet, and
 * once the player is in a state that allows it the line is advanced: each step
 * counts the track down, and the last one either plays the closing effect or
 * releases the animation. When the line has run far enough the camera and the
 * other entries are let go again.
 */
void *func_ov002_0207b438(char *pElement)
{
    void *pCtx;
    int nFlags;
    int nA;
    int nB;
    int i;

    pCtx = func_ov002_0207687c(pElement);
    *(u8 *)(pElement + 0x1b5) &= ~0x80;

    if ((*(u16 *)(pElement + 0x12) & 4) == 0) {
        return 0;
    }

    nFlags = *(u8 *)(pElement + 0x1b5);

    if ((nFlags & 1) != 0) {
        if ((nFlags & 4) != 0) {
            if (func_020339b0(-1, 0x2be) == 0) {
                return 0;
            }
            *(u8 *)(pElement + 0x1b5) &= ~4;
            if ((*(u8 *)(pElement + 0x1b5) & 0x10) != 0) {
                *(u8 *)(pElement + 0x1b5) &= ~0x10;
                func_020235bc(0x20e0);
            }
        }
        *(u8 *)(pElement + 0x17) = 1;
        *(u16 *)(pElement + 0x12) |= 8;
        return func_ov002_0207b698;
    }

    if ((nFlags & 2) != 0) {
        nA = func_ov022_02083f0c();
        func_ov022_02086818(func_ov022_02083f5c(), 0);
        func_ov002_0204cee0(nA, 1);
        func_ov002_0207b078(pElement, func_01fffe14(), 1);

        for (i = 0; i < func_ov022_020882f8(); i++) {
            *(unsigned long long *)func_01fffde0(i) |= 0x40000000000ULL;
            func_ov022_020ad838(func_01fffde0(i), 1);
        }
    }

    if ((*(u8 *)(pElement + 0x1b5) & 4) == 0) {
        if (func_02033788(-1, 0x2be) != 0) {
            *(u8 *)(pElement + 0x1b5) |= 4;
            *(u8 *)(pElement + 0x1b5) |= 0x10;
            func_020235a8(0x20e0);
        } else {
            return 0;
        }
    }

    if (func_ov002_0206aaa0() != 0
        && (func_ov002_0206b78c() == 1 || func_ov002_0206b78c() == 5)) {
        if (*(signed char *)(pElement + 0x1b8) == 2
            && (*(u8 *)(pElement + 0x1b5) & 8) == 0) {
            func_02033d0c(0x2be, 0, pElement + 0xe0, 0);
            *(u8 *)(pElement + 0x1b5) |= 8;
        }

        if (func_ov002_0207c700(pElement, pElement + 0x3c, pCtx, 0, 0x2a000,
                                pElement + 0x1b0) == 0) {
            *(signed char *)(pElement + 0x1b8) -= 1;
            func_ov002_0207c618((short *)(pElement + 0x3c),
                                *(signed char *)(pElement + 0x1b8), 0);
            *(int *)(pElement + 0x1b0) = 0;

            if (*(signed char *)(pElement + 0x1b8) == 1) {
                func_02033d0c(0x2be, 1, pElement + 0xe0, 0);
            } else if (*(signed char *)(pElement + 0x1b8) == 0) {
                *(u8 *)(pElement + 0x1b5) |= 1;
                func_0202af2c((u16 *)(pElement + 0x3c));
            }
        } else if ((*(u8 *)(pElement + 0x1b5) & 2) != 0
                   && *(signed char *)(pElement + 0x1b8) == 1
                   && *(int *)(pElement + 0x1b0) >= 0x5000) {
            nA = func_ov022_02083f0c();
            nB = func_ov022_02083f5c();
            func_ov002_0204cee0(nA, 0);
            func_ov022_02086818(nB, 1);
            func_ov002_0207b078(pElement, func_01fffe14(), 0);

            for (i = 0; i < func_ov022_020882f8(); i++) {
                *(unsigned long long *)func_01fffde0(i) &= ~0x40000000000ULL;
                func_ov022_020ad838(func_01fffde0(i), 0);
            }
        }
    }

    return 0;
}
