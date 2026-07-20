/* OS_GetConsoleType: caches and returns the console-type word (0x82000001). */

extern int data_020422b0;

int OS_GetConsoleType(void) {
    return data_020422b0 = 0x82000001;
}
