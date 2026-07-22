/* Sets up the main-RAM arena and opens the two extra protection regions.  When the flag at
 * data_02044588+4 is set the console type has to report 1 first; when it is clear the check
 * is skipped entirely (the ROM's `beq` jumps PAST the check, not to the epilogue). */
extern int func_020029d0(int arena);
extern void OS_SetArenaHi(int arena, int hi);
extern int func_02002ab4(int arena);
extern void OS_SetArenaLo(int arena, int lo);
extern int OS_GetConsoleType(void);
extern void OS_SetProtectionRegion1(unsigned int v);
extern void OS_SetProtectionRegion2(unsigned int v);
extern int data_02044588[];

void OS_InitArenaEx(void) {
    OS_SetArenaHi(2, func_020029d0(2));
    OS_SetArenaLo(2, func_02002ab4(2));
    if (data_02044588[1] != 0) {
        if ((OS_GetConsoleType() & 3) != 1) {
            return;
        }
    }
    OS_SetProtectionRegion1(0x200002b);
    OS_SetProtectionRegion2(0x23e0021);
}
