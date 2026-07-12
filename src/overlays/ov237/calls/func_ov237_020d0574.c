/* Unless busy, kick anim 0xe, arm the 020c5af8 timer, then dispatch. */
extern int func_ov107_020c9264(int, int, int);
extern int func_ov107_020c5af8(int, int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov237_020d05d0(int);
void func_ov237_020d0574(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (*(unsigned char *)(*(int *)(owner + 4) + 0xad) != 0) return;
    func_ov107_020c9264(*(int *)owner, 0xe, 0);
    func_ov107_020c5af8(*(int *)owner, 0x12d, 0xd, *(int *)(owner + 0x38));
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov237_020d05d0);
}
