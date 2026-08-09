/* Nintendo DS BIOS SWI 0x11 veneer. */
asm void LZ77UnCompReadNormalWrite8bit(register const void *source,
                                       register void *destination)
{
    swi 0x11
    bx lr
}
