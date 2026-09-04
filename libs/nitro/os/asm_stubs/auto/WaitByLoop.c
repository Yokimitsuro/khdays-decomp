/* Nintendo DS BIOS SWI 0x03 veneer. */
asm void WaitByLoop(void)
{
    swi 0x03
    bx lr
}
