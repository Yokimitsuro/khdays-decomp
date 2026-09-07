/* MobiClip: stop playback and hand everything back.
 *
 * Unless a stop is already under way, both screens are asked to finish what
 * they are showing before anything is released. Then every slot's alarm is
 * cancelled, the vertical-blank presenter is uninstalled, the audio ring and
 * its two channel buffers are freed, and each slot has its stream closed, its
 * file closed and the slot itself released.
 */
typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef long long s64;

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
    int bStopping;
};

extern struct MobiClipFileBank data_ov024_02093a48;
extern int data_ov024_0209ba48;
extern struct MobiClipGlobals data_ov024_02093a2c;
extern struct MobiClipFrameTimer *data_ov024_02093a3c[3];
extern int data_ov024_020939ac;

extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern void FS_CloseFile(void *pFile);
extern int func_ov024_02084c24(struct MobiClipFrameTimer *pTimer);
extern void func_ov024_020841c4(void);
extern void func_ov024_02084fac(void *pStream);
extern void func_ov024_02084608(void);
extern void func_02003618(void *pAlarm);
extern void func_020033c0(void);
extern void func_02000fb4(int nSlot, void *pTable);

void func_ov024_02084b14(void)
{
    struct MobiClipFileBank *pBank;
    struct MobiClipFrameTimer **apSlots;
    struct MobiClipAudioStream *pAudio;
    int bMain;
    int bSub;
    int i;

    pAudio = data_ov024_02093a2c.pAudio;
    pBank = &data_ov024_02093a48;
    apSlots = data_ov024_02093a3c;
    if (((int *)&data_ov024_0209ba48)[0x39] == 0) {
        pBank->bStopping = 1;
        do {
            bMain = func_ov024_02084c24(data_ov024_02093a2c.pMain);
            bSub = func_ov024_02084c24(data_ov024_02093a2c.pSub);
        } while ((bMain & bSub) != 0);
    }

    for (i = 0; i < 3; i++) {
        if (apSlots[i] != 0) {
            func_02003618(apSlots[i]->alarm);
        }
    }
    func_020033c0();
    func_02000fb4(1, &data_ov024_020939ac);

    if (pAudio != 0) {
        func_ov024_020841c4();
        NNSi_FndFreeFromDefaultHeap(pAudio->pLeft);
        NNSi_FndFreeFromDefaultHeap(pAudio->pRight);
        NNSi_FndFreeFromDefaultHeap(pAudio);
        data_ov024_02093a2c.pAudio = 0;
    }

    for (i = 0; i < 3; i++) {
        if (apSlots[i] != 0) {
            func_ov024_02084fac(apSlots[i]->pStream);
            FS_CloseFile(pBank->aFiles[i]);
            NNSi_FndFreeFromDefaultHeap(data_ov024_02093a3c[i]);
            data_ov024_02093a3c[i] = 0;
        }
    }
    func_ov024_02084608();
}
