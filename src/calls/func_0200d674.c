extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int mask);
extern int RTCi_ReadRawTimeAsync(void);

extern int data_02046438[];

int func_0200d674(void *time, void *callback, void *arg) {
    int mask;

    mask = OS_DisableInterrupts();
    if (data_02046438[3] != 0) {
        OS_RestoreInterrupts(mask);
        return 1;
    }
    data_02046438[3] = 1;
    OS_RestoreInterrupts(mask);
    data_02046438[8] = 1;
    data_02046438[9] = 0;
    data_02046438[5] = (int)time;
    data_02046438[4] = (int)callback;
    data_02046438[7] = (int)arg;
    if (RTCi_ReadRawTimeAsync() != 0) {
        return 0;
    }
    return 3;
}
