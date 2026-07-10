extern int func_ov002_0206d448(void);
extern int func_ov002_0206d424(int a);
extern int func_ov002_02057390(int a);
extern int func_ov002_0206d3ec(int a, int b);
extern int func_ov002_020573a4(void);

/* Poll the ov002 menu flow: report busy (1) while a transition is pending; if a
 * pending action is queued, kick it and clear it; report busy again if a new
 * request arrived, else idle (0). */
int func_ov019_0207fc88(void) {
    if (func_ov002_0206d448() != 0) {
        return 1;
    }
    if (func_ov002_0206d424(0) != 0) {
        func_ov002_02057390(1);
        func_ov002_0206d3ec(0, 0);
    }
    if (func_ov002_020573a4() != 0) {
        return 1;
    }
    return 0;
}
