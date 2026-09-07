/* MobiClip: hand the next frame to the decoder and queue the one after it.
 *
 * Flips the double-buffered read parity, waits for the read that was already
 * in flight, and splits the word at the head of that buffer into the next
 * frame's size and its offset. The frame state is pointed at the payload, the
 * six reference planes are rebound through the lead table, and -- unless this
 * was the last frame -- the read for the following frame is started into the
 * other buffer.
 *
 * Reports zero once the frame index has caught up with the frame count.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define OFFSET_MASK 0x3fff
#define PLANE_SLOTS 6

class MobiClipReaderRef {
public:
    virtual ~MobiClipReaderRef();
    virtual int Seek(u32 nOffset);
    virtual int Read(void *pDest, u32 nSize);
    virtual int StartRead(void *pDest, u32 nSize);
    virtual void WaitRead();
    virtual void Close();
};

struct MobiClipFrameState {
    void *pPayload;
    u8 pad0004[8];
    void *apLuma[PLANE_SLOTS];
    void *apChroma[PLANE_SLOTS];
};

struct MobiClipDecoder {
    MobiClipReaderRef *pReader;
    u8 pad0004[8];
    int nFrameCount;
    u8 pad0010[0x1e - 0x10];
    u16 nAudioTracks;
    u8 pad0020[0x34 - 0x20];
    MobiClipFrameState *pFrameState;
    u8 pad0038[0x5c - 0x38];
    void **apLuma;
    void **apChroma;
    u8 pad0064[0x70 - 0x64];
    u8 *apScratch[2];
    int anChunkSize[2];
    int anReadOffset[2];
    int anChunkOffset[2];
    int nParity;
    void *pIndex;
    int nFrameIndex;
    u8 pad009c[0xac - 0x9c];
    int anLead[PLANE_SLOTS];
    u8 pad00c4[4];
    int nAudioSamples;
};

extern "C" {

int func_ov024_0208589c(MobiClipDecoder *pDecoder)
{
    int nPrev;
    u32 nWord;
    int i;

    if (pDecoder->nFrameIndex == pDecoder->nFrameCount) {
        return 0;
    }
    pDecoder->nFrameIndex = pDecoder->nFrameIndex + 1;

    nPrev = pDecoder->nParity;
    pDecoder->nParity = (nPrev + 1) % 2;
    pDecoder->pReader->WaitRead();

    nWord = *(u32 *)(pDecoder->apScratch[pDecoder->nParity]
                     + (pDecoder->anReadOffset[pDecoder->nParity]
                        + pDecoder->anChunkSize[pDecoder->nParity]));
    pDecoder->anChunkSize[nPrev] = nWord >> 14;
    pDecoder->anChunkOffset[nPrev] = nWord & OFFSET_MASK;

    pDecoder->pFrameState->pPayload =
        pDecoder->apScratch[pDecoder->nParity]
        + pDecoder->anReadOffset[pDecoder->nParity];

    if ((u32)pDecoder->nFrameIndex < (u32)pDecoder->nFrameCount) {
        pDecoder->anReadOffset[nPrev] = pDecoder->pReader->StartRead(
            pDecoder->apScratch[nPrev], pDecoder->anChunkSize[nPrev] + 4);
    }

    for (i = 0; i < PLANE_SLOTS; i++) {
        pDecoder->pFrameState->apLuma[i] = pDecoder->apLuma[pDecoder->anLead[i]];
        pDecoder->pFrameState->apChroma[i] = pDecoder->apChroma[pDecoder->anLead[i]];
    }

    pDecoder->nAudioSamples =
        pDecoder->nAudioTracks * pDecoder->anChunkOffset[pDecoder->nParity];
    return 1;
}

}
