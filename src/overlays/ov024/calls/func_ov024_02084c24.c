/* MobiClip: run one slot's state machine, one call per turn.
 *
 * The states are: 0 idle, 1 starting, 2 decoding, 3 catching up, 4 draining,
 * 5 waiting for the last frame, 6 finished. Reports non-zero only when the
 * slot has nothing left to do, which is what the teardown polls for.
 */
typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef long long s64;

#define QUEUE_DEPTH 10

struct MobiClipAudioStream {
    void *pStream;
    short *pLeft;
    short *pRight;
    int pad000c;
    u32 nSampleRate;
    u32 nFrameSamples;
    u32 nChannels;
    int nFilled;
    u32 nBlocks;
};

struct MobiClipFrameTimer {
    void *pStream;
    u8 alarm[0x2c];
    s64 nStartTick;
    u8 nState;
    u8 nFrontBuffer;
    u8 bPresented;
    u8 pad003b[0x40 - 0x3b];
    u32 nDecoded;
    u32 nConsumed;
    int nPresented;
    u64 nTimeBase;
    void *pfnBufferForIndex;
};

struct MobiClipGlobals {
    u8 bStopped;
    u8 pad0001[3];
    struct MobiClipAudioStream *pAudio;
    struct MobiClipFrameTimer *pMain;
    struct MobiClipFrameTimer *pSub;
};

extern struct MobiClipGlobals data_ov024_02093a2c;
extern int data_ov024_0209ba48;

extern s64 func_020031d4(void);
extern void OS_SetAlarm(void *pAlarm, u64 nTick, void *pfnHandler, void *pArg);
extern void SND_SetChannelVolume(u32 nChannelMask, int nVolume, int nShift);
extern void func_020087c0(int nChannel);
extern void func_02003618(void *pAlarm);
extern void func_ov024_020840a4(struct MobiClipAudioStream *pAudio);
extern int func_ov024_02085014(void *pStream);
extern void func_ov024_0208435c(struct MobiClipFrameTimer *pTimer);
extern void func_ov024_0208437c(struct MobiClipAudioStream *pAudio);
extern void func_ov024_0208421c(struct MobiClipFrameTimer *pTimer);

int func_ov024_02084c24(struct MobiClipFrameTimer *pTimer)
{
    struct MobiClipAudioStream *pAudio;
    int bOwnsAudio;
    int nState;

    if (pTimer == 0) {
        return 1;
    }

    bOwnsAudio = 0;
    pAudio = data_ov024_02093a2c.pAudio;
    if (pAudio != 0 && pAudio->pStream == pTimer->pStream) {
        bOwnsAudio = 1;
    }
    nState = pTimer->nState;
    if (bOwnsAudio == 0) {
        pAudio = 0;
    }

    switch (nState) {
    case 0:
        return 0;

    case 1:
        pTimer->nStartTick = func_020031d4();
        if (pAudio != 0) {
            func_ov024_020840a4(pAudio);
        }
        pTimer->nState = 2;
        OS_SetAlarm(pTimer->alarm, 0, (void *)&func_ov024_0208421c, pTimer);
        /* fall through */

    case 2:
        if (func_ov024_02085014(pTimer->pStream) == 0
            || ((int *)&data_ov024_0209ba48)[0x39] != 0) {
            if (pAudio != 0) {
                SND_SetChannelVolume(3, 0, 0);
                func_020087c0(1);
            }
            pTimer->nState = 4;
            return 0;
        }
        pTimer->nState = 3;
        /* fall through */

    case 3:
        if (pTimer->nDecoded - pTimer->nConsumed < QUEUE_DEPTH) {
            func_ov024_0208435c(pTimer);
            if (pAudio != 0) {
                func_ov024_0208437c(pAudio);
            }
            pTimer->nState = 2;
        }
        return 0;

    case 4:
        if (pTimer->nDecoded <= pTimer->nConsumed) {
            pTimer->nState = 5;
        }
        return 0;

    case 5:
        if (pTimer->bPresented != 0) {
            return 0;
        }
        pTimer->nState = 6;
        func_02003618(pTimer->alarm);
        return 1;
    }
    return 1;
}
