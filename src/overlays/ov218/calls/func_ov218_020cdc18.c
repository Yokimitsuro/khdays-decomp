/* Kick anim 8, run 020cc8ec, arm the 020c5af8 timer, then dispatch via c634. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov218_020cc8ec(int, int);
extern int func_ov107_020c5af8(int, int, int, int);
extern int func_ov218_020cdc70(int);
void func_ov218_020cdc18(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)owner, 8, 0);
    func_ov218_020cc8ec(*(int *)owner, 1);
    func_ov107_020c5af8(*(int *)owner, 0x135, 7, *(int *)(owner + 8));
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov218_020cdc70);
}
