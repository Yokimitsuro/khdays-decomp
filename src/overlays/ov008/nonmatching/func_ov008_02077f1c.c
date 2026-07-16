/* NONMATCHING: semantics correct (page+2 step). The ROM re-tests obj+0x180 after already
 * branching on it, leaving a dead `ldmne` that can never fire (Ghidra renders it as the redundant
 * `if (bVar3) { if (bVar3) {`); mwcc elides the dead check (108B vs 112B). "Our compiler is
 * smarter" class. The +1 twin func_ov008_02077f8c has the identical shape. */
/* func_ov008_02077f1c -- "next page" on the mission list (step +2).
 * Ignored while dragging (obj+0x158). If a selection is pending (obj+0x180) it just re-arms it
 * (func_ov008_02076e80 with obj+0x184 clear); otherwise it moves to column (page+2) % 3 and
 * fires UI event 0. */
extern void func_ov008_02076e80(int obj, int arg);
extern void func_ov008_02074a4c(int obj, int col);
extern void func_02033b78(int a, int b);

void func_ov008_02077f1c(int param_1) {
    if (*(int *)(param_1 + 0x158) != 0) {
        return;
    }
    if (*(int *)(param_1 + 0x180) != 0) {
        func_ov008_02076e80(param_1, *(int *)(param_1 + 0x184) == 0);
        return;
    }
    {
        int page = *(int *)(param_1 + 4) + 2;
        func_ov008_02074a4c(param_1, page % 3);
        func_02033b78(0, 0);
    }
}
