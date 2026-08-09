/* MI_SetWramBank: selects the WRAM bank via WRAMCNT (0x04000247). */

void MI_SetWramBank(unsigned char bank) {
    *(volatile unsigned char *)0x04000247 = bank;
}
