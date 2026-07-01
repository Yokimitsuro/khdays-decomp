extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int mask);

extern struct { char _0[0x1c]; int field_1c; } data_020463cc;

int PXIi_TryLock(void) {
    int mask = OS_DisableInterrupts();
    if (data_020463cc.field_1c != 0) {
        OS_RestoreInterrupts(mask);
        return 0;
    }
    data_020463cc.field_1c = 1;
    OS_RestoreInterrupts(mask);
    return 1;
}
