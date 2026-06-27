typedef int BOOL;

typedef struct OSContext {
    char dummy[1];
} OSContext;

typedef void (*OSSwitchThreadCallback)(void *from, void *to);

extern BOOL OS_SaveContext(OSContext *context);
extern void OS_LoadContext(OSContext *context);
extern int OS_GetProcMode(void);
extern void *OSi_SelectThread(void);

struct Globals {
    /* +0x00 */ OSSwitchThreadCallback systemCallback;
    /* +0x04 */ unsigned int rescheduleCount;
    /* +0x08 */ void ***currentThreadPtr;
    /* +0x0c */ char _pad[0x18];
    /* +0x24 */ unsigned short isNeedRescheduling;
    /* +0x26 */ unsigned short irqDepth;
    /* +0x28 */ void *currentThread;
    /* +0x2c */ void *list;
    /* +0x30 */ OSSwitchThreadCallback switchCallback;
};

/* Force a separate symbol for the second literal pool entry */
struct ThreadInfo2 {
    /* +0x00 */ unsigned short isNeedRescheduling;
    /* +0x02 */ unsigned short irqDepth;
    /* +0x04 */ void *currentThread;
    /* +0x08 */ void *list;
    /* +0x0c */ OSSwitchThreadCallback switchCallback;
};
extern struct ThreadInfo2 data_02044330;

extern struct Globals data_0204430c;

void OSi_RescheduleThread(void) {
    struct ThreadInfo2 *info;
    void **curPtr;
    void *cur;
    void *next;
    OSSwitchThreadCallback cb;

    if (data_0204430c.rescheduleCount != 0) return;

    info = &data_02044330;
    if (data_0204430c.irqDepth != 0 || OS_GetProcMode() == 0x12) {
        info->isNeedRescheduling = 1;
        return;
    }

    curPtr = (void **)data_0204430c.currentThreadPtr;
    cur = *curPtr;
    next = OSi_SelectThread();

    if (cur == next || next == 0) return;

    if (*(int *)((char *)cur + 0x64) != 2) {
        if (OS_SaveContext((OSContext *)cur)) return;
    }

    cb = data_0204430c.systemCallback;
    if (cb != 0) {
        cb(cur, next);
    }

    cb = info->switchCallback;
    if (cb != 0) {
        cb(cur, next);
    }

    data_0204430c.currentThread = next;
    OS_LoadContext((OSContext *)next);
}
