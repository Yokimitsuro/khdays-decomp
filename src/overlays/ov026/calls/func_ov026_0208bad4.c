extern char *data_ov026_02091368;
extern void func_ov026_020889c0(void);
extern int func_ov026_0208427c(void *p, int a);
extern void func_ov026_020843e8(void *p, int a, int b);
extern void func_ov026_02086f70(void);
extern void func_ov026_0208a774(void);
extern void func_ov026_0208ab5c(void);

/* Per-frame tick: keeps the highlighted entry's sound playing, resets the fade counter when we are
 * about to re-enter the screen, and returns the next state. */
void *func_ov026_0208bad4(void) {
    char *st = *(char **)&data_ov026_02091368;
    char **list;
    func_ov026_020889c0();
    if (*(int *)(st + 0xc250) == 2) {
        list = *(char ***)(st + 0xc3d0);
        if (list != 0) {
            if (*(unsigned int *)(*(char **)(list[*(int *)(st + 0xc3c4)] + 0xc) + 0x24) < 0x3f) {
                func_ov026_020843e8(*(char **)&data_ov026_02091368 + 0x2ab0,
                    func_ov026_0208427c(*(char **)&data_ov026_02091368 + 0x2ab0, 0x3f), 1);
            }
        }
    }
    if (*(void **)(st + 0xc3d8) == (void *)&func_ov026_0208ab5c) {
        func_ov026_02086f70();
        *(int *)st = 0;
    }
    func_ov026_0208a774();
    return *(void **)(st + 0xc3d8);
}
