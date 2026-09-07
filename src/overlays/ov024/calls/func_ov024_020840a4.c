/* MobiClip: hand the decoded audio to the two hardware channels.
 *
 * The stream keeps its left and right sample buffers separate. Both are pushed
 * out of the data cache, channels 0 and 1 are taken, each is pointed at its own
 * buffer as a looping 16-bit stream, and an alarm is armed to fire every half
 * buffer so the decoder can refill the half that just played.
 */
typedef unsigned int u32;

struct MobiClipAudioStream {
    int pad0000;
    short *pLeft;
    short *pRight;
    int pad000c;
    int nSampleRate;
    int pad0014;
    u32 nBlockSamples;
    int pad001c;
    u32 nBlocks;
};

extern int func_0202060c(u32 nBase, int nSampleRate);
extern void DC_StoreRange(void *pBlock, u32 nSize);
extern void SND_LockChannel(u32 nChannelMask, u32 nLockId);
extern void SND_SetupChannelPcm(int nChannel, int nFormat, const void *pData,
                                int nLoop, int nLoopStart, int nLoopLength,
                                int nVolume, int nShift, int nTimer, int nPan);
extern void SND_SetupAlarm(int nId, int nTick, int nPeriod, void *pfn, void *pArg);
extern void SND_StartTimer(u32 nChannelMask, u32 nCaptureMask,
                           u32 nAlarmMask, u32 nFlags);
extern void func_020087c0(int nChannel);
extern void func_ov024_02084084(void);

void func_ov024_020840a4(struct MobiClipAudioStream *pStream)
{
    int nTimer;

    nTimer = func_0202060c(0x00ffb0ff, pStream->nSampleRate);
    DC_StoreRange(pStream->pLeft, (pStream->nBlocks * pStream->nBlockSamples) << 1);
    DC_StoreRange(pStream->pRight, (pStream->nBlocks * pStream->nBlockSamples) << 1);
    SND_LockChannel(3, 0);
    SND_SetupChannelPcm(0, 1, pStream->pLeft, 1, 0,
                        (pStream->nBlocks * pStream->nBlockSamples) >> 1,
                        0, 0, nTimer, 0x20);
    SND_SetupChannelPcm(1, 1, pStream->pRight, 1, 0,
                        (pStream->nBlocks * pStream->nBlockSamples) >> 1,
                        0, 0, nTimer, 0x5f);
    SND_SetupAlarm(0, nTimer * 0x64, 0, (void *)&func_ov024_02084084, 0);
    SND_StartTimer(3, 0, 1, 0);
    func_020087c0(1);
}
