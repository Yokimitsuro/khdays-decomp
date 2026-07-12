/* Bail via 020cc900 if not ready; else latch +0x10 into +0xc, kick anim 4, notify 020cc8ec, dispatch. */
extern int func_ov218_020cc900(int);
extern int func_ov107_020c9264(int, int, int);
extern int func_ov218_020cc8ec(int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov218_020cd6bc(int);
void func_ov218_020cd658(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (func_ov218_020cc900(param_1) < 0) {
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
        return;
    }
    *(int *)(owner + 0xc) = *(int *)(owner + 0x10);
    func_ov107_020c9264(*(int *)owner, 4, 0);
    func_ov218_020cc8ec(*(int *)owner, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov218_020cd6bc);
}
