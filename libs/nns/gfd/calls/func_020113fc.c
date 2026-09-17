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




typedef int (*MIDeviceReadFunction)(void * userdata, void * buffer, u32 offset, u32 length);
typedef int (*MIDeviceWriteFunction)(void * userdata, const void * buffer, u32 offset, u32 length);
void GX_BeginLoadOBJExtPltt_0x02007b64(void);
void GX_LoadOBJExtPltt(const void * pSrc, u32 destSlotAddr, u32 szByte);
void GX_EndLoadOBJExtPltt(void);
typedef void * (*MIAllocatorAllocFunction)(void * userdata, u32 length, u32 alignment);
typedef void (*MIAllocatorFreeFunction)(void * userdata, void * buffer);

/* func_020113fc -- NitroSystem gfd_VramTransferManager.c: DoTransfer2dObjExtPlttMain. */
void func_020113fc (const void * pSrc, u32 offset, u32 szByte)
{
    GX_BeginLoadOBJExtPltt_0x02007b64();
    GX_LoadOBJExtPltt(pSrc, offset, szByte);
    GX_EndLoadOBJExtPltt();
}
