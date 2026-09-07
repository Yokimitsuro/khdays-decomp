/* MobiClip: release everything the container opener laid out.
 *
 * Closes the reader and deletes it, then frees the frame state, every luma and
 * chroma plane and the two arrays holding them, the plane table, the two
 * scratch buffers, the frame index and the audio tracks. Every pointer it
 * releases is cleared, so calling it twice is harmless.
 *
 * C++, like the rest of the stream layer: the reader is a class, the close is
 * a virtual call and the release is a plain delete whose null check is part of
 * the expression.
 */
typedef unsigned char u8;
typedef unsigned int u32;

class MobiClipReaderRef {
public:
    virtual ~MobiClipReaderRef();
    virtual int Seek(u32 nOffset);
    virtual int Read(void *pDest, u32 nSize);
    virtual int v10();
    virtual int v14();
    virtual void Close();
};

struct MobiClipDecoder {
    MobiClipReaderRef *pReader;
    u8 pad0004[0x34 - 4];
    void *pFrameState;
    u8 pad0038[0x58 - 0x38];
    void *pAudioTracks;
    void **apLuma;
    void **apChroma;
    void **apPlanes;
    void *pUnk0068;
    void *pUnk006c;
    void *apScratch[2];
    u8 pad0078[0x94 - 0x78];
    void *pIndex;
    u8 pad0098[0xa8 - 0x98];
    u32 nSlots;
};

extern "C" {

extern void WM_EndKeySharing_0x02083d00(void *pBlock);

void func_ov024_02085700(MobiClipDecoder *pDecoder)
{
    u32 i;
    int j;

    if (pDecoder->pReader != 0) {
        pDecoder->pReader->Close();
        delete pDecoder->pReader;
    }

    WM_EndKeySharing_0x02083d00(pDecoder->pFrameState);

    if (pDecoder->apLuma != 0) {
        for (i = 0; i < pDecoder->nSlots; i++) {
            WM_EndKeySharing_0x02083d00(pDecoder->apLuma[i]);
        }
        WM_EndKeySharing_0x02083d00(pDecoder->apLuma);
    }
    if (pDecoder->apChroma != 0) {
        for (i = 0; i < pDecoder->nSlots; i++) {
            WM_EndKeySharing_0x02083d00(pDecoder->apChroma[i]);
        }
        WM_EndKeySharing_0x02083d00(pDecoder->apChroma);
    }
    if (pDecoder->apPlanes != 0) {
        WM_EndKeySharing_0x02083d00(pDecoder->apPlanes);
    }
    if (pDecoder->pUnk0068 != 0) {
        WM_EndKeySharing_0x02083d00(pDecoder->pUnk0068);
    }
    if (pDecoder->pUnk006c != 0) {
        WM_EndKeySharing_0x02083d00(pDecoder->pUnk006c);
    }
    for (j = 0; j < 2; j++) {
        if (pDecoder->apScratch[j] != 0) {
            WM_EndKeySharing_0x02083d00(pDecoder->apScratch[j]);
        }
        pDecoder->apScratch[j] = 0;
    }
    if (pDecoder->pIndex != 0) {
        WM_EndKeySharing_0x02083d00(pDecoder->pIndex);
    }
    if (pDecoder->pAudioTracks != 0) {
        WM_EndKeySharing_0x02083d00(pDecoder->pAudioTracks);
    }

    pDecoder->pReader = 0;
    pDecoder->apLuma = 0;
    pDecoder->apChroma = 0;
    pDecoder->pUnk0068 = 0;
    pDecoder->pUnk006c = 0;
    pDecoder->apPlanes = 0;
    pDecoder->pAudioTracks = 0;
    pDecoder->pIndex = 0;
}

}
