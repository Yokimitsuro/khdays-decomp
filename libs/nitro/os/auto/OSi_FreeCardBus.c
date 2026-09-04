typedef unsigned short u16;

/* External memory control. Bit 11 holds the NDS-slot access rights: 0 gives the
   card bus to the ARM9, 1 to the ARM7. */
#define REG_EXMEM_CNT (*(volatile u16 *)0x04000204)

void OSi_FreeCardBus(void)
{
    REG_EXMEM_CNT |= 0x0800;
}
