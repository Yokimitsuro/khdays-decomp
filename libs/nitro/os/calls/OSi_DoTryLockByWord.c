extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern int OS_DisableInterrupts_IrqAndFiq(void);
extern void OS_RestoreInterrupts_IrqAndFiq(int state);

extern int MI_SwapWord(unsigned short id, void *lock);

/* Takes a hardware lock word if it is free, running the caller's hook while still inside the
 * critical section. Returns the previous owner (0 = we got it). */
int OSi_DoTryLockByWord(unsigned short id, char *lock, void (*onLock)(void), int fiq) {
    int enabled;
    int prev;
    if (fiq != 0) {
        enabled = OS_DisableInterrupts_IrqAndFiq();
    } else {
        enabled = OS_DisableInterrupts();
    }
    prev = MI_SwapWord(id, lock);
    if (prev == 0) {
        if (onLock != 0) {
            onLock();
        }
        *(unsigned short *)(lock + 4) = id;
    }
    if (fiq != 0) {
        OS_RestoreInterrupts_IrqAndFiq(enabled);
    } else {
        OS_RestoreInterrupts(enabled);
    }
    return prev;
}
