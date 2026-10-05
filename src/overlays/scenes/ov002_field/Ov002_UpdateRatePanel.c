extern int data_ov002_0207fa00;
extern unsigned char data_0204c240;
extern unsigned char data_0204c248[];

extern unsigned long long Ov002_GetTimeoutTicks(void);
extern unsigned long long func_02020368(unsigned long long dividend, unsigned long long divisor);
extern int Ov002_GetRootField8bc8(void);
extern void Ov002_StartHudTimer(int nKind, int nValue);

/* Recompute the displayed rate for the active slot, or blank it when no slot
 * is selected. Only runs while the enable bit is set. */
void Ov002_UpdateRatePanel(void)
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

    *(int *)(pPanel + 0x1c) = (int)func_02020368(Ov002_GetTimeoutTicks() << 6, 0x82ea);
    *(short *)(pPanel + 0x20) = data_0204c248[4];

    Ov002_StartHudTimer(0, Ov002_GetRootField8bc8());
}
