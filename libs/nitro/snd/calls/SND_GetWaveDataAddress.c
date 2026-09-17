typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef unsigned long long u64;
typedef int BOOL;
typedef int OSIntrMode;
typedef void *OSMessage;
typedef unsigned short vu16;
typedef unsigned int vu32;
typedef unsigned char vu8;

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0
#define HW_MAIN_MEM 0x02000000


/* NitroSDK SND library (ARM9 side): command interface to the ARM7 sound driver. */
typedef struct SNDCommand {
    struct SNDCommand *next;      /* 0x00 */
    u32 id;                       /* 0x04 */
    u32 arg[4];                   /* 0x08 */
} SNDCommand;

enum {
    SND_COMMAND_START_SEQ = 0,
    SND_COMMAND_STOP_SEQ = 1,
    SND_COMMAND_PREPARE_SEQ = 2,
    SND_COMMAND_START_PREPARED_SEQ = 3,
    SND_COMMAND_PAUSE_SEQ = 4,
    SND_COMMAND_CHANNEL_PAN = 0x15,
    SND_COMMAND_LOCK_CHANNEL = 0x1a,
    SND_COMMAND_UNLOCK_CHANNEL = 0x1b
};
#define SND_COMMAND_NOBLOCK 0
#define SND_COMMAND_BLOCK 1

extern void PushCommand_impl(int command, u32 arg0, u32 arg1, u32 arg2, u32 arg3);
#define PushCommand(c, a0, a1, a2, a3) PushCommand_impl((c), (u32)(a0), (u32)(a1), (u32)(a2), (u32)(a3))

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

typedef struct SNDWaveArcLink {
    struct SNDWaveArc *waveArc;
    struct SNDWaveArcLink *next;
} SNDWaveArcLink;

typedef struct SNDWaveArc {
    SNDBinaryFileHeader fileHeader;
    SNDBinaryBlockHeader blockHeader;
    SNDWaveArcLink *topLink;      /* 0x18 */
    u32 reserved[7];
    u32 waveCount;                /* 0x38 */
    u32 waveOffset[0];            /* 0x3c */
} SNDWaveArc;

typedef struct SNDWaveData SNDWaveData;

#define SND_BANK_TO_WAVEARC_MAX 4
typedef struct SNDBankData {
    SNDBinaryFileHeader fileHeader;
    SNDBinaryBlockHeader blockHeader;
    SNDWaveArcLink waveArcLink[SND_BANK_TO_WAVEARC_MAX];   /* 0x18 */
    u32 instCount;                /* 0x38 */
    u32 instOffset[0];            /* 0x3c */
} SNDBankData;

extern void SNDi_UnlockMutex_0x020084f4(void);   /* SNDi_LockMutex */
extern void SNDi_UnlockMutex_0x02008508(void);   /* SNDi_UnlockMutex */
#define SNDi_LockMutex SNDi_UnlockMutex_0x020084f4
#define SNDi_UnlockMutex SNDi_UnlockMutex_0x02008508
extern void DC_StoreRange(void *addr, u32 size);

/* SND_GetWaveDataAddress -- the wave data of entry `index` of the archive: an offset
 * below main RAM is relative to the archive, anything else is an absolute address. */
const SNDWaveData *SND_GetWaveDataAddress(const SNDWaveArc *waveArc, int index)
{
    const SNDWaveData *wave;
    u32 offset;

    SNDi_LockMutex();

    offset = waveArc->waveOffset[index];

    if (offset != 0) {
        if (offset < HW_MAIN_MEM)
            wave = (const SNDWaveData *)((u8 *)waveArc + offset);
        else
            wave = (const SNDWaveData *)offset;
    } else {
        wave = NULL;
    }

    SNDi_UnlockMutex();

    return wave;
}
