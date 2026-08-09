extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern void func_02001f10(void *queue);
extern void OS_WakeupThread(void *queue);
extern long long func_02020400(int a, int b);

/* Pushes a message onto the FRONT of the queue (jam). Without the blocking flag a full queue
 * fails instead of waiting. */
int OS_JamMessage(char *q, void *msg, int flags) {
    int enabled = OS_DisableInterrupts();
    void **slots;
    while (*(int *)(q + 0x14) <= *(int *)(q + 0x1c)) {
        if ((flags & 1) == 0) {
            OS_RestoreInterrupts(enabled);
            return 0;
        }
        func_02001f10(q);
    }
    *(int *)(q + 0x18) = (int)(func_02020400(
        *(int *)(q + 0x18) + *(int *)(q + 0x14) - 1, *(int *)(q + 0x14)) >> 32);
    slots = *(void ***)(q + 0x10);
    slots[*(int *)(q + 0x18)] = msg;
    *(int *)(q + 0x1c) = *(int *)(q + 0x1c) + 1;
    OS_WakeupThread(q + 8);
    OS_RestoreInterrupts(enabled);
    return 1;
}
