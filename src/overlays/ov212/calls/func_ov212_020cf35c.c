/* Branch on 020cd63c: if active arm the 020c5af8 burst, else reset via 020cd5ec; dispatch accordingly. */
extern int func_ov212_020cd63c(int, int);
extern int func_ov107_020c5af8(int, int, int, int);
extern int func_ov212_020cd5ec(int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov212_020cf438(int);
extern int func_ov212_020cf3cc(int);
void func_ov212_020cf35c(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (func_ov212_020cd63c(owner, 1) != 0) {
        func_ov107_020c5af8(*(int *)owner, 0x128, 6, *(int *)(owner + 8));
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov212_020cf438);
    } else {
        func_ov212_020cd5ec(owner, 0);
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov212_020cf3cc);
    }
}
