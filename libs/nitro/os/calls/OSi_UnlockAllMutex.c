/* Releases every mutex the thread still holds, waking each queue in turn. */
extern void *OSi_RemoveMutexLinkFromQueue(void *link);
extern void OS_WakeupThread(void *queue);

void OSi_UnlockAllMutex(char *thread) {
    void *q;
    int zero = 0;
    if (*(int *)(thread + 0x88) == 0) {
        return;
    }
    do {
        q = OSi_RemoveMutexLinkFromQueue(thread + 0x88);
        *(int *)((char *)q + 0xc) = zero;
        *(int *)((char *)q + 8) = zero;
        OS_WakeupThread(q);
    } while (*(int *)(thread + 0x88) != 0);
}
