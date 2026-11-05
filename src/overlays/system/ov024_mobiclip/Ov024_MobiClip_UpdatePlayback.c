/* MobiClip: the playback state -- runs until the streams drain or the user skips.
 *
 * Spins on the decoder while it still has work, letting the user cut the movie
 * short with Start, keeping the sound driver fed, and parking everything while
 * the lid is shut. On the way out it drains whatever the skip left behind,
 * closes both streams, tears the video layers down and hands back the state
 * that follows.
 */

#include "nitro/types.h"

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
extern int Ov024_TickStreamSlots(void);
extern int Ov024_MobiClip_PlayerPollAbort(void);
extern void Ov024_MobiClip_StopPlayback(void);
extern void Ov024_MobiClip_StepScreenFade(struct MobiClipPlayer *pPlayer);
extern void Ov024_MobiClip_PlaybackIdleState(void);
extern void ActionScript_RequestSkip(void *pStream);
extern int Game_RunActionScript(void *pStream);
extern void Obj_ResetBothSubBlocksAndArm(void *pStream);
extern void GX_DispOff(void);
extern void DispCnt_ApplyPendingMode(void);
extern int GXx_GetMasterBrightness_(unsigned int nRegister);
extern int PM_SetLCDPower(int bResume);
extern int GetMasterBrightnessMain(void);
extern void SetMasterBrightnessMain(int brightness);
extern int GetMasterBrightnessSub(void);
extern void SetMasterBrightnessSub(int brightness);
extern int SoundStrm_HasPlaybackPos(int nChannel);
extern void Table_TailCallWithEntry(int nChannel, int nFrames);
extern void MsgQueue_SetMoviePlaying(int bOn);
extern void Session_SetMoviePlaying(int bOn);
extern void OS_WaitVBlankIntr(void);

void *Ov024_MobiClip_UpdatePlayback(void)
{
    struct MobiClipPlayer *player = NNSi_FndGetCurrentRootHeap();

    if (player->wState == 0) {
        return 0;
    }

    if ((player->wFlags & 2) == 0
        && (player->nStream0State == 2 || player->nStream1State == 2)) {
        while (Ov024_TickStreamSlots() == 0) {
            if (player->wFlags & 4) {
                if (Ov024_MobiClip_PlayerPollAbort() != 0) {
                    if (player->wFlags & 1) {
                        ActionScript_RequestSkip(player->obj);
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
                if (Game_RunActionScript(player->obj) == 0) {
                    player->wFlags &= ~1;
                }
            }

            if (player->bSuspended == 0 && ((KEYS_EXTRA & LID_CLOSED) >> 15) != 0) {
                GX_DispOff();
                PM_SetLCDPower(0);
                player->bSuspended = 1;
            } else if (player->bSuspended != 0
                       && ((KEYS_EXTRA & LID_CLOSED) >> 15) == 0) {
                if (PM_SetLCDPower(1) != 0) {
                    player->bSuspended = 0;
                    SetMasterBrightnessMain(GetMasterBrightnessMain());
                    SetMasterBrightnessSub(GetMasterBrightnessSub());
                    DispCnt_ApplyPendingMode();
                }
            }
        }

    drain:
        if (player->wFlags & 4) {
            if (Ov024_MobiClip_PlayerPollAbort() == 0) {
                do {
                    OS_WaitVBlankIntr();
                } while (Ov024_MobiClip_PlayerPollAbort() == 0);
            }
            if (player->wFlags & 1) {
                ActionScript_RequestSkip(player->obj);
            }
        }
        Ov024_MobiClip_StopPlayback();
        player->nStream0State = player->nStream1State = 3;
        if (player->wFlags & 1) {
            goto interrupted;
        }
        goto teardown;
    } else if (Game_RunActionScript(player->obj) == 0) {
        goto teardown;
    }
interrupted:
    return 0;

teardown:
    if (player->wFlags & 4) {
        if (SoundStrm_HasPlaybackPos(0) != 0) {
            Table_TailCallWithEntry(0, 0x14);
        }
    }
    Obj_ResetBothSubBlocksAndArm(player->obj);
    MsgQueue_SetMoviePlaying(0);
    Session_SetMoviePlaying(0);

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
    Ov024_MobiClip_StepScreenFade(player);
    SetMasterBrightnessMain(GXx_GetMasterBrightness_(0x0400006c));
    SetMasterBrightnessSub(GXx_GetMasterBrightness_(0x0400106c));
    return (void *)&Ov024_MobiClip_PlaybackIdleState;
}
