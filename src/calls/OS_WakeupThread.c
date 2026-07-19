extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern char *OSi_RemoveLinkFromQueue(void *queue);
extern void OSi_RescheduleThread(void);

/* Makes every thread waiting on the queue runnable and empties the queue. */
void OS_WakeupThread(char *queue) {
    int enabled = OS_DisableInterrupts();
    if (*(int *)queue != 0) {
        while (*(int *)queue != 0) {
            char *thread = OSi_RemoveLinkFromQueue(queue);
            *(int *)(thread + 0x64) = 1;
            *(int *)(thread + 0x78) = 0;
            *(int *)(thread + 0x80) = 0;
            *(int *)(thread + 0x7c) = 0;
        }
        *(int *)(queue + 4) = 0;
        *(int *)queue = 0;
        OSi_RescheduleThread();
    }
    OS_RestoreInterrupts(enabled);
}
