/* Clears DISPCNT bit 30 and hands the main BG extended-palette banks to resetBankForX_. */
extern void *resetBankForX_();
extern unsigned short data_020446e2;

void *GX_DisableBankForBGExtPltt(void) {
    volatile unsigned int *dispcnt = (volatile unsigned int *)0x4000000;
    *dispcnt = *dispcnt & ~0x40000000;
    return resetBankForX_(&data_020446e2);
}
