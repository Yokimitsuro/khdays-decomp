#define NULL ((void *)0)

typedef unsigned char u8;
typedef unsigned int u32;
typedef int OSIntrMode;

typedef void (*OSThreadFunc)(void *pArg);

/* Only the fields this function writes are named; the rest of the record stays
   reserved until a function gives evidence about it. */
typedef struct OSThread {
    u8 _reserved0[4];
    void *pArg;                  /* 0x04 */
    u8 _reserved08[0x34];
    void *pTerminateHook;        /* 0x3c */
    u8 _reserved40[0x24];
    u32 field64;                 /* 0x64 */
    u8 _reserved68[4];
    u32 id;                      /* 0x6c */
    u32 priority;                /* 0x70 */
    u32 field74;                 /* 0x74 */
    u32 field78;                 /* 0x78 */
    struct OSThread *prev;       /* 0x7c */
    struct OSThread *next;       /* 0x80 */
    u32 field84;
    u32 field88;
    u32 field8c;
    u32 *pStackLow;              /* 0x90 */
    u32 *pStackHigh;             /* 0x94 */
    u32 field98;
    u32 field9c;
    u32 fielda0;
    u8 _reserveda4[0xc];         /* 0xa4, cleared as a block */
    u32 fieldb0;                 /* 0xb0 */
} OSThread;

/* Guard words written at both ends of the stack so an overflow is detectable. */
#define OSi_STACK_MAGIC_HIGH 0xfddb597du
#define OSi_STACK_MAGIC_LOW  0x7bf9dd5bu

extern OSIntrMode OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(OSIntrMode state);
extern u32 func_020018ec(void);
extern void OSi_InsertThreadByPriority(OSThread *pThread);
extern void OS_InitContext(OSThread *pThread, OSThreadFunc pfnEntry, void *pStack);
extern void OS_SetThreadDestructor(OSThread *pThread, void *pfnDestructor);
extern void INITi_CpuClear32_0x01ff86fc(u32 nValue, void *pDest, u32 nBytes);
extern void func_02001dec(void);

void OS_CreateThread(OSThread *pThread, OSThreadFunc pfnEntry, void *pArg,
                     void *pStack, u32 nStackSize, u32 nPriority)
{
    u8 *pLow;
    OSIntrMode nLast = OS_DisableInterrupts();
    u32 nId = func_020018ec();

    pThread->priority = nPriority;
    pThread->id = nId;
    pThread->field64 = 0;
    pThread->field74 = 0;
    OSi_InsertThreadByPriority(pThread);

    pLow = (u8 *)pStack - nStackSize;
    pThread->pStackHigh = (u32 *)pStack;
    pThread->pStackLow = (u32 *)pLow;
    pThread->field98 = 0;
    pThread->pStackHigh[-1] = OSi_STACK_MAGIC_HIGH;
    pThread->pStackLow[0] = OSi_STACK_MAGIC_LOW;
    pThread->field9c = pThread->fielda0 = 0;
    OS_InitContext(pThread, pfnEntry, (void *)((u8 *)pStack - 4));

    pThread->pArg = pArg;
    pThread->pTerminateHook = (void *)func_02001dec;
    INITi_CpuClear32_0x01ff86fc(0, pLow + 4, nStackSize - 8);

    pThread->field84 = 0;
    pThread->field88 = 0;
    pThread->field8c = 0;
    OS_SetThreadDestructor(pThread, NULL);

    pThread->field78 = 0;
    pThread->next = NULL;
    pThread->prev = NULL;
    INITi_CpuClear32_0x01ff86fc(0, pThread->_reserveda4, 12);

    pThread->fieldb0 = 0;
    OS_RestoreInterrupts(nLast);
}
