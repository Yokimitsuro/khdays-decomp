typedef unsigned short u16;
typedef unsigned int u32;

/* Nintendo DS BIOS SWI 0x0e veneer. */
asm u16 GetCRC16(register u16 initialValue, register const void *data,
                 register u32 size)
{
    swi 0x0e
    bx lr
}
