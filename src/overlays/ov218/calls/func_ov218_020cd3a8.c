/* Poll 020cc900: if it reports failure just dispatch, otherwise kick anim 3, clear +0x14/+0x40
 * and advance to 020cd404. */
extern int func_ov218_020cc900(int);
extern int func_0203c634(int, int, void *);
extern int func_ov107_020c9264(int, int, int);
extern int func_ov218_020cd404(int);
void func_ov218_020cd3a8(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (func_ov218_020cc900(param_1) < 0) {
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
    } else {
        func_ov107_020c9264(*(int *)owner, 3, 0);
        *(int *)(owner + 0x14) = 0;
        *(unsigned char *)(owner + 0x40) = 0;
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov218_020cd404);
    }
}
