/* NitroSDK os_emulator.c: OSi_ConsoleTypeCache, the console type OS_GetConsoleType caches;
 * OSi_CONSOLE_NOT_DETECT (-1) until the first call. */
typedef unsigned int u32;
#define OSi_CONSOLE_NOT_DETECT 0xffffffff
u32 data_020422b0 = OSi_CONSOLE_NOT_DETECT;
