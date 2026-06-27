extern void OS_LockMutex(void *mutex);
extern void OS_UnlockMutex(void *mutex);
extern void func_0201aa18(void *p);
extern void func_0201d0e0(void *p);

extern char data_0204b608[];
extern char *data_0204ad8c[];

struct S {
    char _0[0x120];
    int field_120;
    unsigned char field_124;
    char _125[0x12c - 0x125];
    int field_12c;
    int field_130;
};

void func_0201d3c4(int key, int arg1, struct S *p) {
    char *q;
    if (key != p->field_12c) {
        return;
    }
    OS_LockMutex(data_0204b608);
    q = data_0204ad8c[1];
    if (q) {
        OS_LockMutex(q + 0xc8 + 0x400);
    }
    func_0201d0e0(p);
    p->field_12c = 0;
    p->field_130 = 0;
    p->field_124 = 0;
    if (p->field_120 > 0) {
        func_0201aa18(p);
        p->field_120 = 0;
    }
    OS_UnlockMutex(data_0204b608);
    q = data_0204ad8c[1];
    if (q) {
        OS_UnlockMutex(q + 0xc8 + 0x400);
    }
}
