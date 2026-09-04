typedef unsigned int u32;

/* Bit 0..1 of the console type is the main-memory size; 1 means the 4 MB retail
   part, which has no extended region above it. */
#define OS_CONSOLE_SIZE_MASK  3
#define OS_CONSOLE_SIZE_4MB   1

extern u32 OS_GetConsoleType(void);

/* Word 0 is the one-shot arena guard; word 1 says whether the extended main
   memory region was declared at all. */
extern u32 data_02044588[];

/* Low boundary of each arena as the linker laid it out. These are link-time
   constants, not relocated symbols, so they appear as literals. */
void *func_02002ab4(int nArena)
{
    switch (nArena) {
    case 0:
        return (void *)0x020d73e0;

    case 2:
        /* Both rejections land on one shared exit in the ROM, so the test is a
           single disjunction with the address returned on the fall-through. */
        if (data_02044588[1] == 0 ||
            (OS_GetConsoleType() & OS_CONSOLE_SIZE_MASK) == OS_CONSOLE_SIZE_4MB) {
            return (void *)0;
        }
        return (void *)0x023e0000;

    case 3:
        return (void *)0x01fffee0;

    case 4:
        return (void *)0x027e0e60;

    case 5:
        return (void *)0x027ff000;

    case 6:
        return (void *)0x037f8000;
    }

    return (void *)0;
}
