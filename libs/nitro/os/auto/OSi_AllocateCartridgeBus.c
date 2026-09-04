typedef unsigned short u16;

/* External memory control. Bit 7 holds the GBA-slot access rights: 0 gives the
   cartridge bus to the ARM9, 1 to the ARM7. */
#define REG_EXMEM_CNT (*(volatile u16 *)0x04000204)

void OSi_AllocateCartridgeBus(void)
{
    REG_EXMEM_CNT &= ~0x0080;
}
