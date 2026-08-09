/* Nintendo DS BIOS SWI 0x14 veneer. */
asm void RLUnCompReadNormalWrite8bit(register const void *source,
                                     register void *destination)
{
    swi 0x14
    bx lr
}
