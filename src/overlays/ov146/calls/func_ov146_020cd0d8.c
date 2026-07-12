/* Kick anim 1 on the body; if the +0x58 slot is live, kick anim 1 on the child and step it;
 * seed +0x3c and dispatch 020cd138. */
extern int func_ov107_020c9264(int, int, int);
extern int func_ov146_020ce2b4(int);
extern int func_0203c634(int, int, void *);
extern int func_ov146_020cd138(int);
void func_ov146_020cd0d8(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)owner, 1, 1);
    if (*(int *)(owner + 0x58) != 0) {
        func_ov107_020c9264(*(int *)(owner + 8), 1, 1);
        func_ov146_020ce2b4(*(int *)(owner + 8));
    }
    *(int *)(owner + 0x3c) = 0x1000;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov146_020cd138);
}
