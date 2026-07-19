extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern int func_ov105_020bd03c(void);
extern int func_ov105_020bd0a0(int a, int b);
extern void func_ov105_020bd4dc(void);
extern void PXI_SetFifoRecvCallback(int tag, void *callback);
extern char data_ov105_020bfa20;

/* Shuts the wireless stack down: refuses if a session is still up, otherwise unhooks the PXI
 * handler and clears the session slot. */
int func_ov105_020bce30(void) {
    int enabled = OS_DisableInterrupts();
    int err;
    if (func_ov105_020bd03c() != 0) {
        OS_RestoreInterrupts(enabled);
        return 3;
    }
    err = func_ov105_020bd0a0(1, 0);
    if (err != 0) {
        return err;
    }
    func_ov105_020bd4dc();
    PXI_SetFifoRecvCallback(0xa, 0);
    *(int *)((char *)&data_ov105_020bfa20 + 4) = 0;
    *(short *)&data_ov105_020bfa20 = 0;
    OS_RestoreInterrupts(enabled);
    return 0;
}
