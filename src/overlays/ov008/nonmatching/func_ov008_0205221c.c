/* NONMATCHING: loop-induction-variable tie — the ROM recomputes the cell address per iteration as
 * `add r1, base, i, lsl#3`; mwcc keeps a separate incrementing pointer (extra callee-saved reg +
 * stack slot, 104B vs 96B). Neither the array-subscript form nor a per-iteration local dislodges
 * it. */
/* func_ov008_0205221c -- re-register up to 4 sub-cells of a grid entry (array at param_3, stride 8,
 * pointer at +0x34) with the entry's row/col (param_2+0x20/+0x22), stopping at the first empty
 * slot; then commit the entry (func_ov008_020520d4). */
extern void func_ov008_02051cf0(int owner, int cell, unsigned int row, unsigned int col, int flag);
extern void func_ov008_020520d4(int entry, int cells);

struct ov008_cellref { int w[2]; };   /* 8-byte stride */

void func_ov008_0205221c(int param_1, int param_2, int param_3) {
    unsigned short row = *(unsigned short *)(param_2 + 0x20);
    struct ov008_cellref *cells = (struct ov008_cellref *)param_3;
    int i = 0;
    do {
        if (*(int *)((int)&cells[i] + 0x34) == 0) {
            break;
        }
        func_ov008_02051cf0(param_1, *(int *)((int)&cells[i] + 0x34), row,
                            *(unsigned short *)(param_2 + 0x22), 1);
        i = i + 1;
    } while (i < 4);
    func_ov008_020520d4(param_2, param_3);
}
