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




void INITi_CpuClear32_0x01ff86fc(u32 data, void * destp, u32 size);
static inline void MI_CpuFill32 (void * dest, u32 data, u32 size)
{
    INITi_CpuClear32_0x01ff86fc(data, dest, size);
}
static inline void MI_CpuClear32 (void * dest, u32 size)
{
    MI_CpuFill32(dest, 0, size);
}
void DC_FlushRange(const void * startAddr, u32 nBytes);
void SND_StartTimer(u32 chBitMask, u32 capBitMask, u32 alarmBitMask, u32 flags);
typedef enum {
    NNS_SND_CAPTURE_FORMAT_PCM16,
    NNS_SND_CAPTURE_FORMAT_PCM8
} NNSSndCaptureFormat;
typedef enum {
    NNS_SND_CAPTURE_TYPE_REVERB,
    NNS_SND_CAPTURE_TYPE_EFFECT,
    NNS_SND_CAPTURE_TYPE_SAMPLING
} NNSSndCaptureType;
typedef void (*NNSSndCaptureCallback)(void * bufferL, void * bufferR, u32 len, NNSSndCaptureFormat format, void * arg);
typedef struct NNSSndFader {
    int origin;
    int target;
    int counter;
    int frame;
} NNSSndFader;
typedef struct CaptureParam {
    BOOL activeFlag;
    NNSSndCaptureType type;
    NNSSndCaptureFormat format;
    void * bufferL;
    void * bufferR;
    u32 bufLen;
    u32 blockSize;
    int curBuffer;
    u32 chBitMask;
    u32 playChBitMask;
    u32 capBitMask;
    int alarmNo;
    int interval;
    NNSSndCaptureCallback callback;
    void * callbackArg;
    NNSSndFader fader;
    BOOL fadeOutFlag;
    int volume;
} CaptureParam;
extern CaptureParam data_0204acf8;

/* func_0201b0ec -- NitroSystem capture.c: NNSi_SndCaptureEndSleep. */
void func_0201b0ec (void)
{
    CaptureParam * cap;

    cap = &data_0204acf8;

    if (!cap->activeFlag) return;

    cap->curBuffer = 0;

    MI_CpuClear32(cap->bufferL, cap->bufLen);
    MI_CpuClear32(cap->bufferR, cap->bufLen);
    DC_FlushRange(cap->bufferL, cap->bufLen);
    DC_FlushRange(cap->bufferR, cap->bufLen);

    SND_StartTimer(
        cap->playChBitMask,
        cap->capBitMask,
        cap->alarmNo >= 0 ? (u32)(1 << cap->alarmNo) : 0,
        0
    );
}
