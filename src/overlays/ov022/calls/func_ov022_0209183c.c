/* ov022: step one standing projectile a frame.
 *
 * The variant for shots that do not travel: the position is taken as it is and
 * the hit test is run against a zero delta. It runs only while the shot is
 * still inside the active window, which ends a fixed span before its animation
 * finishes; the first track with a length is the one that decides. The
 * animation is polled every frame either way, and when it reports done the
 * shot is retired and the retirement marshalled out to the other players.
 */

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

struct Shot {
    u8 pad0000[2];
    signed char nState;          /* 0x0002 */
    u8 pad0003;
    int nAge;                    /* 0x0004 */
    u8 pad0008[0x20];
    u16 nSlotFlags;              /* 0x0028 */
    u8 pad002a[0xa2];
    VecFx32 vecPos;              /* 0x00cc */
};

#define TRACK_COUNT 5
#define WINDOW_TAIL 0x9000

extern VecFx32 data_02041dc8;                  /* kVecZero */

extern int func_0202aef8(u16 *pAnim, u16 nTrack);
extern int func_ov022_02090f5c(void *pCtx, struct Shot *pShot,
                               const VecFx32 *pPos, const VecFx32 *pDelta);
extern unsigned int func_ov022_02091540(u16 *pAnim, int nFrame);
extern void func_ov022_02091d80(void *pCtx, struct Shot *pShot, int nReason);

int func_ov022_0209183c(void *pCtx, struct Shot *pShot, int nFrame)
{
    VecFx32 vPos;
    VecFx32 vDelta;
    int nTrack;
    int nLength;

    vPos = pShot->vecPos;
    vDelta = data_02041dc8;
    for (nTrack = 0; nTrack < TRACK_COUNT; nTrack++) {
        nLength = func_0202aef8(&pShot->nSlotFlags, (u16)nTrack);
        if (nLength > 0) {
            break;
        }
    }
    pShot->nAge = pShot->nAge + nFrame;
    if (pShot->nAge <= nLength - WINDOW_TAIL) {
        func_ov022_02090f5c(pCtx, pShot, &vPos, &vDelta);
    }
    if (func_ov022_02091540(&pShot->nSlotFlags, nFrame) != 0) {
        pShot->nState = 3;
    }
    if (pShot->nState == 3) {
        pShot->nAge = 0;
        func_ov022_02091d80(pCtx, pShot, 0);
    }
    return 0;
}
