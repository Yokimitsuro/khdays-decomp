/* Nintendo DS BIOS SWI 0x00 veneer. */
asm void SoftReset(void)
{
    swi 0x00
    bx lr
}
