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



#define OS_LOW_ENTROPY_DATA_SIZE 32
#define HW_MAIN_MEM_SYSTEM 0x027ffc00
#define HW_BUTTON_XY_BUF   0x027fffa8
#define NVRAM_CONFIG_SIZE  0x74      /* sizeof(NVRAMConfig) in this SDK version */
#define reg_GX_VCOUNT      (*(vu16 *)0x04000006)
#define reg_G3X_GXSTAT     (*(vu32 *)0x04000600)
#define reg_PAD_KEYINPUT   (*(vu16 *)0x04000130)
static inline u16 GX_GetVCount(void) { return reg_GX_VCOUNT; }

typedef struct {
    u8 bootCheckInfo[0x20];       /* 0x000 */
    u32 resetParameter;           /* 0x020 */
    u8 padding5[0x8];             /* 0x024 */
    u32 romBaseOffset;            /* 0x02c */
    u8 cartridgeModuleInfo[12];   /* 0x030 */
    u32 vblankCount;              /* 0x03c */
    u8 wmBootBuf[0x40];           /* 0x040 */
    u8 nvramUserInfo[0x100];      /* 0x080 */
    u8 isd_reserved1[0x20];       /* 0x180 */
    u8 arenaInfo[0x48];           /* 0x1a0 */
    u8 real_time_clock[8];        /* 0x1e8 */
    u32 dmaClearBuf[4];           /* 0x1f0 */
    u8 rom_header[0x160];         /* 0x200 */
    u8 isd_reserved2[32];         /* 0x360 */
    u32 pxiSignalParam[2];        /* 0x380 */
    u32 pxiHandleChecker[2];      /* 0x388 */
    u32 mic_last_address;         /* 0x390 */
    u16 mic_sampling_data;        /* 0x394 */
    u16 wm_callback_control;      /* 0x396 */
    u16 wm_rssi_pool;             /* 0x398 */
    u8 ctrdg_SetModuleInfoFlag;   /* 0x39a */
    u8 ctrdg_IsExisting;          /* 0x39b */
    u32 component_param;          /* 0x39c */
    void *threadinfo_mainp;       /* 0x3a0 */
    void *threadinfo_subp;        /* 0x3a4 */
    u16 button_XY;                /* 0x3a8 */
    u8 touch_panel[4];            /* 0x3aa */
    u16 autoloadSync;             /* 0x3ae */
} OSSystemWork;
#define OS_GetSystemWork() ((OSSystemWork *)HW_MAIN_MEM_SYSTEM)

extern volatile u64 data_0204466c;   /* OSi_TickCounter */
#define OSi_TickCounter data_0204466c
extern u16 OS_GetTickLo(void);

/* OS_GetLowEntropyData -- NitroSDK os_entropy.c: fill 8 words of low-quality entropy
 * from the vcount, the tick counter, the MAC address, the vblank count, the 3D status,
 * the RTC, the microphone, the touch panel and the buttons. */
void OS_GetLowEntropyData(u32 buffer[OS_LOW_ENTROPY_DATA_SIZE / sizeof(u32)])
{
    const OSSystemWork *work = OS_GetSystemWork();
    const u8 *macAddress = (u8 *)((u32)(work->nvramUserInfo) + ((NVRAM_CONFIG_SIZE + 3) & ~0x00000003));

    buffer[0] = (u32)((GX_GetVCount() << 16) | OS_GetTickLo());
    buffer[1] = (u32)(*(u16 *)(macAddress + 4) << 16) ^ (u32)(OSi_TickCounter);
    buffer[2] = (u32)(OSi_TickCounter >> 32) ^ *(u32 *)macAddress ^ work->vblankCount;
    buffer[2] ^= reg_G3X_GXSTAT;
    buffer[3] = *(u32 *)(&work->real_time_clock[0]);
    buffer[4] = *(u32 *)(&work->real_time_clock[4]);
    buffer[5] = (((u32)work->mic_sampling_data) << 16) ^ work->mic_last_address;
    buffer[6] = (u32)((*(u16 *)(&work->touch_panel[0]) << 16) | *(u16 *)(&work->touch_panel[2]));
    buffer[7] = (u32)((work->wm_rssi_pool << 16) | (reg_PAD_KEYINPUT | *(vu16 *)HW_BUTTON_XY_BUF));
}
