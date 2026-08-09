/* Nintendo DS BIOS SWI 0x06 veneer. */
asm void Halt(void)
{
    swi 0x06
    bx lr
}
