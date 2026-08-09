/* Nintendo DS BIOS SWI 0x12 veneer. */
asm void LZ77UnCompReadByCallbackWrite16bit(register const void *source,
                                            register void *destination)
{
    swi 0x12
    bx lr
}
