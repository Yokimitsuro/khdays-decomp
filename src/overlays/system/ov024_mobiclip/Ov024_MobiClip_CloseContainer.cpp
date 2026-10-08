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

#include "nitro/types.h"

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
    u32 *anQuantiser;       /* per-slot frame QP ring */
    void *pFilteredLuma;
    void *pFilteredChroma;
    void *apScratch[2];
    u8 pad0078[0x94 - 0x78];
    void *pIndex;
    u8 pad0098[0xa8 - 0x98];
    u32 nSlots;
};

extern "C" {

extern void Ov024_VeneerTo_NNSi_FndFreeFromDefaultHeap(void *pBlock);

void Ov024_MobiClip_CloseContainer(MobiClipDecoder *pDecoder)
{
    u32 i;
    int j;

    if (pDecoder->pReader != 0) {
        pDecoder->pReader->Close();
        delete pDecoder->pReader;
    }

    Ov024_VeneerTo_NNSi_FndFreeFromDefaultHeap(pDecoder->pFrameState);

    if (pDecoder->apLuma != 0) {
        for (i = 0; i < pDecoder->nSlots; i++) {
            Ov024_VeneerTo_NNSi_FndFreeFromDefaultHeap(pDecoder->apLuma[i]);
        }
        Ov024_VeneerTo_NNSi_FndFreeFromDefaultHeap(pDecoder->apLuma);
    }
    if (pDecoder->apChroma != 0) {
        for (i = 0; i < pDecoder->nSlots; i++) {
            Ov024_VeneerTo_NNSi_FndFreeFromDefaultHeap(pDecoder->apChroma[i]);
        }
        Ov024_VeneerTo_NNSi_FndFreeFromDefaultHeap(pDecoder->apChroma);
    }
    if (pDecoder->anQuantiser != 0) {
        Ov024_VeneerTo_NNSi_FndFreeFromDefaultHeap(pDecoder->anQuantiser);
    }
    if (pDecoder->pFilteredLuma != 0) {
        Ov024_VeneerTo_NNSi_FndFreeFromDefaultHeap(pDecoder->pFilteredLuma);
    }
    if (pDecoder->pFilteredChroma != 0) {
        Ov024_VeneerTo_NNSi_FndFreeFromDefaultHeap(pDecoder->pFilteredChroma);
    }
    for (j = 0; j < 2; j++) {
        if (pDecoder->apScratch[j] != 0) {
            Ov024_VeneerTo_NNSi_FndFreeFromDefaultHeap(pDecoder->apScratch[j]);
        }
        pDecoder->apScratch[j] = 0;
    }
    if (pDecoder->pIndex != 0) {
        Ov024_VeneerTo_NNSi_FndFreeFromDefaultHeap(pDecoder->pIndex);
    }
    if (pDecoder->pAudioTracks != 0) {
        Ov024_VeneerTo_NNSi_FndFreeFromDefaultHeap(pDecoder->pAudioTracks);
    }

    pDecoder->pReader = 0;
    pDecoder->apLuma = 0;
    pDecoder->apChroma = 0;
    pDecoder->pFilteredLuma = 0;
    pDecoder->pFilteredChroma = 0;
    pDecoder->anQuantiser = 0;
    pDecoder->pAudioTracks = 0;
    pDecoder->pIndex = 0;
}

}
