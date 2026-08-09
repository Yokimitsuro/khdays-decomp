extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern void OS_WakeupThread(void *queue);
extern void FSi_ReleaseCommand(void *file, int result);
extern void *FSi_NextCommand(void *arc);
extern void FSi_ExecuteAsyncCommand(void *file);

static inline int FSi_IsArchiveAsync(char *arc) {
    return (*(volatile int *)(arc + 0x1c) & 0x100) != 0;
}

/* Called by an archive when its transfer completes: finishes the command and starts the next one,
 * or just wakes the synchronous waiter. */
void FS_NotifyArchiveAsyncEnd(char *arc, int result) {
    char *file;
    void *next;
    int enabled;
    if (FSi_IsArchiveAsync(arc)) {
        file = *(char **)(arc + 0x24);
        *(volatile int *)(arc + 0x1c) &= ~0x100;
        FSi_ReleaseCommand(file, result);
        next = FSi_NextCommand(arc);
        if (next == 0) {
            return;
        }
        FSi_ExecuteAsyncCommand(next);
        return;
    }
    file = *(char **)(arc + 0x24);
    enabled = OS_DisableInterrupts();
    *(int *)(file + 0x14) = result;
    *(volatile int *)(arc + 0x1c) &= ~0x200;
    OS_WakeupThread(arc + 0xc);
    OS_RestoreInterrupts(enabled);
}
