/* Clears the sleep slot and its thread's alarm pointer, then wakes the thread. */
extern void *OS_WakeupThreadDirect();

void *OSi_SleepAlarmCallback(char **slot) {
    char *thread = *slot;
    *slot = 0;
    *(int *)(thread + 0xb0) = 0;
    return OS_WakeupThreadDirect(thread);
}
