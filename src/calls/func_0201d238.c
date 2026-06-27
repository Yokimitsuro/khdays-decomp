extern void OS_CreateThread(void *thread, void (*func)(void *), void *arg, void *stack, unsigned stackSize, unsigned prio);
extern void NNS_FndInitList(void *list, int offset);
extern void OS_InitMutex(void *mutex);
extern void OS_WakeupThreadDirect(void *thread);
extern void func_0201e09c(void *arg);

void func_0201d238(char *p, unsigned prio) {
    OS_CreateThread(p, func_0201e09c, p, p + 0x4c0, 0x400, prio);
    NNS_FndInitList(p + 0x4e0, 0);
    OS_InitMutex(p + 0x4c8);
    *(int *)(p + 0x4c4) = 0;
    *(int *)(p + 0x4c0) = 0;
    OS_WakeupThreadDirect(p);
}
