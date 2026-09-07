/* MobiClip: decode one audio track's worth of samples out of the frame.
 *
 * Which decoder runs depends on the stream's audio kind: 1 and 2 hand the
 * track its own source and destination and let the codec advance the payload
 * by however much it consumed, 3 reads a per-track header once per frame and
 * then a fixed 0x80 bytes, and anything else is raw 16-bit PCM copied straight
 * out. The track index wraps at the track count, and the header flag is
 * cleared with it.
 *
 * Reports zero once this frame's samples have all been produced.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define TRACK_BYTES  0x14f8
#define PCM_BYTES    0x200
#define KIND3_BYTES  0x80

struct MobiClipFrameState {
    u8 *pPayload;
};

struct MobiClipAudioTrack {
    const u8 *pSrc;
    void *pDst;
    u8 pad0008[TRACK_BYTES - 8];
};

struct MobiClipDecoder {
    u8 pad0000[0x1c];
    u16 nAudioKind;
    u16 nAudioTracks;
    u8 pad0020[0x34 - 0x20];
    MobiClipFrameState *pFrameState;
    u8 pad0038[0x58 - 0x38];
    MobiClipAudioTrack *pAudioTracks;
    u8 pad005c[0xa4 - 0x5c];
    int bTrackHeaderPending;
    u8 pad00a8[0xc8 - 0xa8];
    int nAudioSamples;
    int nAudioDone;
    int nTrack;
};

extern "C" {

extern int func_ov024_02086958(MobiClipAudioTrack *pTrack);
extern int func_ov024_02087318_unk(MobiClipAudioTrack *pTrack);
extern void func_ov024_020867ec(MobiClipAudioTrack *pTrack, const u8 *pHeader);
extern void func_ov024_02086800(MobiClipAudioTrack *pTrack, const u8 *pSrc,
                                u32 nSize, void *pDst);
extern void MIi_CpuCopy16(const void *pSrc, void *pDst, u32 nSize);

int func_ov024_02085c8c(MobiClipDecoder *pDecoder, void *pDst)
{
    if (pDecoder->nAudioDone == pDecoder->nAudioSamples) {
        return 0;
    }
    if (pDecoder->nAudioKind == 0) {
        return 0;
    }

    if (pDecoder->nAudioKind == 1) {
        pDecoder->pAudioTracks[pDecoder->nTrack].pSrc =
            pDecoder->pFrameState->pPayload;
        pDecoder->pAudioTracks[pDecoder->nTrack].pDst = pDst;
        pDecoder->pFrameState->pPayload +=
            func_ov024_02086958(&pDecoder->pAudioTracks[pDecoder->nTrack]);
    } else if (pDecoder->nAudioKind == 2) {
        pDecoder->pAudioTracks[pDecoder->nTrack].pSrc =
            pDecoder->pFrameState->pPayload;
        pDecoder->pAudioTracks[pDecoder->nTrack].pDst = pDst;
        func_ov024_02087318_unk(&pDecoder->pAudioTracks[pDecoder->nTrack]);
        pDecoder->pFrameState->pPayload = pDecoder->pFrameState->pPayload + 0x28;
    } else if (pDecoder->nAudioKind == 3) {
        if (pDecoder->bTrackHeaderPending == 1) {
            func_ov024_020867ec(&pDecoder->pAudioTracks[pDecoder->nTrack],
                                pDecoder->pFrameState->pPayload);
            pDecoder->pFrameState->pPayload =
                pDecoder->pFrameState->pPayload + 4;
        }
        func_ov024_02086800(&pDecoder->pAudioTracks[pDecoder->nTrack],
                            pDecoder->pFrameState->pPayload, KIND3_BYTES, pDst);
        pDecoder->pFrameState->pPayload =
            pDecoder->pFrameState->pPayload + KIND3_BYTES;
    } else {
        MIi_CpuCopy16(pDecoder->pFrameState->pPayload, pDst, PCM_BYTES);
        pDecoder->pFrameState->pPayload =
            pDecoder->pFrameState->pPayload + PCM_BYTES;
    }

    pDecoder->nTrack = pDecoder->nTrack + 1;
    if (pDecoder->nTrack == pDecoder->nAudioTracks) {
        pDecoder->nTrack = 0;
        pDecoder->bTrackHeaderPending = 0;
    }
    pDecoder->nAudioDone = pDecoder->nAudioDone + 1;
    return 1;
}

}
