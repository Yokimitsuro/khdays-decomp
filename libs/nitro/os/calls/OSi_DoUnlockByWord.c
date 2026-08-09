extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern int OS_DisableInterrupts_IrqAndFiq(void);
extern void OS_RestoreInterrupts_IrqAndFiq(int state);

/* Releases a hardware lock word. Fails with -2 if the caller is not the owner. */
int OSi_DoUnlockByWord(unsigned short id, char *lock, void (*onUnlock)(void), int fiq) {
    int enabled;
    if (id != *(unsigned short *)(lock + 4)) {
        return ~1;
    }
    if (fiq != 0) {
        enabled = OS_DisableInterrupts_IrqAndFiq();
    } else {
        enabled = OS_DisableInterrupts();
    }
    *(unsigned short *)(lock + 4) = 0;
    if (onUnlock != 0) {
        onUnlock();
    }
    *(int *)lock = 0;
    if (fiq != 0) {
        OS_RestoreInterrupts_IrqAndFiq(enabled);
    } else {
        OS_RestoreInterrupts(enabled);
    }
    return 0;
}
