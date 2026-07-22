/* Clears sub-DISPCNT bit 30 and hands the sub BG extended-palette banks to resetBankForX_. */
extern void *resetBankForX_();
extern unsigned short data_020446ea;

void *GX_DisableBankForSubBGExtPltt(void) {
    volatile unsigned int *dispcnt = (volatile unsigned int *)0x4001000;
    *dispcnt = *dispcnt & ~0x40000000u;
    return resetBankForX_(&data_020446ea);
}
