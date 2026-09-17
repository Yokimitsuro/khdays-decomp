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


/* NitroSDK SND library (ARM9 side, snd_command.c): the command queue to the ARM7 sound driver. */
typedef int PXIFifoTag;
typedef struct SNDCommand {
    struct SNDCommand *next;      /* 0x00 */
    u32 id;                       /* 0x04 */
    u32 arg[4];                   /* 0x08 */
} SNDCommand;                     /* 0x18 */
typedef struct SNDSharedWork SNDSharedWork;
#define SND_COMMAND_NUM 256
#define SND_PXI_FIFO_MESSAGE_BUFSIZE 8
#define SND_COMMAND_NOBLOCK 0
#define SND_COMMAND_BLOCK 1
#define SND_COMMAND_SHARED_WORK 0x1d
#define PXI_FIFO_TAG_SOUND 7
#define PXI_PROC_ARM7 1

/* snd_command.c's zero-initialised statics are its .bss scalars, addressed off the block's base
 * (data_02044748 = sFreeList): defined here in the order that makes mwcc lay them out as the ROM
 * does (reverse declaration order, the last one appended); the module's delinked bss keeps the
 * symbols. The aggregates are addressed by their own symbols and stay extern. */
/* khdays: shared-bss */
int sWaitingCommandListCount = 0;
int sWaitingCommandListQueueWrite = 0;
int sWaitingCommandListQueueRead = 0;
SNDCommand *sFreeListEnd = 0;
SNDCommand *sReserveListEnd = 0;
SNDCommand *sReserveList = 0;
u32 sFinishedTag = 0;
SNDCommand *data_02044748 = 0;   /* sFreeList: the base of the block */
u32 sCurrentTag = 0;
#define sFreeList data_02044748
extern SNDCommand *data_0204476c[SND_PXI_FIFO_MESSAGE_BUFSIZE + 1];   /* sWaitingCommandListQueue */
#define sWaitingCommandListQueue data_0204476c
extern SNDSharedWork data_020447a0;   /* sSharedWork (0x280 bytes in this SDK, unaligned) */
#define sSharedWork data_020447a0
extern SNDCommand data_02044a20[SND_COMMAND_NUM] __attribute__((aligned(32)));   /* sCommandArray */
#define sCommandArray data_02044a20
extern SNDSharedWork *data_02046280;   /* SNDi_SharedWork */
#define SNDi_SharedWork data_02046280

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern void func_0200386c(u32 cycles);   /* OS_SpinWait */
#define OS_SpinWait func_0200386c
extern void PXI_SetFifoRecvCallback(int fifotag, void (*callback)(PXIFifoTag, u32, BOOL));
extern BOOL PXI_IsCallbackReady(int fifotag, int proc);
extern void PxiFifoCallback(PXIFifoTag tag, u32 data, BOOL err);
extern BOOL IsCommandAvailable(void);
extern void InitPXI(void);
extern void SNDi_InitSharedWork(SNDSharedWork *work);
extern u32 SNDi_GetFinishedCommandTag(void);
extern SNDCommand *SND_AllocCommand(u32 flags);
extern void func_02008788(SNDCommand *command);   /* SND_PushCommand */
#define SND_PushCommand func_02008788
extern BOOL func_020087c0(u32 flags);              /* SND_FlushCommand */
#define SND_FlushCommand func_020087c0

/* func_0200851c -- NitroSDK snd_command.c: SND_CommandInit. */
void func_0200851c (void)
{
    SNDCommand * command;
    int i;


    InitPXI();


    sFreeList = &sCommandArray[0];
    for (i = 0; i < SND_COMMAND_NUM - 1; i++) {
        sCommandArray[i].next = &sCommandArray[i + 1];
    }
    sCommandArray[SND_COMMAND_NUM - 1].next = NULL;
    sFreeListEnd = &sCommandArray[SND_COMMAND_NUM - 1];

    sReserveList = NULL;
    sReserveListEnd = NULL;

    sWaitingCommandListCount = 0;

    sWaitingCommandListQueueRead = 0;
    sWaitingCommandListQueueWrite = 0;

    sCurrentTag = 1;
    sFinishedTag = 0;

    SNDi_SharedWork = &sSharedWork;
    SNDi_InitSharedWork(SNDi_SharedWork);

    command = SND_AllocCommand(SND_COMMAND_BLOCK);
    if (command != NULL) {
        command->id = SND_COMMAND_SHARED_WORK;
        command->arg[0] = (u32)SNDi_SharedWork;

        SND_PushCommand(command);
        (void)SND_FlushCommand(SND_COMMAND_BLOCK);
    }

}
