/* Advance the ov002 request one step. If func_ov002_0206d448 reports the queue
 * already resolved, finish immediately and post event 0x20ef. Otherwise pick the
 * pose from the sub-object's flag byte at +0x4a4, drain any pending entry, and
 * only when func_ov002_020573a4 says the step is complete either hand off to
 * func_ov002_02075578 (flag set) or finish and post the same event. */
extern int func_02021980(void *self, void *arg);
extern int func_ov002_0206d448(void);
extern void func_ov002_0207548c(void);
extern void func_020235e8(int event, int a, int b);
extern void func_ov002_02057390(int pose);
extern void func_ov002_0206d3ec(int a, int b);
extern int func_ov002_0206d424(int a);
extern int func_ov002_020573a4(void);
extern void func_ov002_02075578(void *self, void *req);

int func_ov002_0207568c(int *self, char *req) {
    int pose = func_02021980(self, req + 8);

    if (func_ov002_0206d448() != 0) {
        func_ov002_0207548c();
        func_020235e8(0x20ef, 1, 0);
        return 1;
    }

    if (*(signed char *)(self[0x4a] + 0x4a4) != 0) {
        func_ov002_02057390(1);
    } else {
        func_ov002_02057390(pose);
        func_ov002_0206d3ec(0, 0);
    }

    if (func_ov002_0206d424(0) != 0) {
        func_ov002_02057390(1);
        func_ov002_0206d3ec(0, 0);
    }

    if (func_ov002_020573a4() != 0) {
        if (*(signed char *)(self[0x4a] + 0x4a4) != 0) {
            func_ov002_02075578(self, req);
            return 0;
        }
        func_ov002_0207548c();
        func_020235e8(0x20ef, 1, 0);
        return 1;
    }

    return 0;
}
