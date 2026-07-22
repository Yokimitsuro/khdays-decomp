/* Clears sub-DISPCNT bit 31 and hands the sub OBJ extended-palette banks to resetBankForX_. */
extern void *resetBankForX_();
extern unsigned short data_020446ec;

void *GX_DisableBankForSubOBJExtPltt(void) {
    volatile unsigned int *dispcnt = (volatile unsigned int *)0x4001000;
    *dispcnt = *dispcnt & ~0x80000000u;
    return resetBankForX_(&data_020446ec);
}
