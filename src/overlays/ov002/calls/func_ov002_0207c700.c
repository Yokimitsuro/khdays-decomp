typedef unsigned short u16;

extern void func_ov002_0207c67c(u16 *pAnim, int nElapsed);

/* Advance one element's animation clock by a frame delta.
 *
 * The clock is in 12 bit fixed point frames, so the last frame of a clip that
 * ends at nEnd is nEnd - 0x1000. Once the clock is past it, a looping clip
 * wraps by subtracting the clip length and a one shot clip is clamped there and
 * reports that it has finished. The frame is pushed to the animation object
 * only while the element is visible, and the clock advances unless the clip has
 * just finished.
 *
 * Returns zero once the clip is done, which is what every caller tests.
 */
int func_ov002_0207c700(char *pElement, u16 *pAnim, int nDelta, int bLoop,
                        int nEnd, int *pClock)
{
    int nClock;
    int nLast;
    int bFinished;

    nClock = *pClock;
    nLast = nEnd - 0x1000;
    bFinished = 0;

    if (nClock > nLast) {
        if (bLoop != 0) {
            *pClock = nClock - nLast;
        } else {
            *pClock = nLast;
            bFinished = 1;
        }
    }

    if ((*(u16 *)(pElement + 0x12) & 4) != 0) {
        func_ov002_0207c67c(pAnim, *pClock);
    }

    if (!bFinished) {
        *pClock = *pClock + nDelta;
    }

    return !bFinished;
}
