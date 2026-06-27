extern void func_020021d0(void);
extern void OSi_UnlockAllMutex(void *thread);
extern void OSi_RemoveSpecifiedLinkFromQueue(void *queue, void *thread);
extern void func_02001a94(void *thread);
extern void OS_WakeupThread(void *queue);
extern void func_02002204(void);
extern void OS_RescheduleThread(void);
extern void OS_Terminate(void);
extern void **data_0204430c[];

void func_02001ea0(void)
{
    void *thread = data_0204430c[2][0];
    void *queue;

    func_020021d0();
    OSi_UnlockAllMutex(thread);

    queue = *(void **)((char *)thread + 0x78);
    if (queue != 0) {
        OSi_RemoveSpecifiedLinkFromQueue(queue, thread);
    }

    func_02001a94(thread);
    *(int *)((char *)thread + 0x64) = 2;
    OS_WakeupThread((char *)thread + 0x9c);
    func_02002204();
    OS_RescheduleThread();
    OS_Terminate();
}
