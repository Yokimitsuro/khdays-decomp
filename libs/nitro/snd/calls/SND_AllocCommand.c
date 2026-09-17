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

extern BOOL IsCommandAvailable(void);
extern SNDCommand *func_02008ba4(void);       /* AllocCommand */
extern int SND_CountWaitingCommand(void);
extern const SNDCommand *func_020085f0(u32 flags);   /* SND_RecvCommandReply */
extern BOOL func_020087c0(u32 flags);         /* SND_FlushCommand */
extern void RequestCommandProc(void);

/* SND_AllocCommand -- take a free command slot; with SND_COMMAND_BLOCK the caller waits,
 * first reaping finished command lists, else flushing the reserve list, and then
 * blocking on replies until a slot frees up. */
SNDCommand *SND_AllocCommand(u32 flags)
{
    SNDCommand *command;

    if (!IsCommandAvailable())
        return NULL;

    command = func_02008ba4();
    if (command != NULL)
        return command;

    if ((flags & SND_COMMAND_BLOCK) == 0)
        return NULL;

    if (SND_CountWaitingCommand() > 0) {
        while (func_020085f0(SND_COMMAND_NOBLOCK) != NULL) {
        }

        command = func_02008ba4();
        if (command != NULL)
            return command;
    } else {
        (void)func_020087c0(SND_COMMAND_BLOCK);
    }

    RequestCommandProc();

    do {
        (void)func_020085f0(SND_COMMAND_BLOCK);
        command = func_02008ba4();
    } while (command == NULL);

    return command;
}
