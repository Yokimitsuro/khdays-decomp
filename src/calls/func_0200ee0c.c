typedef void (*CARDFunc)(void *);
typedef void (*CARDCallback)(void *);

extern int  CARDi_ReadFromCache(void *p);
extern void CARDi_ReadRomIDCore(void);
extern void CARDi_CheckPulledOutCore(void);
extern void OS_WakeupThread(void *queue);
extern void OS_WakeupThreadDirect(void *thread);
extern int  OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);

extern char data_02046b20[];
extern int *data_020464e0;

void func_0200ee0c(void)
{
    char *p;
    CARDCallback cb;
    void *cbArg;
    int state;
    unsigned flags;

    char *q = data_02046b20;
    if (CARDi_ReadFromCache(q) != 0) {
        (*(CARDFunc *)q)(q);
    }

    p = (char *)&data_020464e0;
    CARDi_ReadRomIDCore();
    CARDi_CheckPulledOutCore();

    *(*(int **)p) = 0;
    cb    = *(CARDCallback *)(p + 0x38);
    cbArg = *(void **)(p + 0x3c);

    state = OS_DisableInterrupts();
    flags = *(unsigned *)(p + 0x114);
    *(unsigned *)(p + 0x114) = flags & ~0x4cu;
    OS_WakeupThread(p + 0x10c);
    if (*(unsigned *)(p + 0x114) & 0x10) {
        OS_WakeupThreadDirect(p + 0x44);
    }
    OS_RestoreInterrupts(state);

    if (cb != 0) {
        cb(cbArg);
    }
}
