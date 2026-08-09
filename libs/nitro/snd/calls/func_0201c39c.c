typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef int BOOL;

typedef struct SNDBinaryFileHeader {
    u32 signature;
    u16 byteOrder;
    u16 version;
    u32 fileSize;
    u16 headerSize;
    u16 dataBlocks;
} SNDBinaryFileHeader;

typedef struct SNDBinaryBlockHeader {
    u32 kind;
    u32 size;
} SNDBinaryBlockHeader;

struct SNDWaveArc;
typedef struct SNDWaveArcLink {
    struct SNDWaveArc *waveArc;
    struct SNDWaveArcLink *next;
} SNDWaveArcLink;

typedef struct SNDWaveArc {
    SNDBinaryFileHeader fileHeader;
    SNDBinaryBlockHeader blockHeader;
    SNDWaveArcLink *topLink;
    u32 reserved[7];
    u32 waveCount;
    u32 waveOffset[0];
} SNDWaveArc;

typedef struct SNDWaveData SNDWaveData;
typedef struct NNSSndHeap *NNSSndHeapHandle;
typedef void (*NNSSndHeapDisposeCallback)(void *mem, u32 size, u32 data1, u32 data2);

extern const SNDWaveData *SND_GetWaveDataAddress(const SNDWaveArc *waveArc, s32 wave);
extern u32 SND_GetWaveDataCount(const SNDWaveArc *waveArc);
extern void SND_SetWaveDataAddress(SNDWaveArc *waveArc, s32 wave, const SNDWaveData *address);
extern void DC_StoreRange(void *address, u32 size);
extern void *func_0201b9a0(NNSSndHeapHandle heap, u32 size, NNSSndHeapDisposeCallback callback, u32 data1, u32 data2);
extern s32 func_0201b6f4(u32 fileId, void *buffer, s32 size, s32 offset);
extern void func_0201c354(void *mem, u32 size, u32 data1, u32 data2);

BOOL func_0201c39c(SNDWaveArc *waveArc, int waveNo, u32 fileId, NNSSndHeapHandle heap)
{
    SNDWaveData *buffer;
    u32 len;
    u32 begin;
    u32 end;
    u32 waveCount;

    if (SND_GetWaveDataAddress(waveArc, waveNo) != 0) {
        return 1;
    }

    waveCount = SND_GetWaveDataCount(waveArc);

    {
        const SNDWaveArc *entry = (const SNDWaveArc *)((const char *)waveArc +
            (waveArc->waveCount + waveNo) * sizeof(u32));

        begin = entry->waveOffset[0];
        if (waveNo < waveCount - 1) {
            end = entry->waveOffset[1];
        } else {
            end = waveArc->fileHeader.fileSize;
        }
        len = end - begin;

        if (heap == 0) {
            return 0;
        }

        buffer = (SNDWaveData *)func_0201b9a0(
            heap,
            len + 32,
            func_0201c354,
            (u32)waveArc,
            (u32)waveNo
        );
        if (buffer == 0) {
            return 0;
        }

        if (func_0201b6f4(fileId, buffer, (s32)len, (s32)begin) != len) {
            return 0;
        }

        DC_StoreRange(buffer, len);
        SND_SetWaveDataAddress(waveArc, waveNo, buffer);

        return 1;
    }
}
