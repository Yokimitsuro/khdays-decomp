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





/* func_0200ff20 -- NitroSystem std_string.c: STD_CopyString. */
char * func_0200ff20 (char * destp, const char * srcp)
{
    char * retval = destp;


    while (*srcp) {
        *destp++ = (char)*srcp++;
    }

    *destp = '\0';

    return retval;
}
