extern int data_ov002_0207fa00;
extern unsigned char data_0204c240;
extern unsigned char data_0204c248[];

extern unsigned long long func_ov002_0206f604(void);
extern int func_02020368(unsigned long long value, unsigned int arg2, int arg3);
extern int func_ov002_0206dbe0(void);
extern void func_ov002_02061d64(int nKind, int nValue);

/* Recompute the displayed rate for the active slot, or blank it when no slot
 * is selected. Only runs while the enable bit is set. */
void func_ov002_0206db5c(void)
{
    int pPanel;

    pPanel = *(int *)&data_ov002_0207fa00 + 0x8ba8;

    if ((data_0204c240 & 4) == 0) {
        return;
    }

    if (data_0204c248[4] == 0xff) {
        *(int *)(pPanel + 0x1c) = -1;
        return;
    }

    *(int *)(pPanel + 0x1c) = func_02020368(func_ov002_0206f604() << 6, 0x82ea, 0);
    *(short *)(pPanel + 0x20) = data_0204c248[4];

    func_ov002_02061d64(0, func_ov002_0206dbe0());
}
