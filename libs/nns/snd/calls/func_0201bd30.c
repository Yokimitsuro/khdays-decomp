typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef unsigned long long u64;
typedef long long s64;
typedef int BOOL;
typedef int OSIntrMode;
typedef void *OSMessage;
typedef volatile unsigned short vu16;
typedef volatile unsigned int vu32;
typedef volatile unsigned char vu8;

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0
#define HW_MAIN_MEM 0x02000000


#define NNS_SND_ARC_LOAD_BANK (1 << 1)
#define NNS_SND_ARC_LOAD_WAVE (1 << 2)
#define NNS_SND_ARC_INVALID_WAVEARC_NO 0xffff
#define NNS_SND_ARC_BANK_TO_WAVEARC_NUM 4
#define NNS_SND_ARC_WAVEARC_SINGLE_LOAD (1 << 0)

struct SNDBankData;
struct SNDBankData;
typedef struct SNDBinaryFileHeader {
    char signature[4];
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
    struct SNDWaveArc * waveArc;
    struct SNDWaveArcLink * next;
} SNDWaveArcLink;
typedef struct SNDWaveArc {
    struct SNDBinaryFileHeader fileHeader;
    struct SNDBinaryBlockHeader blockHeader;
    struct SNDWaveArcLink * topLink;
    u32 reserved[7];
    u32 waveCount;
    u32 waveOffset[0];
} SNDWaveArc;
typedef struct SNDBankData {
    struct SNDBinaryFileHeader fileHeader;
    struct SNDBinaryBlockHeader blockHeader;
    struct SNDWaveArcLink waveArcLink[4 ];
    u32 instCount;
    u32 instOffset[0];
} SNDBankData;
void SND_AssignWaveArc(struct SNDBankData * bank, int index, struct SNDWaveArc * waveArc);
struct SNDBankData;
typedef struct {
    void * prevObject;
    void * nextObject;
} NNSFndLink;
typedef struct {
    void * headObject;
    void * tailObject;
    u16 numObjects;
    u16 offset;
} NNSFndList;
typedef struct NNSiFndHeapHead NNSiFndHeapHead;
struct NNSiFndHeapHead {
    u32 signature;
    NNSFndLink link;
    NNSFndList childList;
    void * heapStart;
    void * heapEnd;
    u32 attribute;
};
typedef NNSiFndHeapHead * NNSFndHeapHandle;
typedef void (*NNSFndHeapVisitor)(void * memBlock, NNSFndHeapHandle heap, u32 userParam);
typedef int (*MIDeviceReadFunction)(void * userdata, void * buffer, u32 offset, u32 length);
typedef int (*MIDeviceWriteFunction)(void * userdata, const void * buffer, u32 offset, u32 length);
struct NNSSndHeap;
typedef void (*NNSSndHeapDisposeCallback)(void * mem, u32 size, u32 data1, u32 data2);
typedef struct NNSSndHeap * NNSSndHeapHandle;
struct SNDBankData;
struct SNDWaveArc;
typedef enum NNSSndArcLoadResult {
    NNS_SND_ARC_LOAD_SUCESS = 0,
    NNS_SND_ARC_LOAD_ERROR_INVALID_GROUP_NO,
    NNS_SND_ARC_LOAD_ERROR_INVALID_SEQ_NO,
    NNS_SND_ARC_LOAD_ERROR_INVALID_SEQARC_NO,
    NNS_SND_ARC_LOAD_ERROR_INVALID_BANK_NO,
    NNS_SND_ARC_LOAD_ERROR_INVALID_WAVEARC_NO,
    NNS_SND_ARC_LOAD_ERROR_FAILED_LOAD_SEQ,
    NNS_SND_ARC_LOAD_ERROR_FAILED_LOAD_SEQARC,
    NNS_SND_ARC_LOAD_ERROR_FAILED_LOAD_BANK,
    NNS_SND_ARC_LOAD_ERROR_FAILED_LOAD_WAVE
} NNSSndArcLoadResult;
NNSSndArcLoadResult func_0201be70(int waveArcNo, u32 loadFlag, NNSSndHeapHandle heap, BOOL bSetAddr, struct SNDWaveArc ** pData);
typedef struct NNSSndArcBankInfo {
    u32 fileId;
    u16 waveArcNo[4 ];
} NNSSndArcBankInfo;
typedef struct NNSSndArcWaveArcInfo {
    u32 fileId :24;
    u32 flags  :8;
} NNSSndArcWaveArcInfo;
const NNSSndArcBankInfo * func_0201b4b0(int bankNo);
const NNSSndArcWaveArcInfo * func_0201b514(int waveArcNo);
void * func_0201b7e0(u32 fileId);
extern SNDBankData * func_0201c074(u32 fileId, NNSSndHeapHandle heap, BOOL bSetAddr);
extern BOOL func_0201c464(SNDWaveArc * waveArc, const SNDBankData * bank, int waveArcNo, u32 fileId, NNSSndHeapHandle heap);
extern NNSSndArcLoadResult func_0201be70 (int waveArcNo, u32 loadFlag, NNSSndHeapHandle heap, BOOL bSetAddr, struct SNDWaveArc ** pData);
extern SNDBankData * func_0201c074 (u32 fileId, NNSSndHeapHandle heap, BOOL bSetAddr);
extern BOOL func_0201c464 (SNDWaveArc * waveArc, const SNDBankData * bank, int waveArcNo, u32 fileId, NNSSndHeapHandle heap);

/* func_0201bd30 -- NitroSystem sndarc_loader.c: NNSi_SndArcLoadBank. */
NNSSndArcLoadResult func_0201bd30 (int bankNo, u32 loadFlag, NNSSndHeapHandle heap, BOOL bSetAddr, struct SNDBankData ** pData)
{
    const NNSSndArcBankInfo * bankInfo;
    const NNSSndArcWaveArcInfo * waveArcInfo;
    SNDBankData * bank = NULL;
    SNDWaveArc * waveArc;
    NNSSndArcLoadResult result;
    int i;

    bankInfo = func_0201b4b0(bankNo);
    if (bankInfo == NULL) return NNS_SND_ARC_LOAD_ERROR_INVALID_BANK_NO;

    if (loadFlag & NNS_SND_ARC_LOAD_BANK) {
        bank = func_0201c074(bankInfo->fileId, heap, bSetAddr);
        if (bank == NULL) {
            return NNS_SND_ARC_LOAD_ERROR_FAILED_LOAD_BANK;
        }
    } else {
        bank = (SNDBankData *)func_0201b7e0(bankInfo->fileId);
    }

    for (i = 0; i < NNS_SND_ARC_BANK_TO_WAVEARC_NUM; i++) {
        if (bankInfo->waveArcNo[i] == NNS_SND_ARC_INVALID_WAVEARC_NO) continue;

        waveArcInfo = func_0201b514(bankInfo->waveArcNo[i]);
        if (waveArcInfo == NULL) return NNS_SND_ARC_LOAD_ERROR_INVALID_WAVEARC_NO;

        result = func_0201be70(bankInfo->waveArcNo[i], loadFlag, heap, bSetAddr, &waveArc);
        if (result != NNS_SND_ARC_LOAD_SUCESS) return result;

        if (waveArcInfo->flags & NNS_SND_ARC_WAVEARC_SINGLE_LOAD) {

            if (loadFlag & NNS_SND_ARC_LOAD_WAVE) {
                if (!func_0201c464(waveArc, bank, i, waveArcInfo->fileId, heap)) {
                    return NNS_SND_ARC_LOAD_ERROR_FAILED_LOAD_WAVE;
                }
            }
        }

        if (bank != NULL && waveArc != NULL) {
            SND_AssignWaveArc(bank, i, waveArc);
        }
    }

    if (pData != NULL) *pData = bank;

    return NNS_SND_ARC_LOAD_SUCESS;
}
