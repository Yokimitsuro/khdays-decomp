/* Nintendo DS BIOS SWI 0x0d veneer. */
asm void Sqrt(void)
{
    swi 0x0d
    bx lr
}
