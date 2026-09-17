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




typedef struct NNSSndFader {
    int origin;
    int target;
    int counter;
    int frame;
} NNSSndFader;
int func_0201e16c(const NNSSndFader * fader);
extern int func_0201e16c (const NNSSndFader * fader);

/* func_0201e144 -- NitroSystem fader.c: NNSi_SndFaderSet. */
void func_0201e144 (NNSSndFader * fader, int target, int frame)
{

    fader->origin = func_0201e16c(fader);
    fader->target = target;
    fader->frame = frame;
    fader->counter = 0;

}
