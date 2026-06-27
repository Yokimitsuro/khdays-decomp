extern void OS_LockMutex(void *mutex);
extern void OS_UnlockMutex(void *mutex);
extern void func_0201ac34(void *p);
extern void func_0201d178(void *p);

extern char data_0204b608[];
extern char *data_0204ad8c[];

struct S {
    char _0[0x110];
    int flags;
    char _114[0x170 - 0x114];
    void (*cb)(void *);
};

void func_0201d0e0(struct S *p) {
    char *q;
    OS_LockMutex(data_0204b608);
    q = data_0204ad8c[1];
    if (q) {
        OS_LockMutex(q + 0xc8 + 0x400);
    }
    if ((p->flags << 30) >> 31) {
        func_0201ac34(p);
    }
    if ((p->flags << 31) >> 31) {
        p->cb(p);
    }
    func_0201d178(p);
    OS_UnlockMutex(data_0204b608);
    q = data_0204ad8c[1];
    if (q) {
        OS_UnlockMutex(q + 0xc8 + 0x400);
    }
}
