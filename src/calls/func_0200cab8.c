extern int OS_GetCpsrIrq(void);
extern void PXIi_HandlerRecvFifoNotEmpty(void);

extern struct { char _0[0x1c]; int field_1c; } data_020463cc;
extern int data_020463e8;

void func_0200cab8(void) {
    int *p = &data_020463e8;
    if (data_020463cc.field_1c == 0) return;
    do {
        if (OS_GetCpsrIrq() == 0x80) {
            PXIi_HandlerRecvFifoNotEmpty();
        }
    } while (*p != 0);
}
