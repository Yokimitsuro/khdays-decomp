extern int OS_IsThreadAvailable_0x0205f534(void);
extern int func_ov002_0206d424(void);
extern void func_ov002_02057390(int a);
extern void func_ov002_0206d3ec(int a, int b);
extern int func_ov002_020573a4(void);
extern void func_020235e8(int id, int a, unsigned short b);
extern void func_ov002_0205f594(void);
extern void func_ov002_0207548c(void);

/* Confirms the highlighted mission: plays the accept cue, tears the browser down and starts the
 * mission, unless nothing is selected or the confirmation is refused. */
int func_ov002_02075860(void) {
    int sel = OS_IsThreadAvailable_0x0205f534();
    if (sel >= 0) {
        if (func_ov002_0206d424() != 0) {
            func_ov002_02057390(1);
            func_ov002_0206d3ec(sel, 0);
        }
        if (func_ov002_020573a4() != 0) {
            func_020235e8(0x208d, 2, (unsigned short)sel);
            func_ov002_0205f594();
            func_ov002_0207548c();
            func_020235e8(0x20ef, 1, 0);
            return 1;
        }
    }
    return 0;
}
