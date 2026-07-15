/* NONMATCHING (ldm/stm pointer register tie, same as func_ov206_020ccb78): the 11-word
 * matrix copy is exact but mwcc assigns the ldm source pointer to ip and the stm dest to
 * lr, while the ROM uses lr for source and ip for dest (2-byte add/ldm/stm encoding swap).
 * dst-first restructuring doesn't flip it. 4-member family ov137/... .
 * Notify func_ov107_020c9ec8 + func_ov107_020c6980, then copy param_1's 11-word transform
 * block (param_1+0xa0) into **(param_1+0x384)+0x10. */
struct m11 { int w[11]; };
extern void func_ov107_020c9ec8(int a);
extern void func_ov107_020c6980(int a, int b);
void func_ov137_020cc290(int param_1, int param_2) {
    func_ov107_020c9ec8(*(int *)(param_1 + 0x39c));
    func_ov107_020c6980(param_1, param_2);
    *(struct m11 *)(**(int **)(param_1 + 0x384) + 0x10) = *(struct m11 *)(param_1 + 0xa0);
}
