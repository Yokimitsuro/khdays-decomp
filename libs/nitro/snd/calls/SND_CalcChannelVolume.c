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

typedef int SNDChannelDataShift;
#define SND_CHANNEL_DATASHIFT_NONE 0
#define SND_CHANNEL_DATASHIFT_1BIT 1
#define SND_CHANNEL_DATASHIFT_2BIT 2
#define SND_CHANNEL_DATASHIFT_4BIT 3
#define SND_VOLUME_DB_MIN (-723)
#define SND_VOLUME_DB_MAX 0
#define SND_VOLUME_SHIFT_2_MIN (-240)
#define SND_VOLUME_SHIFT_1_MIN (-120)
#define SND_VOLUME_SHIFT_0_MIN (-60)
extern const u8 data_02041588[];              /* VolumeTable, indexed from -723 dB */
#define VolumeTable data_02041588

/* SND_CalcChannelVolume -- turn a decibel level (-723..0, in 1/10 dB) into the channel
 * volume register value: the 7-bit table volume and the data shift that scales it. */
u16 SND_CalcChannelVolume(int dB)
{
    SNDChannelDataShift shift;
    u8 volume;

    if (dB < SND_VOLUME_DB_MIN) {
        dB = SND_VOLUME_DB_MIN;
    } else if (dB > SND_VOLUME_DB_MAX) {
        dB = SND_VOLUME_DB_MAX;
    }

    volume = VolumeTable[dB - SND_VOLUME_DB_MIN];

    if (dB < SND_VOLUME_SHIFT_2_MIN) {
        shift = SND_CHANNEL_DATASHIFT_4BIT;
    } else if (dB < SND_VOLUME_SHIFT_1_MIN) {
        shift = SND_CHANNEL_DATASHIFT_2BIT;
    } else if (dB < SND_VOLUME_SHIFT_0_MIN) {
        shift = SND_CHANNEL_DATASHIFT_1BIT;
    } else {
        shift = SND_CHANNEL_DATASHIFT_NONE;
    }

    return (u16)(shift << 8 | volume);
}
