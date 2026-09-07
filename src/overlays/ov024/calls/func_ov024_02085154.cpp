/* MobiClip: read a container header and lay out everything the decoder needs.
 *
 * Checks the "MODSN" signature and the version -- 2 or 3, where 3 carries a
 * chunk directory that is walked until the "HE" terminator -- then allocates
 * the frame state, the per-slot luma and chroma planes, the two scratch
 * buffers, the audio ring when the stream has sound, and the frame index.
 * Reports zero on the first read or allocation that fails.
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;

#define HEADER_BYTES  0x30
#define MAX_WIDTH     0x100
#define MIN_SLOTS     6
#define FRAME_STATE   0x454
#define AUDIO_TRACK   0x14f8
#define CHUNK_BYTES   0xc34
#define OFFSET_MASK   0x3fff

class MobiClipReaderRef {
public:
    virtual ~MobiClipReaderRef();
    virtual int Seek(u32 nOffset);
    virtual int Read(void *pDest, u32 nSize);

    int pad0004;
    u32 nBase;
};

struct MobiClipAudioTrack {
    u8 pad0000[0x1cc];
    int nDecodeState;
    u8 pad01d0[0x8c0 - 0x1d0];
    u8 aChunk[CHUNK_BYTES];
    int nChunkState;
};

struct MobiClipDecoder {
    MobiClipReaderRef *pReader;
    s8 szSignature[5];
    s8 nVersion;
    u16 nHeaderWords;
    int pad000c;
    u32 nWidth;
    u32 nHeight;
    int pad0018;
    u16 nAudioKind;
    u16 nAudioTracks;
    int pad0020;
    int nScratchBytes;
    u32 nAudioOffset;
    u32 nIndexOffset;
    int nIndexEntries;
    void *pFrameState;
    void *pQuantTables;
    int pad003c[4];
    int nPlaneWidth;
    int nPlaneHeight;
    void *pMotion;
    void *pAudioRing;
    void **apLuma;
    void **apChroma;
    void **apPlanes;
    int pad0068[2];
    void *apScratch[2];
    u32 nFirstChunk;
    int pad007c;
    int pad0080;
    int pad0084;
    u32 nFirstOffset;
    int pad008c;
    int nReady;
    void *pIndex;
    int nAllocated;
    int pad009c;
    int pad00a0;
    int pad00a4;
    u32 nSlots;
    int anLead[6];
    int pad00c4;
    int pad00c8[3];
    u32 nBase;
};

extern "C" {

extern u8 data_ov024_020886c4[];

extern void *func_ov024_02083cf0(u32 nSize);
extern void MIi_CpuClearFast(u32 nValue, void *pDest, u32 nSize);
extern void MI_CpuFill8(void *pDest, int nValue, u32 nSize);
extern void *func_ov024_02086620(void);
extern void *func_ov024_0208669c(void);
extern void *func_ov024_0208677c(void);
extern void *func_ov024_0208670c(void);

int func_ov024_02085154(MobiClipDecoder *pDecoder,
                        MobiClipReaderRef *pReader, u32 nSlots)
{
    u16 nChunkTag;
    u16 nChunkSkip;
    u32 nFirst;
    u32 nHome;
    u32 nSeek;
    u32 i;
    int j;
    int k;
    u32 nAudioHome;
    int m;

    pDecoder->pReader = pReader;
    pDecoder->nBase = pReader->nBase;
    if (pDecoder->pReader->Read(pDecoder->szSignature,
                                            HEADER_BYTES) == 0) {
        return 0;
    }

    if (pDecoder->szSignature[0] != 'M' || pDecoder->szSignature[1] != 'O'
        || pDecoder->szSignature[2] != 'D' || pDecoder->szSignature[3] != 'S'
        || pDecoder->szSignature[4] != 'N'
        || (pDecoder->nVersion != '2' && pDecoder->nVersion != '3')
        || pDecoder->nHeaderWords != 10) {
        return 0;
    }

    if (pDecoder->szSignature[4] == 'N' && pDecoder->nVersion == '3') {
        do {
            if (pDecoder->pReader->Read(&nChunkTag, 2) == 0) {
                return 0;
            }
            if (pDecoder->pReader->Read(&nChunkSkip, 2) == 0) {
                return 0;
            }
            nSeek = (nChunkSkip << 2) + pDecoder->pReader->nBase;
            if (pDecoder->pReader->Seek(nSeek) == 0) {
                return 0;
            }
        } while (((s8 *)&nChunkTag)[0] != 'H' || ((s8 *)&nChunkTag)[1] != 'E');
    }

    if (pDecoder->nAudioKind != 0 && pDecoder->nAudioKind != 1
        && pDecoder->nAudioKind != 2 && pDecoder->nAudioKind != 3
        && pDecoder->nAudioKind != 4) {
        return 0;
    }

    pDecoder->pFrameState = func_ov024_02083cf0(FRAME_STATE);
    MIi_CpuClearFast(0, pDecoder->pFrameState, FRAME_STATE);
    pDecoder->pQuantTables = func_ov024_02086620();
    ((void **)pDecoder->pFrameState)[0xf] = func_ov024_0208669c();
    ((void **)pDecoder->pFrameState)[0x10] = data_ov024_020886c4;
    ((void **)pDecoder->pFrameState)[0x11] =
        (u8 *)func_ov024_0208677c() + 0x40;
    pDecoder->nPlaneWidth = pDecoder->nWidth;
    pDecoder->nPlaneHeight = pDecoder->nHeight;
    pDecoder->pMotion = func_ov024_0208670c();
    ((int *)pDecoder->pFrameState)[1] = pDecoder->nWidth;
    ((int *)pDecoder->pFrameState)[2] = pDecoder->nHeight;
    if ((u32)pDecoder->nWidth > MAX_WIDTH) {
        return 0;
    }
    if (nSlots < MIN_SLOTS) {
        return 0;
    }

    pDecoder->nSlots = nSlots;
    pDecoder->apLuma = (void **)func_ov024_02083cf0(nSlots << 2);
    if (pDecoder->apLuma == 0) {
        return 0;
    }
    pDecoder->apChroma = (void **)func_ov024_02083cf0(pDecoder->nSlots << 2);
    if (pDecoder->apChroma == 0) {
        return 0;
    }

    for (i = 0; i < pDecoder->nSlots; i++) {
        pDecoder->apLuma[i] = func_ov024_02083cf0(pDecoder->nHeight << 8);
        if (pDecoder->apLuma[i] == 0) {
            return 0;
        }
        pDecoder->apChroma[i] = func_ov024_02083cf0((pDecoder->nHeight >> 1) << 8);
        if (pDecoder->apChroma[i] == 0) {
            return 0;
        }
        MIi_CpuClearFast(0, pDecoder->apLuma[i], pDecoder->nHeight << 8);
        MI_CpuFill8(pDecoder->apChroma[i], 0x80, (pDecoder->nHeight >> 1) << 8);
    }

    pDecoder->apPlanes = (void **)func_ov024_02083cf0(pDecoder->nSlots << 2);
    if (pDecoder->apPlanes == 0) {
        return 0;
    }
    pDecoder->nAllocated = 0;
    pDecoder->anLead[0] = 0;
    for (j = 1; j < MIN_SLOTS; j++) {
        pDecoder->anLead[j] = pDecoder->nSlots - j;
    }

    pDecoder->pad00c4 = 0;
    pDecoder->pad00a0 = 0;
    pDecoder->pad009c = 0;
    for (j = 0; j < 2; j++) {
        pDecoder->apScratch[j] =
            func_ov024_02083cf0(pDecoder->nScratchBytes + 0x400);
        if (pDecoder->apScratch[j] == 0) {
            return 0;
        }
    }

    if (pDecoder->nAudioKind != 0) {
        pDecoder->pAudioRing =
            func_ov024_02083cf0(pDecoder->nAudioTracks * sizeof(MobiClipAudioTrack));
        if (pDecoder->pAudioRing == 0) {
            return 0;
        }
        MIi_CpuClearFast(0, pDecoder->pAudioRing,
                         pDecoder->nAudioTracks * sizeof(MobiClipAudioTrack));
    }

    nHome = pDecoder->pReader->nBase;
    nSeek = pDecoder->nIndexOffset + pDecoder->nBase;
    pDecoder->pReader->Seek(nSeek);
    pDecoder->pIndex = func_ov024_02083cf0(pDecoder->nIndexEntries << 3);
    if (pDecoder->pReader->Read(pDecoder->pIndex,
                                            pDecoder->nIndexEntries << 3) == 0) {
        return 0;
    }
    pDecoder->pReader->Seek(nHome);

    if (pDecoder->nAudioKind == 1) {
        nAudioHome = pDecoder->pReader->nBase;
        nSeek = pDecoder->nAudioOffset + pDecoder->nBase;
        pDecoder->pReader->Seek(nSeek);
        for (k = 0; k < (int)pDecoder->nAudioTracks; k++) {
            if (pDecoder->pReader->Read(
                    ((MobiClipAudioTrack *)pDecoder->pAudioRing)[k].aChunk,
                    CHUNK_BYTES) == 0) {
                return 0;
            }
            ((MobiClipAudioTrack *)pDecoder->pAudioRing)[k].nChunkState = 2;
        }
        pDecoder->pReader->Seek(nAudioHome);
    } else if (pDecoder->nAudioKind == 2) {
        for (m = 0; m < (int)pDecoder->nAudioTracks; m++) {
            ((MobiClipAudioTrack *)pDecoder->pAudioRing)[m].nDecodeState = 2;
        }
    }

    pDecoder->pReader->Read(&nFirst, 4);
    pDecoder->nFirstChunk = nFirst >> 14;
    pDecoder->nFirstOffset = nFirst & OFFSET_MASK;
    pDecoder->pad0080 = 0;
    pDecoder->pReader->Read(pDecoder->apScratch[0],
                                        pDecoder->nFirstChunk + 4);
    pDecoder->nReady = 1;
    return 1;
}

}
