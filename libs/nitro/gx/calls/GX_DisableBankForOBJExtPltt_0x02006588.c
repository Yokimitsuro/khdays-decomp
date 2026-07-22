/* Clears DISPCNT bit 31 and hands the main OBJ extended-palette banks to disableBankForX_. */
extern void *disableBankForX_();
extern unsigned short data_020446e4;

void *GX_DisableBankForOBJExtPltt_0x02006588(void) {
    volatile unsigned int *dispcnt = (volatile unsigned int *)0x4000000;
    *dispcnt = *dispcnt & ~0x80000000;
    return disableBankForX_(&data_020446e4);
}
