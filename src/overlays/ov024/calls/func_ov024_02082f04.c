/* MobiClip: the playback state -- runs until the streams drain or the user skips.
 *
 * Spins on the decoder while it still has work, letting the user cut the movie
 * short with Start, keeping the sound driver fed, and parking everything while
 * the lid is shut. On the way out it drains whatever the skip left behind,
 * closes both streams, tears the video layers down and hands back the state
 * that follows.
 */
typedef unsigned char u8;
typedef unsigned short u16;

#define REG_KEYINPUT   (*(volatile u16 *)0x04000130)
#define KEYS_EXTRA     (*(volatile u16 *)0x027fffa8)
#define KEY_MASK       0x2fff
#define KEY_START      0x0008
#define LID_CLOSED     0x8000

struct MobiClipPlayer {
    u16 wState;
    u16 wFlags;
    char obj[0x130 - 4];
    int nEndReason;
    char pad0134[0x8bd8 - 0x134];
    int nStream0State;
    int nStream1State;
    u8 bSuspended;
    u8 pad8be1;
    u8 nFadeScreens;
    u8 pad8be3;
    int bFadeToWhite;
    int nFadeStep;
    int nSkipLatch;
};

extern int data_ov024_02093a20;

extern struct MobiClipPlayer *NNSi_FndGetCurrentRootHeap(void);
extern int func_ov024_02084db8(void);
extern int func_ov024_02082ee0(void);
extern void func_ov024_02084b14(void);
extern void func_ov024_02082960(struct MobiClipPlayer *pPlayer);
extern void func_ov024_020831d4(void);
extern void func_02021048(void *pStream);
extern int func_02020e58(void *pStream);
extern void func_02020cc8(void *pStream);
extern void func_02005630(void);
extern void func_0200566c(void);
extern void func_02005760(unsigned int nRegister);
extern int func_0200d49c(int bResume);
extern void func_0201e428(void);
extern void func_0201e374(void);
extern void func_0201e438(void);
extern void func_0201e3cc(void);
extern int func_02034014(int nChannel);
extern void func_02033fec(int nChannel, int nFrames);
extern void func_02031574(int bOn);
extern void func_02030e64(int bOn);
extern void OS_WaitVBlankIntr(void);

void *func_ov024_02082f04(void)
{
    struct MobiClipPlayer *player = NNSi_FndGetCurrentRootHeap();

    if (player->wState == 0) {
        return 0;
    }

    if ((player->wFlags & 2) == 0
        && (player->nStream0State == 2 || player->nStream1State == 2)) {
        while (func_ov024_02084db8() == 0) {
            if (player->wFlags & 4) {
                if (func_ov024_02082ee0() != 0) {
                    if (player->wFlags & 1) {
                        func_02021048(player->obj);
                    }
                    goto drain;
                }
            } else if (player->bSuspended == 0 && (player->wFlags & 8)) {
                int keys = (u16)(((REG_KEYINPUT | KEYS_EXTRA) ^ KEY_MASK) & KEY_MASK);
                int start = keys & KEY_START;

                if (player->nSkipLatch == 0 && start != 0) {
                    player->nFadeStep = 0;
                    player->wFlags |= 4;
                    *(int *)&data_ov024_02093a20 = 1;
                }
                player->nSkipLatch = start;
            }

            if (player->wFlags & 1) {
                if (func_02020e58(player->obj) == 0) {
                    player->wFlags &= ~1;
                }
            }

            if (player->bSuspended == 0 && ((KEYS_EXTRA & LID_CLOSED) >> 15) != 0) {
                func_02005630();
                func_0200d49c(0);
                player->bSuspended = 1;
            } else if (player->bSuspended != 0
                       && ((KEYS_EXTRA & LID_CLOSED) >> 15) == 0) {
                if (func_0200d49c(1) != 0) {
                    player->bSuspended = 0;
                    func_0201e428();
                    func_0201e374();
                    func_0201e438();
                    func_0201e3cc();
                    func_0200566c();
                }
            }
        }

    drain:
        if (player->wFlags & 4) {
            if (func_ov024_02082ee0() == 0) {
                do {
                    OS_WaitVBlankIntr();
                } while (func_ov024_02082ee0() == 0);
            }
            if (player->wFlags & 1) {
                func_02021048(player->obj);
            }
        }
        func_ov024_02084b14();
        player->nStream0State = player->nStream1State = 3;
        if (player->wFlags & 1) {
            goto interrupted;
        }
        goto teardown;
    } else if (func_02020e58(player->obj) == 0) {
        goto teardown;
    }
interrupted:
    return 0;

teardown:
    if (player->wFlags & 4) {
        if (func_02034014(0) != 0) {
            func_02033fec(0, 0x14);
        }
    }
    func_02020cc8(player->obj);
    func_02031574(0);
    func_02030e64(0);

    switch (player->nEndReason) {
    case 0:
    case 2:
        player->wState = 2;
        break;
    case 1:
        break;
    }

    player->nFadeStep = 0xf;
    OS_WaitVBlankIntr();
    func_ov024_02082960(player);
    func_02005760(0x0400006c);
    func_0201e374();
    func_02005760(0x0400106c);
    func_0201e3cc();
    return (void *)&func_ov024_020831d4;
}
