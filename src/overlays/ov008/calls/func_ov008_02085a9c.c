extern char *data_ov008_02090fac;
extern int func_ov008_02054788(void *p, int id);
extern void func_ov008_02054ba4(void *p, int cell, int on);

/* Greys out the two scroll arrows according to whether the list can move up or down. */
void func_ov008_02085a9c(void) {
    char *st = *(char **)&data_ov008_02090fac;
    char *view = st + 0xc3c4;
    char *arrows = st + 0x2ab0;
    func_ov008_02054ba4(arrows, func_ov008_02054788(arrows, 4), *(int *)(view + 4) != 0);
    func_ov008_02054ba4(arrows, func_ov008_02054788(arrows, 5),
                        (unsigned int)(*(int *)(view + 4) + 8) < (unsigned int)*(int *)(view + 8));
}
