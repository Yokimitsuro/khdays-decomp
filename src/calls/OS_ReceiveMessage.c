extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern void func_02001f10(void *queue);
extern void OS_WakeupThread(void *queue);
extern long long func_02020400(int a, int b);

/* Pops the oldest message. Without the blocking flag an empty queue fails instead of waiting. */
int OS_ReceiveMessage(char *q, void **out, int flags) {
    int enabled = OS_DisableInterrupts();
    while (*(int *)(q + 0x1c) == 0) {
        if ((flags & 1) == 0) {
            OS_RestoreInterrupts(enabled);
            return 0;
        }
        func_02001f10(q + 8);
    }
    if (out != 0) {
        *out = (*(void ***)(q + 0x10))[*(int *)(q + 0x18)];
    }
    *(int *)(q + 0x18) = (int)(func_02020400(
        *(int *)(q + 0x18) + 1, *(int *)(q + 0x14)) >> 32);
    *(int *)(q + 0x1c) = *(int *)(q + 0x1c) - 1;
    OS_WakeupThread(q);
    OS_RestoreInterrupts(enabled);
    return 1;
}
