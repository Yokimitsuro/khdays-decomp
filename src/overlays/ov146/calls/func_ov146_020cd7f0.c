/* Set bit0 of both bodies' +0x1ae, OR 2 into the shared +0x3ac->+8 byte, kick anim 9 on the body
 * and anim 8 on the child, step the child, then dispatch 020cd88c. */
extern int func_ov107_020c9264(int, int, int);
extern int func_ov146_020ce2b4(int);
extern int func_0203c634(int, int, void *);
extern int func_ov146_020cd88c(int);
struct b8 { unsigned f : 8; };
void func_ov146_020cd7f0(int param_1) {
    int owner = *(int *)(param_1 + 4);
    *(unsigned short *)(*(int *)owner + 0x1ae) |= 1;
    *(unsigned short *)(*(int *)(owner + 8) + 0x1ae) |= 1;
    ((struct b8 *)(*(int *)(*(int *)(owner + 8) + 0x3ac) + 8))->f |= 2;
    func_ov107_020c9264(*(int *)owner, 9, 0);
    func_ov107_020c9264(*(int *)(owner + 8), 8, 0);
    func_ov146_020ce2b4(*(int *)(owner + 8));
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov146_020cd88c);
}
