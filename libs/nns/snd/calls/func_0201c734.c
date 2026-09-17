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


#define NNS_SND_ARC_LOAD_SEQ (1 << 0)
#define NNS_SND_ARC_LOAD_BANK (1 << 1)
#define NNS_SND_ARC_LOAD_WAVE (1 << 2)

typedef enum {
    SND_DUTY_1_8,
    SND_DUTY_2_8,
    SND_DUTY_3_8,
    SND_DUTY_4_8,
    SND_DUTY_5_8,
    SND_DUTY_6_8,
    SND_DUTY_7_8
} SNDDuty;
struct SNDExChannel;
typedef enum SNDExChannelCallbackStatus {
    SND_EX_CHANNEL_CALLBACK_DROP,
    SND_EX_CHANNEL_CALLBACK_FINISH
} SNDExChannelCallbackStatus;
typedef void (*SNDExChannelCallback) (struct SNDExChannel * ch_p, SNDExChannelCallbackStatus status, void * userData);
typedef struct SNDWaveParam {
        u8 format;
        u8 loopflag;
        u16 rate;
        u16 timer;
        u16 loopstart;
        u32 looplen;
    } SNDWaveParam;
typedef struct SNDLfoParam {
    u8 target;
    u8 speed;
    u8 depth;
    u8 range;
    u16 delay;
} SNDLfoParam;
typedef struct SNDLfo {
    struct SNDLfoParam param;
    u16 delay_counter;
    u16 counter;
} SNDLfo;
typedef struct SNDExChannel {
    u8 myNo;
    u8 type;
    u8 env_status;
    u8 active_flag : 1;
    u8 start_flag : 1;
    u8 auto_sweep : 1;
    u8 sync_flag : 5;
    u8 pan_range;
    u8 original_key;
    s16 user_decay2;
    u8 key;
    u8 velocity;
    s8 init_pan;
    s8 user_pan;
    s16 user_decay;
    s16 user_pitch;
    s32 env_decay;
    s32 sweep_counter;
    s32 sweep_length;
    u8 attack;
    u8 sustain;
    u16 decay;
    u16 release;
    u8 prio;
    u8 pan;
    u16 volume;
    u16 timer;
    struct SNDLfo lfo;
    s16 sweep_pitch;
    s32 length;
    struct SNDWaveParam wave;
    union {
        const void * data;
        SNDDuty duty;
    };
    SNDExChannelCallback callback;
    void * callback_data;
    struct SNDExChannel * nextLink;
} SNDExChannel;
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
struct SNDExChannel;
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
struct NNSSndHandle;
typedef struct NNSSndSeqParam {
    u16 bankNo;
    u8 volume;
    u8 channelPrio;
    u8 playerPrio;
    u8 playerNo;
    u16 reserved;
} NNSSndSeqParam;
typedef struct NNSSndSeqData {
    struct SNDBinaryFileHeader fileHeader;
    struct SNDBinaryBlockHeader blockHeader;
    u32 baseOffset;
    u32 data[0];
} NNSSndSeqData;
typedef struct NNSSndArcSeqInfo {
    u32 fileId;
    struct NNSSndSeqParam param;
} NNSSndArcSeqInfo;
typedef struct NNSSndFader {
    int origin;
    int target;
    int counter;
    int frame;
} NNSSndFader;
struct SNDBankData;
struct NNSSndSeqPlayer;
struct NNSSndPlayer;
struct NNSSndPlayerHeap;
typedef struct NNSSndHandle {
    struct NNSSndSeqPlayer * player;
} NNSSndHandle;
typedef struct NNSSndSeqPlayer {
    struct NNSSndHandle * handle;
    struct NNSSndPlayer * player;
    struct NNSSndPlayerHeap * heap;
    NNSFndLink playerLink;
    NNSFndLink prioLink;
    NNSSndFader fader;
    u8 status;
    u8 startFlag;
    u8 pauseFlag;
    u8 prepareFlag;
    u32 commandTag;
    u16 seqType;
    u16 pad2;
    u16 seqNo;
    u16 seqArcIndex;
    u8 playerNo;
    u8 prio;
    s16 volume;
    u8 initVolume;
    u8 extVolume;
    u16 pad3_;
} NNSSndSeqPlayer;
typedef struct NNSSndPlayer {
    NNSFndList playerList;
    NNSFndList heapList;
    u32 playableSeqCount;
    u32 allocChBitFlag;
    u8 volume;
    u8 pad_;
    u16 pad2_;
} NNSSndPlayer;
void func_0201a110(NNSSndHandle * handle, int volume);
void func_0201a150(NNSSndHandle * handle, int priority);
void func_0201a1c0(NNSSndHandle * handle, int seqNo);
void func_0201a568(NNSSndSeqPlayer * seqPlayer, const void * seqDataBase, u32 seqDataOffset, const struct SNDBankData * bank);
NNSSndSeqPlayer * func_0201a4c4(NNSSndHandle * handle, int playerNo, int prio);
void WM_EndKeySharing_0x0201a55c(NNSSndSeqPlayer * seqPlayer);
NNSSndHeapHandle func_0201a62c(int playerNo, NNSSndSeqPlayer * seqPlayer);
struct NNSSndSeqData;
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
NNSSndArcLoadResult func_0201bc4c(int seqNo, u32 loadFlag, NNSSndHeapHandle heap, BOOL bSetAddr, struct NNSSndSeqData ** pData);
NNSSndArcLoadResult func_0201bd30(int bankNo, u32 loadFlag, NNSSndHeapHandle heap, BOOL bSetAddr, struct SNDBankData ** pData);

/* func_0201c734 -- NitroSystem sndarc_player.c: StartSeq. */
BOOL func_0201c734 (NNSSndHandle * handle, int playerNo, int bankNo, int playerPrio, const NNSSndArcSeqInfo * info, int seqNo)
{
    NNSSndSeqPlayer * player;
    NNSSndHeapHandle heap;
    NNSSndSeqData * seq;
    SNDBankData * bank;
    NNSSndArcLoadResult result;


    player = func_0201a4c4(handle, playerNo, playerPrio);
    if (player == NULL) return FALSE;

    heap = func_0201a62c(playerNo, player);

    result = func_0201bd30(bankNo, NNS_SND_ARC_LOAD_BANK | NNS_SND_ARC_LOAD_WAVE, heap, FALSE, &bank);
    if (result != NNS_SND_ARC_LOAD_SUCESS) {
        WM_EndKeySharing_0x0201a55c(player);
        return FALSE;
    }

    result = func_0201bc4c(seqNo, NNS_SND_ARC_LOAD_SEQ, heap, FALSE, &seq);
    if (result != NNS_SND_ARC_LOAD_SUCESS) {
        WM_EndKeySharing_0x0201a55c(player);
        return FALSE;
    }

    func_0201a568(
        player,
        (u8 *)seq + seq->baseOffset,
        0,
        bank
        );

    func_0201a110(handle, info->param.volume);
    func_0201a150(handle, info->param.channelPrio);
    func_0201a1c0(handle, seqNo);

    return TRUE;
}
