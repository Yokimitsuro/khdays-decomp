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


/* NitroSDK OS library: arena defaults (os_arena.c), the thread system init (os_thread.c) and the
 * owner info (os_ownerInfo.c). The SDK_* figures are link-time constants of the SDK build; the ROM
 * carries their values in the literal pools. */
typedef int OSArenaId;
enum { OS_ARENA_MAIN = 0, OS_ARENA_MAIN_SUBPRIV, OS_ARENA_MAINEX, OS_ARENA_ITCM, OS_ARENA_DTCM, OS_ARENA_SHARED, OS_ARENA_WRAM_MAIN, OS_ARENA_WRAM_SUB, OS_ARENA_WRAM_SUBPRIV, OS_ARENA_MAX };
#define OS_CONSOLE_SIZE_MASK 0x00000003
#define OS_CONSOLE_SIZE_4MB  0x00000001
#define HW_MAIN_MEM_MAIN_END 0x023e0000
#define HW_MAIN_MEM_DEBUGGER 0x02700000
#define HW_ITCM_ARENA_HI_DEFAULT 0x02000000
#define HW_SHARED_ARENA_HI_DEFAULT 0x027ff680
#define HW_WRAM 0x037f8000
#define HW_DTCM_IRQ_STACK_END 0x027e3f80
#define HW_DTCM_SVC_STACK     0x027e3f80
/* Link-time constants of the SDK build (linker-absolute symbols, declared in tools/configure.py
 * ABSOLUTE_SYMBOLS with the ROM's values: SDK_SYS_STACKSIZE 0, SDK_IRQ_STACKSIZE 0x800,
 * SDK_SECTION_ARENA_DTCM_START 0x027e0e60): the code must keep testing them at run time. */
extern void SDK_SYS_STACKSIZE(void);
extern void SDK_IRQ_STACKSIZE(void);
extern void SDK_SECTION_ARENA_DTCM_START(void);
#define OSi_SYS_STACKSIZE ((s32)SDK_SYS_STACKSIZE)
#define OSi_IRQ_STACKSIZE ((s32)SDK_IRQ_STACKSIZE)
#define OSi_MAIN_ARENA_HI_DEFAULT   HW_MAIN_MEM_MAIN_END
#define OSi_MAINEX_ARENA_HI_DEFAULT HW_MAIN_MEM_DEBUGGER
#define OSi_DTCM_ARENA_LO_DEFAULT   ((u32)SDK_SECTION_ARENA_DTCM_START)
#define OSi_WRAM_MAIN_ARENA_HI_DEFAULT HW_WRAM
/* HW_DTCM is the DTCM base symbol: the pool carries it and the offsets are added (+0x3f80). */
extern u32 data_027e0000;
#define HW_DTCM ((u32)&data_027e0000)
#define HW_DTCM_SVC_STACK_ADDR (HW_DTCM + 0x3f80)
#define HW_DTCM_IRQ_STACK_END_ADDR (HW_DTCM + 0x3f80)
extern u32 OS_GetConsoleType(void);

/* os_arena.c statics, one .bss block: OSi_Initialized then OSi_MainExArenaEnabled (a .bss
 * BOOL in this SDK version: the SDK_4M build's FALSE). */
extern struct { BOOL initialized; BOOL mainExArenaEnabled; } data_02044588;
#define OSi_Initialized data_02044588.initialized
#define OSi_MainExArenaEnabled data_02044588.mainExArenaEnabled

/* os_thread.c. */
typedef struct OSThread OSThread;
typedef struct OSThreadQueue { OSThread *head; OSThread *tail; } OSThreadQueue;
typedef struct OSThreadLink { OSThread *prev; OSThread *next; } OSThreadLink;
typedef struct OSMutexQueue { void *head; void *tail; } OSMutexQueue;
typedef int OSThreadState;
enum { OS_THREAD_STATE_WAITING = 0, OS_THREAD_STATE_READY = 1, OS_THREAD_STATE_TERMINATED = 2 };
#define OS_THREAD_LAUNCHER_PRIORITY 16
#define OS_THREAD_PRIORITY_MAX 31
#define OS_THREAD_SPECIFIC_MAX 3
struct OSThread {
    u8 context[0x64];             /* 0x00: OSContext */
    OSThreadState state;          /* 0x64 */
    OSThread *next;               /* 0x68 */
    u32 id;                       /* 0x6c */
    u32 priority;                 /* 0x70 */
    void *profiler;               /* 0x74 */
    OSThreadQueue *queue;         /* 0x78 */
    OSThreadLink link;            /* 0x7c */
    void *mutex;                  /* 0x84 */
    OSMutexQueue mutexQueue;      /* 0x88 */
    u32 stackTop;                 /* 0x90 */
    u32 stackBottom;              /* 0x94 */
    u32 stackWarningOffset;       /* 0x98 */
    OSThreadQueue joinQueue;      /* 0x9c */
    void *specific[OS_THREAD_SPECIFIC_MAX];   /* 0xa4 */
    void *alarmForSleep;          /* 0xb0 */
    void (*destructor)(void *);   /* 0xb4 */
    void *userParameter;          /* 0xb8 */
    int systemErrno;              /* 0xbc */
};                                /* 0xc0 */
typedef struct OSThreadInfo {
    u16 isNeedRescheduling;       /* 0x00 */
    u16 irqDepth;                 /* 0x02 */
    OSThread *current;            /* 0x04 */
    OSThread *list;               /* 0x08 */
    void *switchCallback;         /* 0x0c */
} OSThreadInfo;
/* os_thread.c statics, one .bss block at data_0204430c: the scalars, then OSi_ThreadInfo (+0x24,
 * data_02044330); OSi_IdleThread (data_02044340), OSi_LauncherThread (data_02044400) and
 * OSi_IdleThreadStack (data_020444c0) follow with their own symbols. */
extern struct {
    u32 unused0;                  /* 0x00 */
    u32 unused4;                  /* 0x04 */
    OSThread **currentThreadPtr;  /* 0x08: OSi_CurrentThreadPtr */
    BOOL isThreadInitialized;     /* 0x0c: OSi_IsThreadInitialized */
    u32 unused10[4];              /* 0x10 */
    int threadIdCount;            /* 0x20: OSi_ThreadIdCount */
    OSThreadInfo threadInfo;      /* 0x24: OSi_ThreadInfo (data_02044330) */
} data_0204430c;
#define OSi_CurrentThreadPtr data_0204430c.currentThreadPtr
#define OSi_IsThreadInitialized data_0204430c.isThreadInitialized
#define OSi_ThreadInfo data_0204430c.threadInfo
extern OSThread data_02044340;    /* OSi_IdleThread */
#define OSi_IdleThread data_02044340
extern OSThread data_02044400;    /* OSi_LauncherThread */
#define OSi_LauncherThread data_02044400
#define HW_SVC_STACK_SIZE 0x40
#define OSi_IDLE_CHECKNUM_SIZE (sizeof(u32) * 2 + HW_SVC_STACK_SIZE)
#define OSi_IDLE_SVC_SIZE (sizeof(u32) * 32)
#define OSi_IDLE_THREAD_STACK_SIZE (OSi_IDLE_CHECKNUM_SIZE + OSi_IDLE_SVC_SIZE)
extern u32 data_020444c0[OSi_IDLE_THREAD_STACK_SIZE / sizeof(u32)];   /* OSi_IdleThreadStack */
#define OSi_IdleThreadStack data_020444c0
#define OSi_STACK_CHECKNUM_BOTTOM 0xfddb597dUL
#define OSi_STACK_CHECKNUM_TOP    0x7bf9dd5bUL
#define OSi_LAUNCHER_STACK_LO_DEFAULT SDK_SECTION_ARENA_DTCM_START
#define OSi_LAUNCHER_STACK_HI_MAX (HW_DTCM_SVC_STACK_ADDR - OSi_IRQ_STACKSIZE)
#define OSi_LAUNCHER_STACK_BOTTOM (HW_DTCM_SVC_STACK_ADDR - OSi_IRQ_STACKSIZE)
/* OSSystemWork.threadinfo_mainp lives at HW_SYS_WORK + 0x?? = 0x027fffa0. */
#define OSi_SYSTEMWORK_THREADINFO_MAINP (*(OSThreadInfo **)0x027fffa0)
extern int func_02002198(void *callback);   /* OS_SetSwitchThreadCallback */
#define OS_SetSwitchThreadCallback func_02002198
extern void OS_CreateThread(OSThread *thread, void (*func)(void *), void *arg, void *stack, u32 stackSize, u32 prio);
extern void OSi_IdleThreadProc(void *arg);

static inline void OS_InitThreadQueue(OSThreadQueue *queue)
{
    queue->head = queue->tail = NULL;
}

static inline void OS_SetCurrentThread(OSThread *thread)
{
    OSi_ThreadInfo.current = thread;
}

/* os_ownerInfo.c: the MAC address sits right after the NVRAMConfig (0x74 bytes) in the system
 * work's nvramUserInfo copy (HW_NVRAM_USER_INFO 0x027ffc80). */
#define HW_NVRAM_USER_INFO 0x027ffc80
#define NVRAMCONFIG_SIZE 0x74
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* func_02001ba4 -- NitroSDK os_thread.c: OS_InitThread. */
void func_02001ba4 (void)
{
    void * stackLo;

    if (OSi_IsThreadInitialized) {
        return;
    }

    OSi_IsThreadInitialized = TRUE;


    OSi_CurrentThreadPtr = &(OSi_ThreadInfo.current);
    OSi_LauncherThread.priority = OS_THREAD_LAUNCHER_PRIORITY;
    OSi_LauncherThread.id = 0;
    OSi_LauncherThread.state = OS_THREAD_STATE_READY;
    OSi_LauncherThread.next = NULL;
    OSi_LauncherThread.profiler = NULL;

    OSi_ThreadInfo.list = &OSi_LauncherThread;

    OS_SetCurrentThread(&OSi_LauncherThread);

    stackLo = (OSi_SYS_STACKSIZE <= 0) ?
              (void *)((u32)OSi_LAUNCHER_STACK_LO_DEFAULT - OSi_SYS_STACKSIZE) :
              (void *)((u32)OSi_LAUNCHER_STACK_HI_MAX - OSi_SYS_STACKSIZE);


    OSi_LauncherThread.stackBottom = (u32)OSi_LAUNCHER_STACK_BOTTOM;
    OSi_LauncherThread.stackTop = (u32)stackLo;
    OSi_LauncherThread.stackWarningOffset = 0;

    *(u32 *)(OSi_LauncherThread.stackBottom - sizeof(u32)) = OSi_STACK_CHECKNUM_BOTTOM;
    *(u32 *)OSi_LauncherThread.stackTop = OSi_STACK_CHECKNUM_TOP;

    OS_InitThreadQueue(&OSi_LauncherThread.joinQueue);


    OSi_ThreadInfo.isNeedRescheduling = FALSE;
    OSi_ThreadInfo.irqDepth = 0;

    OSi_SYSTEMWORK_THREADINFO_MAINP = &OSi_ThreadInfo;

    (void)OS_SetSwitchThreadCallback(NULL);

    OS_CreateThread(&OSi_IdleThread,
                    OSi_IdleThreadProc,
                    (void *)NULL,
                    OSi_IdleThreadStack + OSi_IDLE_THREAD_STACK_SIZE / sizeof(u32),
                    OSi_IDLE_THREAD_STACK_SIZE,
                    OS_THREAD_PRIORITY_MAX);

    OSi_IdleThread.priority = OS_THREAD_PRIORITY_MAX + 1;
    OSi_IdleThread.state = OS_THREAD_STATE_READY;
}
