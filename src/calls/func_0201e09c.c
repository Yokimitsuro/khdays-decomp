extern void func_02001f10(void *arg0);
extern void OS_LockMutex(void *mutex);
extern void OS_UnlockMutex(void *mutex);
extern void *func_0201d308(void *list);
extern void func_0201d398(void *object);
extern void func_0201d6dc(void);

void func_0201e09c(char *p) {
    void *object;
    void *mutex;

    mutex = p + 0x4c8;

wait:
    func_02001f10(p + 0x4c0);

loop:
    OS_LockMutex(mutex);
    object = func_0201d308(p + 0x4e0);
    if (object == 0) {
        OS_UnlockMutex(mutex);
        goto wait;
    }

    func_0201d6dc();
    func_0201d398(object);
    OS_UnlockMutex(mutex);
    goto loop;
}
