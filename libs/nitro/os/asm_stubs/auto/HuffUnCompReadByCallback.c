/* Nintendo DS BIOS SWI 0x13 veneer. */
asm void HuffUnCompReadByCallback(void)
{
    swi 0x13
    bx lr
}
