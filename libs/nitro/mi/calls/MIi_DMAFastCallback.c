/* MIi_DMAFastCallback: clears the pending flag and dispatches the stored DMA callback. */

extern int data_020446b0;

void MIi_DMAFastCallback(void) {
    void (*cb)(int);
    int arg;

    data_020446b0 = 0;
    cb = *(void (**)(int))((int)&data_020446b0 + 0x10);
    arg = *(int *)((int)&data_020446b0 + 0x14);
    if (cb != 0) {
        cb(arg);
    }
}
