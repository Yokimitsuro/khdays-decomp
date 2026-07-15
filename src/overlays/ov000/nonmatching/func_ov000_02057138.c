/* NONMATCHING (loop strength-reduction tie): mwcc 139 walks the entry pointer (+= 8)
 * and CSEs the +0x34 handle load into one register (140B), whereas the ROM recomputes
 * `param_3 + i*8` from i each iteration and re-loads the handle per branch (152B),
 * keeping param_3 in one register for the trailing func_ov000_02056f90 call. Array-index
 * rewrite only made it worse (extra *4 counter). 6-member family ov000/... .
 * For up to 4 stride-8 entries invoke func_ov000_02056cb4 with scaled +0x38/+0x3a. */
extern void func_ov000_02056cb4(int a, int handle, unsigned int x, unsigned int y, unsigned int p4);
extern void func_ov000_02056f90(int param_2, int param_3);
void func_ov000_02057138(int param_1, int param_2, int param_3, unsigned int param_4) {
    unsigned short sx = *(unsigned short *)(param_2 + 0x20);
    unsigned short sy = *(unsigned short *)(param_2 + 0x22);
    int i = 0;
    do {
        int e = param_3 + i * 8;
        if (*(int *)(e + 0x34) == 0) break;
        if (i == 0) {
            func_ov000_02056cb4(param_1, *(int *)(e + 0x34), *(unsigned short *)(e + 0x38),
                                sy * *(unsigned short *)(e + 0x3a), param_4);
        } else {
            func_ov000_02056cb4(param_1, *(int *)(e + 0x34), sx * *(unsigned short *)(e + 0x38),
                                sy * *(unsigned short *)(e + 0x3a), param_4);
        }
        i++;
    } while (i < 4);
    func_ov000_02056f90(param_2, param_3);
}
