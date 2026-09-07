/* MobiClip: open up to three streams and start everything that drives them.
 *
 * Takes a slot for each stream the request names, opens each one's file,
 * gives the first stream that carries audio a ring of its own, works out how
 * many ticks a frame is worth on each slot, arms every slot's alarm and primes
 * its decoder, and finally installs the vertical-blank presenter.
 *
 * If no slot could be taken, or any file failed to open, everything taken so
 * far is handed back and the caller is told the movie will not play.
 */
typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef long long s64;

#define TICK_BASE   0x00ffb0ffu
#define FRAME_TRIES 10
#define RING_FRAMES 10

struct MobiClipOpenRequest {
    const char *pszStream0;
    const char *pszStream1;
    const char *pszStream2;
    void *pfnFrameReady;
};

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
    int nDecoded;
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

typedef u8 MobiClipFile[0x48];

struct MobiClipFileBank {
    MobiClipFile aFiles[3];
    u8 pad00d8[0x80e0 - 3 * 0x48];
    void *pfnFrameReady;
};

extern struct MobiClipFileBank data_ov024_02093a48;
extern int data_ov024_0209ba48;
extern struct MobiClipGlobals data_ov024_02093a2c;
extern int data_ov024_020939ac;
extern struct MobiClipFrameTimer *data_ov024_02093a3c[3];

extern void FS_InitFile(void *pFile);
extern void MI_CpuFill8(void *pDest, int nValue, u32 nSize);
extern void DC_StoreAll(void);
extern void *NNS_FndAllocFromDefaultExpHeapEx(u32 nSize, int nAlignment);
extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern void OS_CreateAlarm(void *pAlarm);
extern void OS_WaitVBlankIntr(void);
extern struct MobiClipFrameTimer *func_ov024_02084650(int nSlot, const char *pszPath);
extern void func_ov024_0208455c(void);
extern void *func_ov024_02084ec4(void *pFile, int nTries);
extern u32 func_ov024_02084ffc(void *pStream);
extern u32 func_ov024_02084fcc(void *pStream);
extern u32 func_ov024_02084fe4(void *pStream);
extern void func_ov024_02085014(void *pStream);
extern void func_ov024_0208435c(struct MobiClipFrameTimer *pTimer);
extern void func_ov024_0208437c(struct MobiClipAudioStream *pAudio);
extern void func_ov024_02084608(void);
extern void func_ov024_02084054(void);
extern void func_ov024_0208406c(void);
extern void func_ov024_02084438(void);
extern void func_02003380(void);
extern void func_02000f48(int nSlot, void *pTable, void *pfn);

int func_ov024_020846c0(struct MobiClipOpenRequest *pRequest)
{
    struct MobiClipFrameTimer *apSlots[3];
    struct MobiClipAudioStream *pAudio;
    struct MobiClipFileBank *pBank;
    u64 nTicks;
    u64 nUnit;
    int i;
    int j;

    pBank = &data_ov024_02093a48;
    ((int *)&data_ov024_0209ba48)[0x39] = 0;
    for (i = 0; i < 3; i++) {
        FS_InitFile(pBank->aFiles[i]);
        apSlots[i] = 0;
    }

    if (pRequest->pszStream0 != 0) {
        apSlots[0] = func_ov024_02084650(0, pRequest->pszStream0);
        data_ov024_02093a2c.pMain = apSlots[0];
    }
    if (pRequest->pszStream1 != 0) {
        apSlots[1] = func_ov024_02084650(1, pRequest->pszStream1);
        data_ov024_02093a2c.pSub = apSlots[1];
    }
    if (pRequest->pszStream2 != 0) {
        apSlots[2] = func_ov024_02084650(2, pRequest->pszStream2);
    }
    if (apSlots[0] == 0 && apSlots[1] == 0 && apSlots[2] == 0) {
        return 0;
    }

    func_ov024_0208455c();
    if (apSlots[0] != 0) {
        apSlots[0]->pfnBufferForIndex = (void *)&func_ov024_02084054;
    }
    if (apSlots[1] != 0) {
        apSlots[1]->pfnBufferForIndex = (void *)&func_ov024_0208406c;
    }
    if (apSlots[2] != 0) {
        apSlots[2]->pfnBufferForIndex = (void *)&func_ov024_0208406c;
    }
    pBank->pfnFrameReady = pRequest->pfnFrameReady;

    for (i = 0; i < 3; i++) {
        if (apSlots[i] != 0) {
            apSlots[i]->pStream =
                func_ov024_02084ec4(pBank->aFiles[i], FRAME_TRIES);
            if (apSlots[i]->pStream == 0) {
                goto failed;
            }
        }
    }

    data_ov024_02093a2c.pAudio = 0;
    for (i = 0; i < 2; i++) {
        u32 nChannels;

        if (apSlots[i] != 0
            && (nChannels = func_ov024_02084ffc(apSlots[i]->pStream)) != 0) {
            data_ov024_02093a2c.pAudio =
                (struct MobiClipAudioStream *)
                NNS_FndAllocFromDefaultExpHeapEx(0x24, 0x20);
            MI_CpuFill8(data_ov024_02093a2c.pAudio, 0, 0x24);
            data_ov024_02093a2c.pAudio->pStream = apSlots[i]->pStream;
            data_ov024_02093a2c.pAudio->nChannels = nChannels;
            break;
        }
    }

    pAudio = data_ov024_02093a2c.pAudio;
    if (pAudio != 0) {
        u64 nRate;

        pAudio->nSampleRate = func_ov024_02084fcc(pAudio->pStream);
        nRate = TICK_BASE / (u64)(TICK_BASE / (u64)pAudio->nSampleRate);
        pAudio->nFrameSamples =
            (u32)((nRate << 24)
                  / ((u64)pAudio->nChannels * func_ov024_02084fe4(pAudio->pStream)))
            + 1;
        pAudio->nBlocks = pAudio->nFrameSamples * RING_FRAMES;
        pAudio->pLeft = (short *)NNS_FndAllocFromDefaultExpHeapEx(
            (pAudio->nBlocks * pAudio->nChannels) << 1, 0x20);
        pAudio->pRight = (short *)NNS_FndAllocFromDefaultExpHeapEx(
            (pAudio->nBlocks * pAudio->nChannels) << 1, 0x20);
        MI_CpuFill8(pAudio->pLeft, 0, (pAudio->nBlocks * pAudio->nChannels) << 1);
        MI_CpuFill8(pAudio->pRight, 0, (pAudio->nBlocks * pAudio->nChannels) << 1);
        DC_StoreAll();
    }

    for (i = 0; i < 3; i++) {
        if (apSlots[i] == 0) {
            continue;
        }
        if (pAudio != 0 && pAudio->pStream == apSlots[i]->pStream) {
            nUnit = TICK_BASE / (u64)pAudio->nSampleRate;
            nTicks = (u64)func_ov024_02084fe4(pAudio->pStream) * TICK_BASE
                     / (nUnit * pAudio->nSampleRate);
            apSlots[i]->nTimeBase = nTicks;
            pAudio->nFilled = 0;
        } else {
            apSlots[i]->nTimeBase = func_ov024_02084fe4(apSlots[i]->pStream);
        }
        apSlots[i]->nFrontBuffer = 0;
        apSlots[i]->bPresented = 1;
        func_02003380();
        OS_CreateAlarm(apSlots[i]->alarm);
        apSlots[i]->nConsumed = 0;
        apSlots[i]->nDecoded = 0;
        apSlots[i]->nPresented = 0;
        apSlots[i]->nState = 0;
        for (j = 0; j < RING_FRAMES; j++) {
            func_ov024_02085014(apSlots[i]->pStream);
            func_ov024_0208435c(apSlots[i]);
            if (pAudio != 0 && pAudio->pStream == apSlots[i]->pStream) {
                func_ov024_0208437c(pAudio);
            }
        }
    }

    data_ov024_02093a2c.bStopped = 0;
    func_02000f48(1, &data_ov024_020939ac, (void *)&func_ov024_02084438);
    OS_WaitVBlankIntr();
    return 1;

failed:
    func_ov024_02084608();
    for (i = 0; i < 3; i++) {
        if (apSlots[i] != 0) {
            NNSi_FndFreeFromDefaultHeap(apSlots[i]);
            data_ov024_02093a3c[i] = 0;
        }
    }
    return 0;
}
