/* Clears EXMEMCNT bit 11 so the ARM9 owns the card bus. */
void OSi_AllocateCardBus(void) {
    volatile unsigned short *exmemcnt = (volatile unsigned short *)0x4000204;
    *exmemcnt = (unsigned short)(*exmemcnt & ~0x800);
}
