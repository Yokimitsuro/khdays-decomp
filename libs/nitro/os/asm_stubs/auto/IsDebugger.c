/* Nintendo DS BIOS SWI 0x0f veneer. */
asm int IsDebugger(void)
{
    swi 0x0f
    bx lr
}
