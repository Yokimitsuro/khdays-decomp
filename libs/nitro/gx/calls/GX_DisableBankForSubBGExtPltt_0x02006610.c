/* Clears sub-DISPCNT bit 30 and hands the sub BG extended-palette banks to disableBankForX_. */
extern void *disableBankForX_();
extern unsigned short data_020446ea;

void *GX_DisableBankForSubBGExtPltt_0x02006610(void) {
    volatile unsigned int *dispcnt = (volatile unsigned int *)0x4001000;
    *dispcnt = *dispcnt & ~0x40000000u;
    return disableBankForX_(&data_020446ea);
}
