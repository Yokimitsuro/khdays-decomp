/* Kick the 3 animation on the object, then dispatch via c634. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov245_020cff94(int);
void func_ov245_020d0664(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)owner, 3, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov245_020cff94);
}
