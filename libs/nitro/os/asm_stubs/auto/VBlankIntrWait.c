/* Nintendo DS BIOS SWI 0x05 veneer. */
asm void VBlankIntrWait(void)
{
    mov r2, #0
    swi 0x05
    bx lr
}
