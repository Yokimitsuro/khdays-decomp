struct SVCUnpackBitsParam;

/* Nintendo DS BIOS SWI 0x10 veneer. */
asm void BitUnPack(register const void *source, register void *destination,
                   register const struct SVCUnpackBitsParam *parameters)
{
    swi 0x10
    bx lr
}
