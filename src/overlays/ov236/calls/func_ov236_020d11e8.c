/* Kick anim 0x10, arm the 020c5af8 timer, set the +0x1ae bit, then dispatch. */
extern int func_ov107_020c9264(int, int, int);
extern int func_ov107_020c5af8(int, int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov236_020d1248(int);
void func_ov236_020d11e8(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)owner, 0x10, 0);
    func_ov107_020c5af8(*(int *)owner, 0x127, 0x10, *(int *)(owner + 0x38));
    *(unsigned short *)(*(int *)owner + 0x1ae) |= 1;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov236_020d1248);
}
