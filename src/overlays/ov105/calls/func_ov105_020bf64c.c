/* func_ov105_020bf64c -- fatal-check the scene state, ov105. When the scene reaches
 * error state 8, logs code 9 (func_ov105_020be49c) and terminates. */
extern void func_ov105_020be49c(int);
extern void OS_Terminate(void);
void func_ov105_020bf64c(char *scene) {
    if (*(unsigned short *)(scene + 2) == 8) {
        func_ov105_020be49c(9);
        OS_Terminate();
    }
}
