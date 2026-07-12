/* Poll 02033ea0: on empty hand off to 0203c640; otherwise refresh the bar, and if it is active
 * but not flagged bail, then depending on +8 either hand off again or step 02033e48 and dispatch. */
extern int func_02033ea0(int);
extern int func_0203c640(int);
extern int func_02033e00(int, int);
extern int func_02033e48(int);
extern int func_0203c634(int, int, void *);
extern int func_ov107_020cb208(int);
struct sb { int b0 : 1; };
void func_ov107_020cb178(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (func_02033ea0(*(int *)(owner + 0x10)) == 0) {
        func_0203c640(param_1);
        return;
    }
    func_02033e00(*(int *)(owner + 0x10), *(int *)(owner + 0xc) + 0x10);
    int obj = *(int *)owner;
    if (((struct sb *)(obj + 0x40))->b0 != 0) {
        if ((*(unsigned char *)(obj + 0x1c4) & 2) == 0) return;
    }
    if (*(int *)(owner + 8) == 0) {
        func_0203c640(param_1);
        return;
    }
    func_02033e48(*(int *)(owner + 0x10));
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov107_020cb208);
}
