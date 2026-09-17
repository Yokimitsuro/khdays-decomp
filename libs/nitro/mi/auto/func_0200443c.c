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



typedef struct {
    u32 compParam :4;
    u32 compType :4;
    u32 destSize :24;
} MICompressionHeader;
typedef struct {
    u8 * destp;
    s32 destCount;
    u32 length;
    u16 destTmp;
    u8 destTmpCnt;
    u8 flags;
    u8 flagIndex;
    u8 lengthFlg;
    u8 exFormat;
    u8 _padding[1];
} MIUncompContextLZ;

/* func_0200443c -- NitroSDK mi_uncomp_stream.c: MI_InitUncompContextLZ. */
void func_0200443c (MIUncompContextLZ * context, u8 * dest, const MICompressionHeader * header)
{
    context->destp = dest;
    context->destCount = (s32)header->destSize;
    context->flags = 0;
    context->flagIndex = 0;
    context->length = 0;
    context->lengthFlg = 3;
    context->destTmp = 0;
    context->destTmpCnt = 0;
    context->exFormat = (u8)((header->compParam == 0)? 0U : 1U);
}
