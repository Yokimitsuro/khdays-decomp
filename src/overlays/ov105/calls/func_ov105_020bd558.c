extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);

extern int func_ov105_020bd03c(void);
extern char *func_ov105_020bd02c(void);

/* Records the caller's callback on the wireless session, if the session is idle enough to take it. */
int func_ov105_020bd558(int callback) {
    int enabled = OS_DisableInterrupts();
    int err = func_ov105_020bd03c();
    if (err != 0) {
        OS_RestoreInterrupts(enabled);
        return err;
    }
    *(int *)(func_ov105_020bd02c() + 0xc8) = callback;
    OS_RestoreInterrupts(enabled);
    return 0;
}
