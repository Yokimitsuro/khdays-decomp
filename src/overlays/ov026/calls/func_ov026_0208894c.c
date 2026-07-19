extern char *data_ov026_02091368;
extern int func_ov026_0208427c(void *p, int id);
extern void func_ov026_020843e8(void *p, int cell, int on);

/* Greys out the two scroll arrows according to whether the list can move up or down. */
void func_ov026_0208894c(void) {
    char *st = *(char **)&data_ov026_02091368;
    char *view = st + 0xc3c4;
    char *arrows = st + 0x2ab0;
    func_ov026_020843e8(arrows, func_ov026_0208427c(arrows, 4), *(int *)(view + 4) != 0);
    func_ov026_020843e8(arrows, func_ov026_0208427c(arrows, 5),
                        (unsigned int)(*(int *)(view + 4) + 8) < (unsigned int)*(int *)(view + 8));
}
