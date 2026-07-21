extern int func_ov002_0206b78c(void);
extern int func_ov022_02083fdc(void);
extern int func_ov002_0206b7a4(void);
/* True when the active panel reports idle: mode 1 uses the mission query, anything else the
 * local one. */
int func_ov002_020758b8(void) {
    int busy;
    if (func_ov002_0206b78c() == 1) {
        busy = func_ov022_02083fdc();
    } else {
        busy = func_ov002_0206b7a4();
    }
    if (busy != 0) {
        return 0;
    }
    return 1;
}
