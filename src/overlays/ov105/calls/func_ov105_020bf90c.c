/* func_ov105_020bf90c -- kick the scene-manager idle handler, ov105. When the manager
 * reports idle (func_ov105_020bf008 == 0), runs func_ov105_020be49c(0xa). */
extern int func_ov105_020bf008(void);
extern void func_ov105_020be49c(int);
void func_ov105_020bf90c(void) {
    if (func_ov105_020bf008() == 0) {
        func_ov105_020be49c(0xa);
    }
}
