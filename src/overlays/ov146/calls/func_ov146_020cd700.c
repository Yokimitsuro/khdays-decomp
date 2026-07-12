/* Set bit0 of both bodies' +0x1ae, OR 2 into the shared +0x3ac->+8 byte, anim 8 on body/anim 7 on
 * child + step it, arm the 0x125/6 timer with +0xc, flag +0x58 and dispatch 020cd7bc. */
extern int func_ov107_020c9264(int, int, int);
extern int func_ov146_020ce2b4(int);
extern int func_ov107_020c5af8(int, int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov146_020cd7bc(int);
struct b8 { unsigned f : 8; };
void func_ov146_020cd700(int param_1) {
    int owner = *(int *)(param_1 + 4);
    *(unsigned short *)(*(int *)owner + 0x1ae) |= 1;
    *(unsigned short *)(*(int *)(owner + 8) + 0x1ae) |= 1;
    ((struct b8 *)(*(int *)(*(int *)(owner + 8) + 0x3ac) + 8))->f |= 2;
    func_ov107_020c9264(*(int *)owner, 8, 0);
    func_ov107_020c9264(*(int *)(owner + 8), 7, 0);
    func_ov146_020ce2b4(*(int *)(owner + 8));
    func_ov107_020c5af8(*(int *)owner, 0x125, 6, *(int *)(owner + 0xc));
    *(int *)(owner + 0x58) = 1;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov146_020cd7bc);
}
