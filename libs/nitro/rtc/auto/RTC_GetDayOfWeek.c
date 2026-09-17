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
typedef volatile unsigned short vu16;
typedef volatile unsigned int vu32;
typedef volatile unsigned char vu8;

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0
#define HW_MAIN_MEM 0x02000000



typedef int RTCWeek;
typedef struct RTCDate {
    u32 year;                     /* 0x00: since 2000 */
    u32 month;                    /* 0x04 */
    u32 day;                      /* 0x08 */
    RTCWeek week;                 /* 0x0c */
} RTCDate;

/* RTC_GetDayOfWeek -- NitroSDK rtc convert.c: Zeller's rule for the weekday of `date`
 * (year since 2000), 0 = Sunday. */
RTCWeek RTC_GetDayOfWeek(RTCDate *date)
{
    int cent;
    int year = (int)(2000 + date->year);
    int month = (int)date->month;
    int day = (int)date->day;

    month -= 2;

    if (month < 1) {
        month += 12;
        --year;
    }

    cent = year / 100;
    year %= 100;
    return (RTCWeek)(((26 * month - 2) / 10 + day + year + year / 4 + cent / 4 + 5 * cent) % 7);
}
