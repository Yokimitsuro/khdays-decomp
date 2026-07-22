/* Clears sub-DISPCNT bit 31 and hands the sub OBJ extended-palette banks to disableBankForX_. */
extern void *disableBankForX_();
extern unsigned short data_020446ec;

void *GX_DisableBankForSubOBJExtPltt_0x02006638(void) {
    volatile unsigned int *dispcnt = (volatile unsigned int *)0x4001000;
    *dispcnt = *dispcnt & ~0x80000000u;
    return disableBankForX_(&data_020446ec);
}
