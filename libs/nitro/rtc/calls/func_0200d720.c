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


/* NitroSDK RTC library (external.c): the ARM9 side of the real-time clock PXI protocol. */
typedef int PXIFifoTag;
typedef int RTCResult;
typedef int RTCPxiResult;
typedef int RTCWeek;
typedef int RTCAlarmStatus;
typedef void (*RTCCallback)(RTCResult result, void *arg);
typedef void (*RTCInterrupt)(void);
enum { RTC_RESULT_SUCCESS = 0, RTC_RESULT_BUSY, RTC_RESULT_ILLEGAL_PARAMETER, RTC_RESULT_SEND_ERROR,
       RTC_RESULT_INVALID_COMMAND, RTC_RESULT_ILLEGAL_STATUS, RTC_RESULT_FATAL_ERROR, RTC_RESULT_MAX };
enum { RTC_PXI_RESULT_SUCCESS = 0, RTC_PXI_RESULT_INVALID_COMMAND, RTC_PXI_RESULT_ILLEGAL_STATUS,
       RTC_PXI_RESULT_BUSY, RTC_PXI_RESULT_FATAL_ERROR };
enum { RTC_ALARM_STATUS_OFF = 0, RTC_ALARM_STATUS_ON, RTC_ALARM_STATUS_MAX };
enum { RTC_LOCK_OFF = 0, RTC_LOCK_ON, RTC_LOCK_MAX };
typedef enum RTCSequence {
    RTC_SEQ_GET_DATE = 0, RTC_SEQ_GET_TIME, RTC_SEQ_GET_DATETIME, RTC_SEQ_SET_DATE, RTC_SEQ_SET_TIME,
    RTC_SEQ_SET_DATETIME, RTC_SEQ_GET_ALARM1_STATUS, RTC_SEQ_GET_ALARM2_STATUS, RTC_SEQ_GET_ALARM_PARAM,
    RTC_SEQ_SET_ALARM1_STATUS, RTC_SEQ_SET_ALARM2_STATUS, RTC_SEQ_SET_ALARM1_PARAM, RTC_SEQ_SET_ALARM2_PARAM,
    RTC_SEQ_SET_HOUR_FORMAT, RTC_SEQ_SET_REG_STATUS2, RTC_SEQ_SET_REG_ADJUST, RTC_SEQ_MAX
} RTCSequence;
#define RTC_ALARM_ENABLE_NONE       0x0000
#define RTC_ALARM_ENABLE_WEEK       0x0001
#define RTC_ALARM_ENABLE_HOUR       0x0002
#define RTC_ALARM_ENABLE_MINUTE     0x0004
#define RTC_INTERRUPT_MODE_NONE     0x0
#define RTC_INTERRUPT_MODE_ALARM    0x4
#define RTC_PXI_COMMAND_MASK        0x00007f00
#define RTC_PXI_COMMAND_SHIFT       8
#define RTC_PXI_RESULT_MASK         0x000000ff
#define RTC_PXI_RESULT_SHIFT        0
#define RTC_PXI_COMMAND_INTERRUPT   0x30
#define HW_RTC_BUF                  0x027ffde8   /* OSSystemWork.real_time_clock[8] */

typedef struct RTCDate { u32 year; u32 month; u32 day; RTCWeek week; } RTCDate;
typedef struct RTCTime { u32 hour; u32 minute; u32 second; } RTCTime;
typedef struct RTCAlarmParam { RTCWeek week; u32 hour; u32 minute; u32 enable; } RTCAlarmParam;

typedef struct RTCRawDate {
    u32 year :8;
    u32 month :5;
    u32 dummy0 :3;
    u32 day :6;
    u32 dummy1 :2;
    u32 week :3;
    u32 dummy2 :5;
} RTCRawDate;
typedef struct RTCRawTime {
    u32 hour :6;
    u32 afternoon :1;
    u32 dummy0 :1;
    u32 minute :7;
    u32 dummy1 :1;
    u32 second :7;
    u32 dummy2 :9;
} RTCRawTime;
typedef struct RTCRawStatus1 {
    u16 reset :1;
    u16 format :1;
    u16 dummy0 :2;
    u16 intr1 :1;
    u16 intr2 :1;
    u16 bld :1;
    u16 poc :1;
    u16 dummy1 :8;
} RTCRawStatus1;
typedef struct RTCRawStatus2 {
    u16 intr_mode :4;
    u16 dummy0 :2;
    u16 intr2_mode :1;
    u16 test :1;
    u16 dummy1 :8;
} RTCRawStatus2;
typedef struct RTCRawAlarm {
    u32 week :3;
    u32 dummy0 :4;
    u32 we :1;
    u32 hour :6;
    u32 afternoon :1;
    u32 he :1;
    u32 minute :7;
    u32 me :1;
    u32 dummy2 :8;
} RTCRawAlarm;
typedef struct RTCRawPulse { u32 pulse :5; u32 dummy :27; } RTCRawPulse;
typedef struct RTCRawAdjust { u32 adjust :8; u32 dummy :24; } RTCRawAdjust;
typedef struct RTCRawFree { u32 free :8; u32 dummy :24; } RTCRawFree;
typedef union RTCRawData {
    struct {
        RTCRawDate date;
        RTCRawTime time;
    } t;
    struct {
        RTCRawStatus1 status1;
        RTCRawStatus2 status2;
        union {
            RTCRawPulse pulse;
            RTCRawAlarm alarm;
            RTCRawAdjust adjust;
            RTCRawFree free;
        };
    } a;
    u32 words[2];
    u16 halfs[4];
    u8 bytes[8];
} RTCRawData;
#define OS_GetSystemWork_real_time_clock() ((u8 *)HW_RTC_BUF)

typedef struct RTCWork {
    u32 lock;                     /* 0x00 */
    RTCCallback callback;         /* 0x04 */
    void *buffer[2];              /* 0x08 */
    void *callbackArg;            /* 0x10 */
    u32 sequence;                 /* 0x14 */
    u32 index;                    /* 0x18 */
    RTCInterrupt interrupt;       /* 0x1c */
    RTCResult commonResult;       /* 0x20 */
} RTCWork;
/* external.c statics, one .bss block at data_02046438 (mwcc's reverse order): the tick base,
 * the two init flags, then rtcWork at +0xc. */
extern struct {
    u64 initialTotalTicks;        /* 0x00: rtcInitialTotalTicks */
    u16 tickInitialized;          /* 0x08: rtcTickInitialized */
    u16 initialized;              /* 0x0a: rtcInitialized */
    RTCWork work;                 /* 0x0c: rtcWork */
} data_02046438;
#define rtcWork data_02046438.work

extern u32 func_0200dc70(u32 bcd);   /* RtcBCD2HEX */
#define RtcBCD2HEX func_0200dc70
extern RTCWeek RTC_GetDayOfWeek(RTCDate *date);
extern BOOL RTCi_WriteRawStatus2Async(void);

/* func_0200d720 -- NitroSDK rtc external.c: RtcCommonCallback, the PXI completion handler: convert the
 * raw BCD registers the ARM7 wrote into the caller's buffers per sequence, chase the two-step
 * alarm status writes, then unlock and call back. */
void func_0200d720 (PXIFifoTag tag, u32 data, BOOL err)
{

    RTCResult result;
    RTCPxiResult pxiresult;
    u8 command;
    RTCCallback cb;

    if (err) {
        if (rtcWork.index) {
            rtcWork.index = 0;
        }

        if (rtcWork.lock != RTC_LOCK_OFF) {
            rtcWork.lock = RTC_LOCK_OFF;
        }

        if (rtcWork.callback) {
            cb = rtcWork.callback;
            rtcWork.callback = NULL;
            cb(RTC_RESULT_FATAL_ERROR, rtcWork.callbackArg);
        }

        return;
    }

    command = (u8)((data & RTC_PXI_COMMAND_MASK) >> RTC_PXI_COMMAND_SHIFT);
    pxiresult = (RTCPxiResult)((data & RTC_PXI_RESULT_MASK) >> RTC_PXI_RESULT_SHIFT);

    if (command == RTC_PXI_COMMAND_INTERRUPT) {
        if (rtcWork.interrupt) {
            rtcWork.interrupt();
        }
        return;
    }

    if (pxiresult == RTC_PXI_RESULT_SUCCESS) {
        result = RTC_RESULT_SUCCESS;
        switch (rtcWork.sequence) {

        case RTC_SEQ_GET_DATE:
        {
            RTCDate * pDst = (RTCDate *)(rtcWork.buffer[0]);
            RTCRawDate * pSrc = &(((RTCRawData *)OS_GetSystemWork_real_time_clock())->t.date);

            pDst->year = RtcBCD2HEX(pSrc->year);
            pDst->month = RtcBCD2HEX(pSrc->month);
            pDst->day = RtcBCD2HEX(pSrc->day);
            pDst->week = RTC_GetDayOfWeek(pDst);
        }
        break;
        case RTC_SEQ_GET_TIME:
        {
            RTCTime * pDst = (RTCTime *)(rtcWork.buffer[0]);
            RTCRawTime * pSrc = &(((RTCRawData *)OS_GetSystemWork_real_time_clock())->t.time);

            pDst->hour = RtcBCD2HEX(pSrc->hour);
            pDst->minute = RtcBCD2HEX(pSrc->minute);
            pDst->second = RtcBCD2HEX(pSrc->second);
        }
        break;
        case RTC_SEQ_GET_DATETIME:
        {
            RTCDate * pDst = (RTCDate *)(rtcWork.buffer[0]);
            RTCRawDate * pSrc = &(((RTCRawData *)OS_GetSystemWork_real_time_clock())->t.date);

            pDst->year = RtcBCD2HEX(*(u32 *)pSrc & 0x000000ff);
            pDst->month = RtcBCD2HEX(pSrc->month);
            pDst->day = RtcBCD2HEX(pSrc->day);
            pDst->week = RTC_GetDayOfWeek(pDst);
        }
            {
                RTCTime * pDst = (RTCTime *)(rtcWork.buffer[1]);
                RTCRawTime * pSrc = &(((RTCRawData *)OS_GetSystemWork_real_time_clock())->t.time);

                pDst->hour = RtcBCD2HEX(pSrc->hour);
                pDst->minute = RtcBCD2HEX(pSrc->minute);
                pDst->second = RtcBCD2HEX(pSrc->second);
            }
            break;

        case RTC_SEQ_SET_DATE:
        case RTC_SEQ_SET_TIME:
        case RTC_SEQ_SET_DATETIME:
            break;
        case RTC_SEQ_GET_ALARM1_STATUS:
        {
            RTCAlarmStatus * pDst = (RTCAlarmStatus *)(rtcWork.buffer[0]);
            RTCRawStatus2 * pSrc = &(((RTCRawData *)OS_GetSystemWork_real_time_clock())->a.status2);

            switch (pSrc->intr_mode) {
            case RTC_INTERRUPT_MODE_ALARM:
                *pDst = RTC_ALARM_STATUS_ON;
                break;
            default:
                *pDst = RTC_ALARM_STATUS_OFF;
            }
        }
        break;

        case RTC_SEQ_GET_ALARM2_STATUS:
        {
            RTCAlarmStatus * pDst = (RTCAlarmStatus *)(rtcWork.buffer[0]);
            RTCRawStatus2 * pSrc = &(((RTCRawData *)OS_GetSystemWork_real_time_clock())->a.status2);

            if (pSrc->intr2_mode) {
                *pDst = RTC_ALARM_STATUS_ON;
            } else {
                *pDst = RTC_ALARM_STATUS_OFF;
            }
        }
        break;

        case RTC_SEQ_GET_ALARM_PARAM:
        {
            RTCAlarmParam * pDst = (RTCAlarmParam *)(rtcWork.buffer[0]);
            RTCRawAlarm * pSrc = &(((RTCRawData *)OS_GetSystemWork_real_time_clock())->a.alarm);

            pDst->week = (RTCWeek)(pSrc->week);
            pDst->hour = RtcBCD2HEX(pSrc->hour);
            pDst->minute = RtcBCD2HEX(pSrc->minute);
            pDst->enable = RTC_ALARM_ENABLE_NONE;
            if (pSrc->we)
                pDst->enable += RTC_ALARM_ENABLE_WEEK;
            if (pSrc->he)
                pDst->enable += RTC_ALARM_ENABLE_HOUR;
            if (pSrc->me)
                pDst->enable += RTC_ALARM_ENABLE_MINUTE;
        }
        break;
        case RTC_SEQ_SET_ALARM1_STATUS:
            if (rtcWork.index == 0) {
                RTCRawStatus2 * pSrc = &(((RTCRawData *)OS_GetSystemWork_real_time_clock())->a.status2);

                if (*(RTCAlarmStatus *)(rtcWork.buffer[0]) == RTC_ALARM_STATUS_ON) {
                    if (pSrc->intr_mode != RTC_INTERRUPT_MODE_ALARM) {
                        rtcWork.index++;
                        pSrc->intr_mode = RTC_INTERRUPT_MODE_ALARM;
                        if (!RTCi_WriteRawStatus2Async()) {
                            rtcWork.index = 0;
                            result = RTC_RESULT_SEND_ERROR;
                        }
                    }
                } else {
                    if (pSrc->intr_mode != RTC_INTERRUPT_MODE_NONE) {
                        rtcWork.index++;
                        pSrc->intr_mode = RTC_INTERRUPT_MODE_NONE;
                        if (!RTCi_WriteRawStatus2Async()) {
                            rtcWork.index = 0;
                            result = RTC_RESULT_SEND_ERROR;
                        }
                    }
                }
            } else {
                rtcWork.index = 0;
            }
            break;
        case RTC_SEQ_SET_ALARM2_STATUS:
            if (rtcWork.index == 0) {
                RTCRawStatus2 * pSrc = &(((RTCRawData *)OS_GetSystemWork_real_time_clock())->a.status2);

                if (*(RTCAlarmStatus *)(rtcWork.buffer[0]) == RTC_ALARM_STATUS_ON) {
                    if (!pSrc->intr2_mode) {
                        rtcWork.index++;
                        pSrc->intr2_mode = 1;
                        if (!RTCi_WriteRawStatus2Async()) {
                            rtcWork.index = 0;
                            result = RTC_RESULT_SEND_ERROR;
                        }
                    }
                } else {

                    if (pSrc->intr2_mode) {

                        rtcWork.index++;
                        pSrc->intr2_mode = 0;
                        if (!RTCi_WriteRawStatus2Async()) {
                            rtcWork.index = 0;
                            result = RTC_RESULT_SEND_ERROR;
                        }
                    }
                }
            } else {
                rtcWork.index = 0;
            }
            break;
        case RTC_SEQ_SET_ALARM1_PARAM:
        case RTC_SEQ_SET_ALARM2_PARAM:
        case RTC_SEQ_SET_HOUR_FORMAT:
        case RTC_SEQ_SET_REG_STATUS2:
        case RTC_SEQ_SET_REG_ADJUST:
            break;
        default:
            result = RTC_RESULT_INVALID_COMMAND;
            rtcWork.index = 0;
        }
    } else {
        rtcWork.index = 0;

        switch (pxiresult) {
        case RTC_PXI_RESULT_INVALID_COMMAND:
            result = RTC_RESULT_INVALID_COMMAND;
            break;
        case RTC_PXI_RESULT_ILLEGAL_STATUS:
            result = RTC_RESULT_ILLEGAL_STATUS;
            break;
        case RTC_PXI_RESULT_BUSY:
            result = RTC_RESULT_BUSY;
            break;
        case RTC_PXI_RESULT_FATAL_ERROR:
        default:
            result = RTC_RESULT_FATAL_ERROR;
        }
    }

    if (rtcWork.index == 0) {
        if (rtcWork.lock != RTC_LOCK_OFF) {
            rtcWork.lock = RTC_LOCK_OFF;
        }

        if (rtcWork.callback) {
            cb = rtcWork.callback;
            rtcWork.callback = NULL;
            cb(result, rtcWork.callbackArg);
        }
    }
}
