extern char *data_ov008_02090fac;
extern void func_ov008_02085b10(void);
extern int func_ov008_02054788(void *p, int a);
extern void func_ov008_02054ba4(void *p, int a, int b);
extern void func_ov008_020840c0(void);
extern void func_ov008_020878c4(void);
extern void func_ov008_02087cac(void);

/* Per-frame tick: keeps the highlighted entry's sound playing, resets the fade counter when we are
 * about to re-enter the screen, and returns the next state. */
void *func_ov008_02088c24(void) {
    char *st = *(char **)&data_ov008_02090fac;
    char **list;
    func_ov008_02085b10();
    if (*(int *)(st + 0xc250) == 2) {
        list = *(char ***)(st + 0xc3d0);
        if (list != 0) {
            if (*(unsigned int *)(*(char **)(list[*(int *)(st + 0xc3c4)] + 0xc) + 0x24) < 0x3f) {
                func_ov008_02054ba4(*(char **)&data_ov008_02090fac + 0x2ab0,
                    func_ov008_02054788(*(char **)&data_ov008_02090fac + 0x2ab0, 0x3f), 1);
            }
        }
    }
    if (*(void **)(st + 0xc3d8) == (void *)&func_ov008_02087cac) {
        func_ov008_020840c0();
        *(int *)st = 0;
    }
    func_ov008_020878c4();
    return *(void **)(st + 0xc3d8);
}
