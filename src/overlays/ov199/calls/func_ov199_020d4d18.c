/* Push the +0x28 vector into 020d43a4; unless busy kick anim 3, run 020d4234 and dispatch. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
struct w3 { int a, b, c; };
extern int func_ov199_020d43a4(int, struct w3, int);
extern int func_ov199_020d4234(int, int);
extern int func_ov199_020d4d80(int);
void func_ov199_020d4d18(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov199_020d43a4(owner, *(struct w3 *)(owner + 0x28), 1);
    if (*(unsigned char *)(*(int *)(owner + 4) + 0xad) != 0) return;
    func_ov107_020c9264(*(int *)owner, 3, 0);
    func_ov199_020d4234(*(int *)owner, 1);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov199_020d4d80);
}
