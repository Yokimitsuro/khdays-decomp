extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern void OSi_SetTimer(void *alarm);
extern char data_02044674;

/* Cancels an armed alarm: unlink it from the fire list and, if it was the head, reprogram the
 * timer for whatever comes next. */
void func_02003618(char *alarm) {
    int enabled = OS_DisableInterrupts();
    char *next;
    char *prev;
    if (*(int *)alarm == 0) {
        OS_RestoreInterrupts(enabled);
        return;
    }
    next = *(char **)(alarm + 0x18);
    if (next == 0) {
        *(char **)((char *)&data_02044674 + 8) = *(char **)(alarm + 0x14);
    } else {
        *(char **)(next + 0x14) = *(char **)(alarm + 0x14);
    }
    prev = *(char **)(alarm + 0x14);
    if (prev != 0) {
        *(char **)(prev + 0x18) = next;
    } else {
        *(char **)((char *)&data_02044674 + 4) = next;
        if (next != 0) {
            OSi_SetTimer(next);
        }
    }
    *(int *)alarm = 0;
    *(int *)(alarm + 0x1c) = 0;
    *(int *)(alarm + 0x20) = 0;
    OS_RestoreInterrupts(enabled);
}
