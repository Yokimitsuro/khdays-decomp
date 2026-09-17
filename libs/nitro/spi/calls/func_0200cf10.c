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

#define offsetof(type, member) ((u32)&(((type *)0)->member))

#define PM_SUCCESS 0

typedef enum {
    PM_LED_NONE = 0,
    PM_LED_ON = 1,
    PM_LED_BLINK_LOW = 2,
    PM_LED_BLINK_HIGH = 3
} PMLEDStatus;
typedef enum {
    PXI_FIFO_TAG_EX = 0,
    PXI_FIFO_TAG_USER_0,
    PXI_FIFO_TAG_USER_1,
    PXI_FIFO_TAG_SYSTEM,
    PXI_FIFO_TAG_NVRAM,
    PXI_FIFO_TAG_RTC,
    PXI_FIFO_TAG_TOUCHPANEL,
    PXI_FIFO_TAG_SOUND,
    PXI_FIFO_TAG_PM,
    PXI_FIFO_TAG_MIC,
    PXI_FIFO_TAG_WM,
    PXI_FIFO_TAG_FS,
    PXI_FIFO_TAG_OS,
    PXI_FIFO_TAG_CTRDG,
    PXI_FIFO_TAG_CARD,
    PXI_FIFO_TAG_WVR,
    PXI_FIFO_TAG_CTRDG_Ex,
    PXI_FIFO_TAG_CTRDG_PHI,
    PXI_MAX_FIFO_TAG = 32
} PXIFifoTag;
typedef void (*PXIFifoCallback) (PXIFifoTag tag, u32 data, BOOL err);
typedef void (*PMCallback) (u32 result, void * arg);
u32 PXIi_RouteByChannelId(PMLEDStatus status, PMCallback callback, void * arg);
typedef int (*MIDeviceReadFunction)(void * userdata, void * buffer, u32 offset, u32 length);
typedef int (*MIDeviceWriteFunction)(void * userdata, const void * buffer, u32 offset, u32 length);
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
struct SNDExChannel;
typedef enum {
    TP_REQUEST_COMMAND_SAMPLING         = 0x0,
    TP_REQUEST_COMMAND_AUTO_ON          = 0x1,
    TP_REQUEST_COMMAND_AUTO_OFF         = 0x2,
    TP_REQUEST_COMMAND_SET_STABILITY    = 0x3,
    TP_REQUEST_COMMAND_AUTO_SAMPLING    = 0x10
} TPRequestCommand;
typedef enum {
    TP_RESULT_SUCCESS = 0,
    TP_RESULT_INVALID_PARAMETER,
    TP_RESULT_ILLEGAL_STATUS,
    TP_RESULT_EXCLUSIVE,
    TP_RESULT_PXI_BUSY
} TPRequestResult;
typedef void (*TPRecvCallback) (TPRequestCommand command, TPRequestResult result, u16 index);
typedef enum MICResult {
    MIC_RESULT_SUCCESS = 0,
    MIC_RESULT_BUSY,
    MIC_RESULT_ILLEGAL_PARAMETER,
    MIC_RESULT_SEND_ERROR,
    MIC_RESULT_INVALID_COMMAND,
    MIC_RESULT_ILLEGAL_STATUS,
    MIC_RESULT_FATAL_ERROR,
    MIC_RESULT_MAX
} MICResult;
typedef void (*MICCallback) (MICResult result, void * arg);
typedef enum RTCResult {
    RTC_RESULT_SUCCESS = 0,
    RTC_RESULT_BUSY,
    RTC_RESULT_ILLEGAL_PARAMETER,
    RTC_RESULT_SEND_ERROR,
    RTC_RESULT_INVALID_COMMAND,
    RTC_RESULT_ILLEGAL_STATUS,
    RTC_RESULT_FATAL_ERROR,
    RTC_RESULT_MAX
} RTCResult;
typedef void (*RTCCallback) (RTCResult result, void * arg);
typedef struct WMGameInfo {
    u16 magicNumber;
    u8 ver;
    u8 platform;
    u32 ggid;
    u16 tgid;
    u8 userGameInfoLength;
    union {
        u8 gameNameCount_attribute;
        u8 attribute;
    };
    u16 parentMaxSize;
    u16 childMaxSize;
    union {
        u16 userGameInfo[112 / sizeof(u16)];
        struct {
            u16 userName[8 / sizeof(u16)];
            u16 gameName[16 / sizeof(u16)];
            u16 padd1[44];
        } old_type;
    };
} WMGameInfo, WMgameInfo;
typedef struct WMStartScanCallback {
    u16 apiid;
    u16 errcode;
    u16 wlCmdID;
    u16 wlResult;
    u16 state;
    u8 macAddress[6 ];
    u16 channel;
    u16 linkLevel;
    u16 ssidLength;
    u16 ssid[32 / sizeof(u16)];
    u16 gameInfoLength;
    WMGameInfo gameInfo;
} WMStartScanCallback, WMstartScanCallback;
typedef enum WVRResult {
    WVR_RESULT_SUCCESS = 0,
    WVR_RESULT_OPERATING,
    WVR_RESULT_DISABLE,
    WVR_RESULT_INVALID_PARAM,
    WVR_RESULT_FIFO_ERROR,
    WVR_RESULT_ILLEGAL_STATUS,
    WVR_RESULT_VRAM_LOCKED,
    WVR_RESULT_FATAL_ERROR,
    WVR_RESULT_MAX
} WVRResult;
typedef void (*WVRCallbackFunc) (void * arg, WVRResult result);
typedef void (*MBCommPStateCallback) (u16 child_aid, u32 status, void * arg);
typedef void (*MBCommCStateCallbackFunc) (u32 status, void * arg);
typedef void (*MBFakeScanCallbackFunc) (u16 type, void * arg);
typedef BOOL (*MBFakeCompareGGIDCallbackFunc) (WMStartScanCallback * arg, u32 defaultGGID);
typedef void * (*MIAllocatorAllocFunction)(void * userdata, u32 length, u32 alignment);
typedef void (*MIAllocatorFreeFunction)(void * userdata, void * buffer);
void func_0200cab8(void);
void func_0200caf8(u32 result, void * arg);
extern void func_0200cab8 (void);
extern void func_0200caf8 (u32 result, void * arg);
extern u32 PXIi_RouteByChannelId (PMLEDStatus status, PMCallback callback, void * arg);

/* func_0200cf10 -- NitroSDK pm.c: PMi_SetLED. */
u32 func_0200cf10 (PMLEDStatus status)
{
    u32 commandResult;
    u32 sendResult = PXIi_RouteByChannelId(status, func_0200caf8, &commandResult);

    if (sendResult == PM_SUCCESS) {
        func_0200cab8();
        return commandResult;
    }

    return sendResult;
}
