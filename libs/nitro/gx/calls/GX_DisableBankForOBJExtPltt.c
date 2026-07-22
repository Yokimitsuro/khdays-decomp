/* Clears DISPCNT bit 31 and hands the main OBJ extended-palette banks to resetBankForX_. */
extern void *resetBankForX_();
extern unsigned short data_020446e4;

void *GX_DisableBankForOBJExtPltt(void) {
    volatile unsigned int *dispcnt = (volatile unsigned int *)0x4000000;
    *dispcnt = *dispcnt & ~0x80000000;
    return resetBankForX_(&data_020446e4);
}
