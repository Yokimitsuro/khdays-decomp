typedef int BOOL;

/* Arena ids, in the order NitroSDK declares them. Id 1 is the sub-processor's
   private slice of main memory and is not touched here; id 2 is the extended
   main memory, which retail hardware does not have, so it is emptied instead
   of being seeded from the linker's figures. */
#define OS_ARENA_MAIN       0
#define OS_ARENA_MAINEX     2
#define OS_ARENA_ITCM       3
#define OS_ARENA_DTCM       4
#define OS_ARENA_SHARED     5
#define OS_ARENA_WRAM_MAIN  6

/* The two getters return the boundaries the linker laid down for an arena;
   the setters publish them as the live allocation window. */
extern void *func_020029d0(int nArena);
extern void *func_02002ab4(int nArena);
extern void OS_SetArenaHi(int nArena, void *pAddress);
extern void OS_SetArenaLo(int nArena, void *pAddress);

/* Set once, so a second call is a no-op rather than a reset that would strand
   everything already allocated. */
extern BOOL data_02044588;

void OS_InitArena(void)
{
    if (data_02044588) {
        return;
    }
    data_02044588 = 1;

    OS_SetArenaHi(OS_ARENA_MAIN, func_020029d0(OS_ARENA_MAIN));
    OS_SetArenaLo(OS_ARENA_MAIN, func_02002ab4(OS_ARENA_MAIN));

    OS_SetArenaLo(OS_ARENA_MAINEX, (void *)0);
    OS_SetArenaHi(OS_ARENA_MAINEX, (void *)0);

    OS_SetArenaHi(OS_ARENA_ITCM, func_020029d0(OS_ARENA_ITCM));
    OS_SetArenaLo(OS_ARENA_ITCM, func_02002ab4(OS_ARENA_ITCM));

    OS_SetArenaHi(OS_ARENA_DTCM, func_020029d0(OS_ARENA_DTCM));
    OS_SetArenaLo(OS_ARENA_DTCM, func_02002ab4(OS_ARENA_DTCM));

    OS_SetArenaHi(OS_ARENA_SHARED, func_020029d0(OS_ARENA_SHARED));
    OS_SetArenaLo(OS_ARENA_SHARED, func_02002ab4(OS_ARENA_SHARED));

    OS_SetArenaHi(OS_ARENA_WRAM_MAIN, func_020029d0(OS_ARENA_WRAM_MAIN));
    OS_SetArenaLo(OS_ARENA_WRAM_MAIN, func_02002ab4(OS_ARENA_WRAM_MAIN));
}
